#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include "poelon.h"
// Communication Série du robot
class Comm
{
public:
    void update();
    void spam_baro();
    void spam_odom();
    void spamValeursCapt();
    void reportStateMachineStates(int av, int ar);
    void reportStart();

private:
    //Attributs
    //Serial2 for usb, Serial3 for Xbee
    HardwareSerial& SerialCom = Serial2; //Serial3;

    char buffer[70];
    int buf_index = 0;
    int sentDescr = 0;
    int spammingContact = 0;

    // méthodes privées
    void parse_data();
    void cmdStop();
    void cmdResetPosition();
    void cmdSetPID();
    void cmdVitesse();
    void cmdActionneurAX12A();
    void cmdActionneurBaro();
    void cmdActionneurPompe();
    void cmdActionneurVanne();
    void cmdActionneurServo();
    void cmdActionneurDisplay();
    void cmdActionneurOhmMetre();
    void cmdMacro();
    void cmdCaptContact();
};
extern Comm radio;
extern int color;
#endif