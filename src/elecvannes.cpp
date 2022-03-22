#include "elecvannes.h"
#include "config.h"


ElecVanne ev1(EV1);
ElecVanne ev2(EV2);

ElecVanne::ElecVanne(int broche){
    pinMode(broche,OUTPUT);
    pin=broche;
    putOff();
    tempsMiseOn = 0;
}

void ElecVanne::putOff(){
    isOn = 0;
    digitalWrite(pin,LOW);
}

void ElecVanne::putOn(){
    isOn = 1;
    tempsMiseOn = millis();
    digitalWrite(pin,HIGH);
}

void ElecVanne::update(){
    if (isOn && (millis()-tempsMiseOn > TEMPS_OUVERTURE_VANNE)){
        putOff();
        //Serial2.print("stopped");
    }
}
