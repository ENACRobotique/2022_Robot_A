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
    uint32_t temp1;
    uint32_t temp2;

    digitalWrite (CLK_PRESSION, LOW);
    delayMicroseconds(1);
    while ((digitalRead (DATA_PRESSION1)==HIGH) || (digitalRead(DATA_PRESSION2)==HIGH)){}
    for (int j=0; j<10;j++){
        for (int i = 23; i >-1; i--){
            digitalWrite (CLK_PRESSION, HIGH);
            delayMicroseconds(1);
            digitalWrite (CLK_PRESSION, LOW);

            if (digitalRead(DATA_PRESSION1)==HIGH){bitSet(temp1,i);}
            if (digitalRead(DATA_PRESSION2)==HIGH){bitSet(temp2,i);}
            delayMicroseconds(1);
        }
        if (j==0){
            valeur1=temp1;
            valeur2=temp2;
        }
        else{
            valeur1 = min (valeur1,temp1);
            valeur2 = min (valeur2,temp2);
        }
    }
    if (spamOn){
        radio.spam_baro();
    }

}