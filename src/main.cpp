#include <Arduino.h>

//#include <comm.h>
#include <config.h>
#include <motor.h>
#include <odom.h>
#include <../lib/metro.h>
//#include "poelon.h"

Odometry odom = Odometry();
MotorControl motor = MotorControl();

Metro metro_odom = Metro(ENCODER_PERIOD);
//Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_PERIOD);

Metro metro_test = Metro(1000);

#ifndef UNIT_TEST
void setup() {
    Serial2.begin(115200);
    while(!Serial2) {}
    Serial2.println("aaaaa");

    //Poelon::init();
    odom.init();//initialisation odométrie
    motor.init();//initialisation moteur
}

// double sp[4] = {100, 0, -100, 0};
// double omg[4] = {0, 0, 0, 0};
// int i = 0;

void loop() {
    //Comm::update();
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        //Serial2.println("bbbbb");
        odom._update();
    }
    if (metro_motor.check()){//mise à jour du contrôle moteur
       motor.update();
    }

    // if(metro_test.check()){
    //     motor.set_cons(sp[i], omg[i]);
    //     i = (i+1)%4;
    // }
}
#endif