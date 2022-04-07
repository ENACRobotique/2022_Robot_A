#ifndef ELECVANNES
#define ELECVANNES

#include <Arduino.h>
#include "config.h"

class ElecVanne{
    public:
        ElecVanne(int broche);
        void update();
        void putOn();
        void putOff();
        int getState(){return isOn;};
    private:
        int pin;
        int isOn=0;
        long tempsMiseOn;
};

extern ElecVanne ev1;
extern ElecVanne ev2;
#endif
