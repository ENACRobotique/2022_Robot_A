#include <Arduino.h>

#include <comm.h>
#include <config.h>
#include <metro.h>
#include <odom.h>

Odometry odom = Odometry();
Metro metro_odom = Metro(ENCODER_RATE_MILLIS);
Metro metro_comm = Metro(CONTROL_RATE);

void setup() {
    odom.init();//initialisation odométrie
}

void loop() {
    if (metro_odom.check()){//mise à jour périodique de l'odométrie (logiciel)
        odom._update();
    }
    if (metro_comm.check()){//récupération périodique des informations via Serial
        Comm::update();
    }
}