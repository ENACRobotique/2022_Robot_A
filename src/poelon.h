#ifndef POELON
#define POELON

#include <Servo.h>

//attention: l'usage de Servo sur STM32 peut amener une plus grande charge CPU

namespace Poelon {
    extern Servo poel;
    //TODO: ajouter le périphérique de lecture de résistance
    extern int active_color;
    void init();
    void detach();
    void changerEtat(bool nv_etat);
    bool recupEtat();
    void pousserCarre();
    int lireResistance();
    int autoPush();
    void setCouleur(int coul);
}

#endif //POELON