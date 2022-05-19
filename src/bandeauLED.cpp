#include "bandeauLED.h"
#include "comm.h"

void bandeauLED::init(){
    pinMode(PIN_BANDEAU_LED, OUTPUT);
    FastLED.addLeds<WS2812B, PIN_BANDEAU_LED, RGB>(leds, NB_LEDS);
    for (int i=0;i<NB_LEDS;i++){
        leds[i]=CRGB::Black;
    }
    FastLED.show();

}

void bandeauLED::setLED_ON(int id){
    if ((id>=0)&&(id<NB_LEDS)){
        leds[id]= ( color ? CRGB::Yellow : CRGB::Purple );
        FastLED.show();
    }
}