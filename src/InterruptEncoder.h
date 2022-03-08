#include "AbstractEncoder.h"

class InterruptEncoder: public AbstractEncoder {
    public:
        InterruptEncoder(int pinA, int pinB): pinA(pinA), pinB(pinB){}
        
        int get_value() {
            //return counter;
            auto tmp = counter;
            counter = 0;
            return tmp;
        }

        void init() {
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

    private:
        int pinA;
        int pinB;

        int counter;
};

extern InterruptEncoder encoder_m1;
extern InterruptEncoder encoder_m2;
//extern InterruptEncoder encoder_w1;
//extern InterruptEncoder encoder_w2;