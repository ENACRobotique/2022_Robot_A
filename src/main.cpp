#include <Arduino.h>

#include <comm.h>
#include <config.h>
#include <motor.h>
#include <odom.h>
#include <../lib/metro.h>
#include "poelon.h"

Odometry odom = Odometry();
Metro metro_odom = Metro(ENCODER_RATE_MILLIS);
Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_RATE);

//attention si utilisation du software Serial2 avec STM32DUINO
//d'après la doc, impacte beaucoup le CPU à fort baud rate


void setup() {
    Serial2.begin(9600);
    Serial2.println("aaaaa");
    while(!Serial2) {}
    delay(0.5f); //wait for serial to be ready

    Poelon::init();
    odom.init();//initialisation odométrie
    MotorControl::init();//initialisation du ctrl moteur
}

void loop() {
    delay(0.9f);
    odom._update();
    Comm::update();
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        //odom._update();
    }
    if (metro_comm.check()){//récupération périodique des informations via Serial2
        Comm::update();
    }
    if (metro_motor.check()){//mise à jour du contrôle moteur
        MotorControl::update();
    }
}
