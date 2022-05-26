#ifndef STRAT
#define STRAT

#include "macros.h"
#include "motor.h"
#include "odom.h"
#include "DisplayController.h"

float TIME_START = 0.0;
typedef int event;
typedef int state_id;

//flags pour que le loop gère des trucs liés aux moteurs

bool is_going_stat = false;


bool is_going_back = false;

// évènements qui peuvent générer des transitions manuelles

const event TRIGGER_TIRETTE = 0;

// états

const state_id WAITING_TIRETTE = 0;
const state_id GOING_STAT = 1;
const state_id AT_STAT = 2;
const state_id PUSHED_STAT = 3;
const state_id DROPPED_REPL = 4;
const state_id GONE_BACK = 5;

//état 0: attendre tirette
void nothing(){
    afficheur.setNbDisplayed(0);
    AX12As.moveSpeed(4, BRAS_AR_N, ARM_SPEED_SLOW);
    AX12As.moveSpeed(5, MAIN_AR_N, HAND_SPEED);
}
state_id waiting_tirette_tr(event evt){
    return GOING_STAT;
}
State waiting_tirette(-1, -1, &nothing, &waiting_tirette_tr);

//état 1: aller à la statuette
const int GOING_STAT_TIMEOUT = 5500;
const state_id GOING_STAT_TIMEOUT_AUTOTR = AT_STAT;
void go_stat(){
    afficheur.setNbDisplayed(4);
    is_going_stat = true;
    //bouger les bras
    AX12As.moveSpeed(4, 775, ARM_SPEED_SLOW);
    AX12As.moveSpeed(5, 250, HAND_SPEED);
}
state_id no_man_tr(event evt){
    return -1;
}
State going_stat(GOING_STAT_TIMEOUT_AUTOTR, GOING_STAT_TIMEOUT, &go_stat, &no_man_tr);

//état 2: à la statuette
const int AT_STAT_TIMEOUT = 10000;
const state_id AT_STAT_TIMEOUT_AUTOTR = PUSHED_STAT;
void push_stat(){
    afficheur.setNbDisplayed(9);
    is_going_stat = false;
    AX12As.moveSpeed(4, 620, ARM_SPEED_SLOW);
    AX12As.moveSpeed(5, 0, HAND_SPEED);
}
State at_stat(AT_STAT_TIMEOUT_AUTOTR, AT_STAT_TIMEOUT, &push_stat, &no_man_tr);

//état 3: a poussé la statuette
const int PUSHED_STAT_TIMEOUT = 20000;
const state_id PUSHED_STAT_TIMEOUT_AUTOTR = DROPPED_REPL;
void drop_repl(){
    afficheur.setNbDisplayed(9);
    digitalWrite(POMPE2, LOW);
    ev2.putOn();
}
State pushed_stat(PUSHED_STAT_TIMEOUT_AUTOTR, PUSHED_STAT_TIMEOUT, &drop_repl, &no_man_tr);

//état 4: a droppé la réplique
const int DROPPED_REPL_TIMEOUT = 4750;
const state_id DROPPED_REPL_TIMEOUT_AUTOTR = GONE_BACK;
void go_back(){
    //ev2.putOn();
    afficheur.setNbDisplayed(14);
    AX12As.moveSpeed(4, NEUTRAL_ARM_AR, ARM_SPEED_SLOW);
    AX12As.moveSpeed(5, NEUTRAL_HAND_AR, HAND_SPEED);
    delay(1000);
    AX12As.moveSpeed(4, 700, ARM_SPEED_SLOW);
    //AX12As.moveSpeed(5, NEUTRAL_HAND_AR, HAND_SPEED);
    delay(1000);
    AX12As.moveSpeed(4, NEUTRAL_ARM_AR, ARM_SPEED_SLOW);
    //AX12As.moveSpeed(5, NEUTRAL_HAND_AR, HAND_SPEED);
    is_going_back = true;
}
State dropped_repl(DROPPED_REPL_TIMEOUT_AUTOTR, DROPPED_REPL_TIMEOUT, &go_back, &no_man_tr);

//état 5: on est de retour
void things_at_home(){
    afficheur.setNbDisplayed(34);
    is_going_back = false;
}
State gone_back(-1, -1, &things_at_home, &no_man_tr);

StateMachine strat_machine({
    waiting_tirette,
    going_stat,
    at_stat,
    pushed_stat,
    dropped_repl,
    gone_back
});

#endif