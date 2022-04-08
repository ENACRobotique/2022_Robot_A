#include "macros.h"

void saisirPaletAvant(){
    //orienter la main avant
    AX12As.moveSpeed((unsigned) 7, POS_MAIN_AVANT_SAISIR, 400);

    //baisser le bras avant
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_SAISIR, 150);

    //fermer EV avant
    ev1.putOn();

    //attendre un peu
    delay(AVANT_SAISIR_DELAY);

    //allumer pompe avant
    digitalWrite(POMPE1, HIGH);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_NEUTRE, 150);
}

void saisirPaletArriere(){
    //orienter la main ARRIERE
    AX12As.moveSpeed((unsigned) 5, POS_MAIN_ARRIERE_SAISIR, 400);

    //baisser le bras ARRIERE
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_SAISIR, 150);

    //fermer EV ARRIERE
    ev2.putOn();

    //attendre un peu
    delay(ARRIERE_SAISIR_DELAY);

    //allumer pompe ARRIERE
    digitalWrite(POMPE2, HIGH);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_NEUTRE, 150);
}

void mettrePaletAvant(){
    //orienter la main avant
    AX12As.moveSpeed((unsigned) 7, POS_MAIN_AVANT_METTRE, 400);

    //baisser le bras avant
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_METTRE, 150);

    //couper pompe avant
    digitalWrite(POMPE1, LOW);
    //ouvrir EV avant
    ev1.putOff();

    //attendre un peu
    delay(AVANT_METTRE_DELAY);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_NEUTRE, 150);
}

void mettrePaletArriere(){
    //orienter la main ARRIERE
    AX12As.moveSpeed((unsigned) 5, POS_MAIN_ARRIERE_METTRE, 400);

    //baisser le bras ARRIERE
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_METTRE, 150);

    //couper pompe ARRIERE
    digitalWrite(POMPE2, LOW);
    //ouvrir EV ARRIERE
    ev2.putOff();

    //attendre un peu
    delay(ARRIERE_METTRE_DELAY);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_NEUTRE, 150);
}

void sortirPaletAvant(){
    //fermer EV avant
    ev1.putOn();

    //orienter la main avant
    AX12As.moveSpeed((unsigned) 7, POS_MAIN_AVANT_SORTIR, 400);

    //baisser le bras avant
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_SORTIR, 150);

    //allumer pompe avant
    digitalWrite(POMPE1, HIGH);
    
    //attendre un peu
    delay(AVANT_SORTIR_DELAY);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 6, POS_BRAS_AVANT_NEUTRE, 150);

    //orienter main en position de sortie
    AX12As.moveSpeed((unsigned) 7, POS_MAIN_AVANT_NEUTRE, 150);
}

void sortirPaletArriere(){
    //fermer EV ARRIERE
    ev2.putOn();

    //orienter la main ARRIERE
    AX12As.moveSpeed((unsigned) 5, POS_MAIN_ARRIERE_SORTIR, 400);

    //baisser le bras ARRIERE
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_SORTIR, 150);

    //allumer pompe ARRIERE
    digitalWrite(POMPE2, HIGH);

    //attendre un peu
    delay(ARRIERE_SORTIR_DELAY);

    //relever le bras en position plus normale
    AX12As.moveSpeed((unsigned) 4, POS_BRAS_ARRIERE_NEUTRE, 150);

    //orienter main en position de sortie
    AX12As.moveSpeed((unsigned) 5, POS_MAIN_ARRIERE_NEUTRE, 150);
}