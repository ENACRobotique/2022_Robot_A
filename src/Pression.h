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
        void setSpamOn(){spamOn=1;};
        void shutDownSpam(){spamOn=0;};


    private:
        uint32_t valeur1;
        uint32_t valeur2;
        int spamOn = 0;

};
extern CapteurPression barometre;
#endif
