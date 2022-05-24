#pragma once

#include "AbstractEncoder.h"

class InterruptEncoder: public AbstractEncoder {
    public:
        InterruptEncoder(int pinA, int pinB): pinA(pinA), pinB(pinB){}
        
        int get_value();
        void init();

    private:
        int pinA;
        int pinB;

        int counter;
};

extern InterruptEncoder encoder_m1;
extern InterruptEncoder encoder_m2;
extern InterruptEncoder encoder_w1;
extern InterruptEncoder encoder_w2;