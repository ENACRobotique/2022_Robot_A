#pragma once
#include <arduino.h>
#include "../lib/FastLED-3.4.0/src/FastLED.h"
#include "config.h"

class bandeauLED{
    public:
        void init();
        void setLED_ON(int id);
    private:
        int NB_LEDS =10;
        CRGB leds[NB_LEDS];
}

extern bandeauLED rubanLED;