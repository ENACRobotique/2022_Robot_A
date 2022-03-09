#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
//Communication Série du robot
class Comm {
public :
    void update();
    void spam_odom();
private:
    //Attributs
    //Serial2 for usb, Serial3 for Xbee
    HardwareSerial& SerialCom = Serial3; //Serial3;

    char buffer[70];
    int buf_index = 0;

    //méthodes privées
    void parse_data();

};
extern Comm radio;
#endif