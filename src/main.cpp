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

#include "strat.h"

//#define BASIC_STRAT

InterruptEncoder encoder_m1(ENCODER_MOTOR1_B, ENCODER_MOTOR1_A);
InterruptEncoder encoder_m2(ENCODER_MOTOR2_A, ENCODER_MOTOR2_B);
InterruptEncoder encoder_w1(ENCODER_WHEEL1_B, ENCODER_WHEEL1_A);
InterruptEncoder encoder_w2(ENCODER_WHEEL2_B, ENCODER_WHEEL2_A);

CapteurPression barometre;

Odometry odom = Odometry(encoder_m1, encoder_m2,INC_TO_MM_MOTOR_RIGHT, INC_TO_MM_MOTOR_LEFT, MOTOR_BASE);
Odometry odom_wheel = Odometry(encoder_w1, encoder_w2, INC_TO_MM_WHEEL_RIGHT, INC_TO_MM_WHEEL_LEFT, ENCODER_BASE);
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
int color = (digitalRead(COLOR) == HIGH)?0:1;


float time_start = 0.0;

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
    AX12As.setCMargin(6,5,5);
    AX12As.setCMargin(4,5,5);

    Serial2.begin(115200); // STLink serial port
    Serial3.begin(57600);  // XBee serial port

    poel.initServo();
    afficheur.init();
    afficheur.setNbDisplayed(valDisplayed++);

    odom.init();  // initialisation odométrie
    odom_wheel.init();
    motor.init(); // initialisation moteur
    pinMode(POMPE1, OUTPUT);
    pinMode(POMPE2, OUTPUT);
    color = (digitalRead(COLOR) == HIGH) ? 0:1;

    motor.stop();

    // mise des AX-12 en neutre sans palets
    //neutre(true);
    //neutre(false);
    //bras_main_pompe_ev_ar.start();
    //bras_main_pompe_ev_av.start();
    strat_machine.start();
    //encoder_hw.init();
}
void loop()
{
    if ((! hasStarted)&(digitalRead(TIRETTE)==LOW)){
        hasStarted=1;
        //bras_main_pompe_ev_ar.forceState(START_REPL_HAND);
        time_start = millis();
        digitalWrite(POMPE2, HIGH); //aggripper la statuette
        delay(1000);
        strat_machine.handleEvent(TRIGGER_TIRETTE);
    }
    radio.update();
    if (metro_odom.check())
    { // mise à jour périodique de l'odométrie (logiciel)
        // Serial2.println("bbbbb");
        odom._update();
        //odom_wheel._update();
    }
    if (metro_motor.check())
    { // mise à jour du contrôle moteur
        motor.update();
        // Serial3.println("test");
    }
    if (metro_spam_odom.check())
    { // mise à jour périodique de l'odométrie (xbee)
        barometre.update();
        //radio.spam_odom();
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

    }
    if (state_machine_check.check()){
        /*if (bras_main_pompe_ev_ar.isStarted()){
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
        }
        //printing state machine states to serial as actuator value
        radio.reportStateMachineStates(bras_main_pompe_ev_av.current_state(), bras_main_pompe_ev_ar.current_state());
        */
        strat_machine.checkAutoTransitions();
        if (false){} 
        else if (is_going_stat){
            motor.set_cons(-175.0, 0.0); //on est vers l'arrière donc on recule
        } else if (is_going_back){
            motor.set_cons(200.0, (color==1)?-0.1:0.1);
        } else {
            motor.stop();
        }
    }

}