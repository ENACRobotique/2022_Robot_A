#ifndef POELON
#define POELON

#include <Servo.h>

//attention: l'usage de Servo sur STM32 peut amener une plus grande charge CPU

class Poelon {
    public:
        Poelon();
        void changerEtat(bool nv_etat);
        bool recupEtat();
        void pousserCarre();
        int lireResistance();
        int autoPush();
        void setCouleur(int coul);
    private:
        Servo poel;
        int active_color;
};

extern Poelon poel;

#endif //POELON