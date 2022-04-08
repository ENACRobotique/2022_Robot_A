#ifndef __MACROS__
#define __MACROS__

#include "config.h"
#include <Arduino.h>
#include "AX12A.h"
#include "elecvannes.h"

//position neutre bras
const int BRAS_AV_N = 655;
const int BRAS_AR_N = 655;

//position neutre main sans palet
const int MAIN_AV_N = 350;
const int MAIN_AR_N = 350;

//positions neutre main avec palet
const int MAIN_AV_P_N = 600;
const int MAIN_AR_P_N = 100;

//saisirSol
const int MAIN_AV_SSol = 700;
const int MAIN_AR_SSol = 50;
const int BRAS_AV_SSol = 360;
const int BRAS_AR_SSol = 950;

const int SSol_DELAY = 1500;

//mettre
const int MAIN_AV_M = 200;
const int MAIN_AR_M = 500;
const int BRAS_AV_M = 700;
const int BRAS_AR_M = 580;
const int METTRE_DELAY_HAND = 250;
const int METTRE_DELAY = 700;
const int METTRE_DELAY_RELACHER = 500;

//sortir
const int BRAS_AV_S_PRE = 550;
const int BRAS_AR_S_PRE = 700;
const int MAIN_AV_S = 110;
const int MAIN_AR_S = 600;
const int BRAS_AV_S = 870;
const int BRAS_AR_S = 350;
const int SORTIR_DELAY_MAIN = 500;
const int SORTIR_DELAY = 1500;

//deposerSol
const int DSol_DELAY = 1500;
const int DSol_DELAY_RELACHER = 500;

void saisirSol(bool avant);

//void saisirDistrib(bool avant);

//void saisirHaut(bool avant);

void mettre(bool avant);

void sortir(bool avant);

void deposerSol(bool avant);

//void deposerAngle(bool avant);

#endif //__MACROS__