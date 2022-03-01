#include <poelon.h>
#include <config.h>

void Poelon::init(){
    poel = Servo();
    poel.attach(POELON_SERVO_PIN, POELON_RETRACTED_ANGLE);
    pinMode(POELON_READ_PIN, INPUT);
    active_color = 0;
}

void Poelon::detach(){
    poel.detach();
}

void Poelon::changerEtat(bool nv_etat){
    if (nv_etat){
        poel.write(POELON_DEPLOYED_ANGLE);
    } else {
        poel.write(POELON_RETRACTED_ANGLE);
    }
}

bool Poelon::recupEtat(){
    if (poel.attached()){
        int angle = poel.read();
        if (POELON_DEPLOYED_ANGLE - POELON_ANGLE_TOL_MINUS <= angle && angle <= POELON_DEPLOYED_ANGLE + POELON_ANGLE_TOL_PLUS){
            return true; // le poelon est dans un endroit adéquat pour lire les résistances
        } 
    }
    return false; // le servo n'est pas associé ou n'est pas dans un endroit adapté pour lire les résistances
}

int Poelon::lireResistance(){
    int value = analogRead(POELON_READ_PIN);
    //codes à retourner:
    //1: ~470 Ohms (violet)
    //2: ~1,0 kOhm (jaune)
    //3: ~4,7 kOhms (rouge)
    //0 | tout le reste: lecture a échoué (pas de contact par ex.)
    //TODO: ajouter le code de lecture de la résistance electrique
    return 0;
}

void Poelon::pousserCarre(){
    bool etat_avant = Poelon::recupEtat();
    poel.write(POELON_PUSH_ANGLE);
    //wait a moment (blocking or non-blocking?)
    //TODO: tester les deux méthodes
    delay(250); //mode bloquant
    Poelon::changerEtat(etat_avant);
}

void Poelon::setCouleur(int coul){
    Poelon::active_color = coul;
}

int Poelon::autoPush(){
    //lire la résistance et pousser le carré si besoin
    int mesure = Poelon::lireResistance();
    if (mesure == active_color){
        Poelon::pousserCarre();
        return mesure+10;
    }
    return mesure;
}