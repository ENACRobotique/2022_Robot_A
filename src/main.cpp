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


Odometry odom = Odometry();
MotorControl motor = MotorControl();
Poelon poel = Poelon();

Metro metro_odom = Metro(ENCODER_PERIOD);
//Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_PERIOD);
Metro metro_spam_odom = Metro(SPAM_ODOM_PERIOD);
Metro metro_spam_valCapt = Metro(SPAM_CAPT);

Comm radio = Comm();
DynamixelSerial AX12As = DynamixelSerial();
DisplayController afficheur = DisplayController();
int valDisplayed = 0;
char color = 'n';

#ifndef UNIT_TEST

void setup() {
    pinMode(COLOR,INPUT_PULLUP);
    AX12As.init(&Serial1);    
    Serial2.begin(115200);  // STLink serial port
    Serial3.begin(57600);   // XBee serial port

    poel.initServo();
    afficheur.init();
    afficheur.setNbDisplayed(valDisplayed++);

    odom.init();//initialisation odométrie
    motor.init();//initialisation moteur
    pinMode(POMPE1,OUTPUT);
    pinMode(POMPE2,OUTPUT);
    if (digitalRead(COLOR)==LOW) {color='j';}
    else {color='v';}
}

// double sp[4] = {100, 0, -100, 0};
// double omg[4] = {0, 0, 0, 0};
// int i = 0;

void loop() {
    radio.update();
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        //Serial2.println("bbbbb");
        odom._update();
    }
    if (metro_motor.check()){//mise à jour du contrôle moteur
       motor.update();
       //Serial3.println("test");
    }
    if(metro_spam_odom.check()){//mise à jour périodique de l'odométrie (xbee)
        radio.spam_odom();
        ev1.update();
        ev2.update();
    }
    if(metro_spam_valCapt.check()){
        if (digitalRead(COLOR)==LOW) {color='j';}
        else {color='v';}
        radio.spamValeursCapt();

    }
    
    

    // if(metro_test.check()){
    //     motor.set_cons(sp[i], omg[i]);
    //     i = (i+1)%4;
    // }
}
#endif