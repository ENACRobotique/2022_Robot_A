#include <Arduino.h>

#include <comm.h>
#include <config.h>
#include <motor.h>
#include <odom.h>
#include <../lib/metro.h>

Odometry odom = Odometry();
Metro metro_odom = Metro(ENCODER_RATE_MILLIS);
Metro metro_comm = Metro(COMM_RATE);
Metro metro_motor = Metro(CONTROL_RATE);

//attention si utilisation du software serial avec STM32DUINO
//d'après la doc, impacte beaucoup le CPU à fort baud rate

void setup() {
    Serial.begin(9600);
    while(!Serial){}
    odom.init();//initialisation odométrie
    MotorControl::init();//initialisation du ctrl moteur
}

void loop() {
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        odom._update();
    }
    if (metro_comm.check()){//récupération périodique des informations via Serial
        Comm::update();
    }
    if (metro_motor.check()){//mise à jour du contrôle moteur
        MotorControl::update();
    }
}
