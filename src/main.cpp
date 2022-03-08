#include <Arduino.h>

//#include <comm.h>
#include <config.h>
#include <motor.h>
#include <odom.h>
#include <../lib/metro.h>
//#include "poelon.h"

Odometry odom = Odometry();
Metro metro_odom = Metro(ENCODER_PERIOD);
//Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_PERIOD);

#ifndef UNIT_TEST
void setup() {
    Serial2.begin(115200);
    while(!Serial2) {}
    Serial2.println("aaaaa");

    //Poelon::init();
    odom.init();//initialisation odométrie
    MotorControl motor = MotorControl();
}

void loop() {
    //Comm::update();
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        //Serial2.println("bbbbb");
        odom._update();
    }
    if (metro_motor.check()){//mise à jour du contrôle moteur
       motor.update();
    }
}
#endif