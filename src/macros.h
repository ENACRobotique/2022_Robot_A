#ifndef __MACROS__
#define __MACROS__

#include "config.h"
#include <Arduino.h>
#include "AX12A.h"
#include "elecvannes.h"
#include "state_machine.h"

const int ARM_SPEED_FAST = 400;
const int ARM_SPEED_SLOW = 200;
const int HAND_SPEED = 400;

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
const int BRAS_AV_M = 680;
const int BRAS_AR_M = 580;
const int METTRE_DELAY_HAND = 250;
const int METTRE_DELAY = 700;
const int METTRE_DELAY_RELACHER = 500;

// sortir
const int BRAS_AV_S_PRE = 550;
const int BRAS_AR_S_PRE = 700;
const int MAIN_AV_S = 110;
const int MAIN_AR_S = 600;
const int BRAS_AV_S = 725;
const int BRAS_AR_S = 570;
const int SORTIR_DELAY_MAIN = 500;
const int SORTIR_DELAY = 1500;

// deposerSol
const int DSol_DELAY = 1000;
const int DSol_DELAY_RELACHER = 500;
const int DSol_SMALL_LIFT_AV = BRAS_AV_SSol + 150;
const int DSol_SMALL_LIFT_AR = BRAS_AR_SSol - 150;
const int DSol_DELAY_LIFT = 250;

//--- macros new version, async ---

//code states
const int QUEUE_EVENT = -2;
const int INVALID = -1;

const int NEUTRAL_NOLOAD_START = 0;
extern State st_neutral_noload_start_av, st_neutral_noload_start_ar;
const int NEUTRAL_NOLOAD_END = 1;
extern State st_neutral_noload_end_av, st_neutral_noload_end_ar;
const int NEUTRAL_LOAD_START = 2;
extern State st_neutral_load_start_av, st_neutral_load_start_ar;
const int NEUTRAL_LOAD_END = 3;
extern State st_neutral_load_end_av, st_neutral_load_end_ar;
const int GET = 4;
extern State st_get_av, st_get_ar;
const int INSTORE_START = 5;
extern State st_instore_start_av, st_instore_start_ar;
const int INSTORE_MID = 6;
extern State st_instore_mid_av, st_instore_mid_ar;
const int INSTORE_END = 7;
extern State st_instore_end_av, st_instore_end_ar;
const int FROMSTORE_START = 8;
extern State st_fromstore_start_av, st_fromstore_start_ar;
const int FROMSTORE_END = 9;
extern State st_fromstore_end_av, st_fromstore_end_ar;
const int PUT_START = 10;
extern State st_put_start_av, st_put_start_ar;
const int PUT_MID = 11;
extern State st_put_mid_av, st_put_mid_ar;
const int PUT_END = 12;
extern State st_put_end_av, st_put_end_ar;

//code events
const int TRIGGER_GET = 0;
const int TRIGGER_INSTORE = 1;
const int TRIGGER_FROMSTORE = 2;
const int TRIGGER_PUT = 3;

extern StateMachine bras_main_pompe_ev_av;
extern StateMachine bras_main_pompe_ev_ar;


#endif //__MACROS__