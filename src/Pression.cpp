#include <Pression.h>
#include "comm.h"

void CapteurPression::init(){
    pinMode(CLK_PRESSION, OUTPUT);
    pinMode(DATA_PRESSION1, INPUT);
    pinMode(DATA_PRESSION2, INPUT);
}

void CapteurPression::update(){
    valeur1=0;
    valeur2=0;

    digitalWrite (CLK_PRESSION, LOW);
    delayMicroseconds(1);
    while ((digitalRead (DATA_PRESSION1)==HIGH) || (digitalRead(DATA_PRESSION2)==HIGH)){}

    for (int i = 23; i >-1; i--){
        digitalWrite (CLK_PRESSION, HIGH);
        delayMicroseconds(1);
        digitalWrite (CLK_PRESSION, LOW);

        if (digitalRead(DATA_PRESSION1)==HIGH){bitSet(valeur1,i);}
        if (digitalRead(DATA_PRESSION2)==HIGH){bitSet(valeur2,i);}
        
    }
    if (spamOn){
        radio.spam_baro();
    }

}