#ifndef CAPTEURS_PRESSION
#define CAPTEURS_PRESSION

#include <Arduino.h>
#include <config.h>

class CapteurPression{
    public:
        uint32_t readCapteur1(){return valeur1;}
        uint32_t readCapteur2(){return valeur2;}
        void update();
        void init();


    private:
        uint32_t valeur1;
        uint32_t valeur2;

};
extern CapteurPression barometre;
#endif
