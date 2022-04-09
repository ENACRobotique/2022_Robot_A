#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include "poelon.h"
//Communication Série du robot
class Comm {
public :
    void update();
    void spam_odom();
    void spamValeursCapt();
private:
    //Attributs
    //Serial2 for usb, Serial3 for Xbee
    HardwareSerial& SerialCom = Serial3; //Serial3;

    char buffer[70];
    int buf_index = 0;
    int sentDescr=0;

    //méthodes privées
    void parse_data();

};
extern Comm radio;
extern char color;
#endif