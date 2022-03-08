#include "InterruptEncoder.h"
#include "Arduino.h"


int InterruptEncoder::get_value() {
    //return counter;
    auto tmp = counter;
    counter = 0;
    return tmp;
}

void InterruptEncoder::init() {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinA), [=]() {
        if (digitalRead(pinB) == HIGH) {
            counter++;
        } else {
            counter--;
        }
    }, RISING);
}


extern InterruptEncoder encoder_m1;
extern InterruptEncoder encoder_m2;
//extern InterruptEncoder encoder_w1;
//extern InterruptEncoder encoder_w2;