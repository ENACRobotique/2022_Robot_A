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
    uint32_t tableauVal1[10];
    uint32_t tableauVal2[10];

    digitalWrite (CLK_PRESSION, LOW);
    delayMicroseconds(1);
    while ((digitalRead (DATA_PRESSION1)==HIGH) || (digitalRead(DATA_PRESSION2)==HIGH)){}
    for (int j=0; j<10;j++){
        for (int i = 23; i >-1; i--){
            digitalWrite (CLK_PRESSION, HIGH);
            delayMicroseconds(1);
            digitalWrite (CLK_PRESSION, LOW);

            if (digitalRead(DATA_PRESSION1)==HIGH){bitSet(tableauVal1[j],i);}
            if (digitalRead(DATA_PRESSION2)==HIGH){bitSet(tableauVal2[j],i);}
            delayMicroseconds(1);
        }
    }
    for(int i =0;i<10;i++){
        valeur1 += tableauVal1[i]/10;
        valeur2 += tableauVal2[i]/10;
    }
    if (spamOn){
        radio.spam_baro();
    }

}