#include "macros.h"

void neutrePalet(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    //relever le bras en position plus normale
    AX12As.moveSpeed(bras, avant?BRAS_AV_N: BRAS_AR_N, 150);

    //orienter main en position de sortie
    AX12As.moveSpeed(main, avant?MAIN_AV_P_N: MAIN_AR_P_N, 150);
}

void neutre(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    //relever le bras en position plus normale
    AX12As.moveSpeed(bras, avant?BRAS_AV_N: BRAS_AR_N, 150);

    //orienter main en position de sortie
    AX12As.moveSpeed(main, avant?MAIN_AV_N: MAIN_AR_N, 150);
}

void saisirSol(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    ElecVanne ev = avant? ev1: ev2;
    int POMPE = avant? POMPE1: POMPE2;

    //orienter la main
    AX12As.moveSpeed(main, avant?MAIN_AV_SSol: MAIN_AR_SSol, 400);

    //baisser le bras
    AX12As.moveSpeed(bras, avant?BRAS_AV_SSol: BRAS_AR_SSol, 150);

    //fermer EV
    ev.putOff();

    //allumer pompe avant
    digitalWrite(POMPE, HIGH);

    //attendre un peu
    delay(SSol_DELAY);

    neutrePalet(avant);   
}

void mettre(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    ElecVanne ev = avant? ev1: ev2;
    int POMPE = avant? POMPE1: POMPE2;

    //orienter la main
    AX12As.moveSpeed(main, avant?MAIN_AV_M: MAIN_AR_M, 400);

    delay(METTRE_DELAY_HAND);

    //baisser le bras
    AX12As.moveSpeed(bras, avant?BRAS_AV_M: BRAS_AR_M, 150);

    //attendre un peu
    delay(METTRE_DELAY);

    //couper pompe
    digitalWrite(POMPE, LOW);

    //ouvrir EV
    ev.putOn();

    delay(METTRE_DELAY_RELACHER);

    neutre(avant);
}

void sortir(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    ElecVanne ev = avant? ev1: ev2;
    int POMPE = avant? POMPE1: POMPE2;

    //fermer EV avant
    ev.putOn();

    //baisser le bras avant
    AX12As.moveSpeed(bras, avant?BRAS_AV_S_PRE:BRAS_AR_S_PRE, 150);

    //orienter la main avant
    AX12As.moveSpeed(main, avant?MAIN_AV_S: MAIN_AR_S, 400);

    delay(SORTIR_DELAY_MAIN);

    //baisser le bras avant
    AX12As.moveSpeed(bras, avant?BRAS_AV_S: BRAS_AR_S, 150);

    //allumer pompe avant
    digitalWrite(POMPE, HIGH);
    
    //attendre un peu
    delay(SORTIR_DELAY);

    neutrePalet(avant);
}

void deposerSol(bool avant){
    unsigned main = avant? (unsigned) 7: (unsigned) 5;
    unsigned bras = avant? (unsigned) 6: (unsigned) 4;
    ElecVanne ev = avant? ev1: ev2;
    int POMPE = avant? POMPE1: POMPE2;

    //orienter la main
    AX12As.moveSpeed(main, avant?MAIN_AV_SSol: MAIN_AR_SSol, 400);

    //baisser le bras
    AX12As.moveSpeed(bras, avant?BRAS_AV_SSol: BRAS_AR_SSol, 150);

    //attendre un peu
    delay(DSol_DELAY);

    //couper pompe
    digitalWrite(POMPE, LOW);

    //ouvrir ev
    ev.putOn();

    //attendre palet relaché
    delay(DSol_DELAY_RELACHER);

    neutre(avant);
}