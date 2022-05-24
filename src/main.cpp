#include <Arduino.h>

#include "comm.h"
#include "config.h"
#include "motor.h"
#include "odom.h"
#include "../lib/metro.h"
#include "AX12A.h"
#include "elecvannes.h"
#include "poelon.h"
#include "DisplayController.h"
#include "macros.h"
#include "state_machine.h"
#include "Pression.h"
#include "encodersWithTimers.h"

CapteurPression barometre;
Odometry odom = Odometry();
MotorControl motor = MotorControl();
Poelon poel = Poelon();
int hasStarted = 0;

Metro metro_odom = Metro(ENCODER_PERIOD);
// Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_PERIOD);
Metro metro_spam_odom = Metro(SPAM_ODOM_PERIOD);
Metro metro_spam_valCapt = Metro(SPAM_CAPT);
Metro state_machine_check = Metro(100.0f);

timerEncoders encoder_hw = timerEncoders();

Comm radio = Comm();
DynamixelSerial AX12As = DynamixelSerial();
DisplayController afficheur = DisplayController();
int valDisplayed = 0;
int color = 0;

int on_pompe_av = 0;
Metro metro_pompe_interm(500.0);

#ifndef UNIT_TEST

void setup()
{
    barometre.init();
    pinMode(TIRETTE, INPUT_PULLUP);
    pinMode(COLOR, INPUT_PULLUP);
    pinMode(PIN_CONTACT_1, INPUT_PULLUP);
    pinMode(PIN_CONTACT_2, INPUT_PULLUP);
    AX12As.init(&Serial1);
    // AX12As.torqueStatus(6, true);
    AX12As.setMaxTorque(6, 1023);
    AX12As.setMaxTorque(4, 1023);

    Serial2.begin(115200); // STLink serial port
    Serial3.begin(57600);  // XBee serial port

    poel.initServo();
    afficheur.init();
    afficheur.setNbDisplayed(valDisplayed++);

    odom.init();  // initialisation odométrie
    motor.init(); // initialisation moteur
    pinMode(POMPE1, OUTPUT);
    pinMode(POMPE2, OUTPUT);
    color = (digitalRead(COLOR) == HIGH) ? 0:1;

    // mise des AX-12 en neutre sans palets
    //neutre(true);
    //neutre(false);
    bras_main_pompe_ev_ar.start();
    bras_main_pompe_ev_av.start();

    //encoder_hw.init();
}

// double sp[4] = {100, 0, -100, 0};
// double omg[4] = {0, 0, 0, 0};
// int i = 0;

void loop()
{
    if ((! hasStarted)&(digitalRead(TIRETTE)==LOW)){
        hasStarted=1;
        bras_main_pompe_ev_av.forceState(START_REPL_HAND);
        radio.reportStart();
    }
    radio.update();
    if (metro_odom.check())
    { // mise à jour périodique de l'odométrie (logiciel)
        // Serial2.println("bbbbb");
        odom._update();
    }
    if ((!hasStarted)&metro_pompe_interm.check()){
        if (on_pompe_av%6){
            digitalWrite(POMPE1, LOW);
        } else {
            digitalWrite(POMPE1, HIGH);
        }
        on_pompe_av ++;
    }
    if (metro_motor.check())
    { // mise à jour du contrôle moteur
        motor.update();
        // Serial3.println("test");
    }
    if (metro_spam_odom.check())
    { // mise à jour périodique de l'odométrie (xbee)
        barometre.update();
        radio.spam_odom();
        ev1.update();
        ev2.update();
    }
    if (metro_spam_valCapt.check())
    {
        if (digitalRead(COLOR) == HIGH)
        {
            color = 0;
        }
        else
        {
            color = 1;
        }
        radio.spamValeursCapt();
        // Serial2.println("TO REMOVE BELOW in MAIN : ..");
        // Serial2.println(AX12As.readLoad(6));
    }
    if (state_machine_check.check()){
        if (bras_main_pompe_ev_ar.isStarted()){
            //Serial2.print("AR: ");
            //Serial2.print(bras_main_pompe_ev_ar.current_state());
            bras_main_pompe_ev_ar.checkAutoTransitions();
            //Serial2.print(" ");
            //Serial2.println(bras_main_pompe_ev_ar.current_state());
        }
        if (bras_main_pompe_ev_av.isStarted()){
            //Serial2.print("AV: ");
            //Serial2.print(bras_main_pompe_ev_av.current_state());
            bras_main_pompe_ev_av.checkAutoTransitions();
            //Serial2.print(" ");
            //Serial2.println(bras_main_pompe_ev_av.current_state());
        }
        //printing state machine states to serial as actuator value
        radio.reportStateMachineStates(bras_main_pompe_ev_av.current_state(), bras_main_pompe_ev_ar.current_state());
    }

    // if(metro_test.check()){
    //     motor.set_cons(sp[i], omg[i]);
    //     i = (i+1)%4;
    // }
}
#endif