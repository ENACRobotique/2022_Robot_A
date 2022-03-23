#include <poelon.h>
#include <config.h>
#include <utils.h>


constexpr PinMap PinMap_ADC[] = {
  {PB_1,  ADC1,  STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 16, 0)}, // ADC1_IN16
  {NC,   NP,    0}
};


Poelon::Poelon(){
    Servo poel = Servo();
    //poel.attach(POELON_SERVO_PIN, POELON_RETRACTED_ANGLE, POELON_DEPLOYED_ANGLE);
    int active_color = 0;
    static_assert(testADCpin(PB_1), "PB1 is not defined as ADC pin, redefine PinMap_ADC!");
    active_color++;
    active_color--;
}


void Poelon::changerEtat(int valeur){
    poel.write(valeur);
}

int Poelon::recupEtat(){
    if (poel.attached()){
        return poel.read();
    } 
    return -1; // le servo n'est pas associé ou n'est pas dans un endroit adapté pour lire les résistances
}

double Poelon::lireResistance(){
    int value = analogRead(POELON_READ_PIN);
    // seuils décision
    double voltage = ((float)value)*.00322;
    if (voltage < 0.0001){
        voltage=0.0001;
    }
    double r =((3.3-voltage)/voltage);
    if (r>99){r=99.f;}
    return r;
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