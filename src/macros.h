#ifndef __MACROS__
#define __MACROS__

#include "config.h"
#include <Arduino.h>
#include "AX12A.h"
#include "elecvannes.h"
#include "state_machine.h"


// delay neutre
const int N_DELAY = 1000;

// position neutre bras interieur sans palet
const int BRAS_AV_N = 680; // 655
const int BRAS_AR_N = 610; // 655

// position neutre bras avec palet
const int BRAS_AV_N_P = 710;
const int BRAS_AR_N_P = 570;

// position neutre main sans palet
const int MAIN_AV_N = 350; // 350
const int MAIN_AR_N = 350; // 350

// positions neutre main avec palet
const int MAIN_AV_P_N = 600;
const int MAIN_AR_P_N = 100;

// saisirSol
const int MAIN_AV_SSol = 700;
const int MAIN_AR_SSol = 0;
const int BRAS_AV_SSol = 360;
const int BRAS_AR_SSol = 950;

const int SSol_DELAY = 1500;

// mettre
const int MAIN_AV_M = 200;
const int MAIN_AR_M = 500;
const int BRAS_AV_M = 700;
const int BRAS_AR_M = 580;
const int METTRE_DELAY_HAND = 250;
const int METTRE_DELAY = 700;
const int METTRE_DELAY_RELACHER = 500;

// sortir
const int BRAS_AV_S_PRE = 550;
const int BRAS_AR_S_PRE = 700;
const int MAIN_AV_S = 110;
const int MAIN_AR_S = 600;
const int BRAS_AV_S = 870;
const int BRAS_AR_S = 350;
const int SORTIR_DELAY_MAIN = 500;
const int SORTIR_DELAY = 1500;

// deposerSol
const int DSol_DELAY = 1500;
const int DSol_DELAY_RELACHER = 500;


//--- macros old version, synchrone ---
void neutre(bool avant);
void neutrePalet(bool avant);

void saisirSol(bool avant);

// void saisirDistrib(bool avant);

// void saisirHaut(bool avant);

void mettre(bool avant);

void sortir(bool avant);

void deposerSol(bool avant);

// void deposerAngle(bool avant);

//--- macros new version, async ---

//code states
const int QUEUE_EVENT = -2;
const int INVALID = -1;
const int NEUTRAL_NOLOAD_START = 0;
const int NEUTRAL_NOLOAD_END = 1;
const int NEUTRAL_LOAD_START = 2;
const int NEUTRAL_LOAD_END = 3;
const int GET = 4;
const int INSTORE_START = 5;
const int INSTORE_MID = 6;
const int INSTORE_END = 7;
const int FROMSTORE_START = 8;
const int FROMSTORE_END = 9;
const int PUT_START = 10;
const int PUT_END = 11;

//code events
const int TRIGGER_GET = 0;
const int TRIGGER_INSTORE = 1;
const int TRIGGER_FROMSTORE = 2;
const int TRIGGER_PUT = 3;

extern StateMachine bras_main_pompe_ev_av;
extern StateMachine bras_main_pompe_ev_ar;


#endif //__MACROS__