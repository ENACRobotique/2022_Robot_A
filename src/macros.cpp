#include "macros.h"

int av_hand_content = 0;
int ar_hand_content = 0;
int store_content = 0;

//Etat neutre des bras sans charge transportée
    //début mouvement
    void neutral_noload_start_av(){
        AX12As.torqueStatus(6, true); //allumer bras
        AX12As.moveSpeed(6, BRAS_AV_N, ARM_SPEED_FAST); // relever le bras en position plus normale
        AX12As.moveSpeed(7, MAIN_AV_N, HAND_SPEED); // orienter main en position de sortie
    }
    void neutral_noload_start_ar(){
        AX12As.torqueStatus(4, true); //allumer bras
        AX12As.moveSpeed(4, BRAS_AR_N, ARM_SPEED_FAST); // relever le bras en position plus normale
        AX12As.moveSpeed(5, MAIN_AR_N, HAND_SPEED); // orienter main en position de sortie
    }
    int queue_man_events(int evt){
        return -2;
    }
    //états 0 de chaque machine
    State st_neutral_noload_start_av (NEUTRAL_NOLOAD_END, N_DELAY, &neutral_noload_start_av, &queue_man_events);
    State st_neutral_noload_start_ar (NEUTRAL_NOLOAD_END, N_DELAY, &neutral_noload_start_ar, &queue_man_events);

    //fin du mouvement
    void shutarm_av(){
        AX12As.torqueStatus(6, false);//eteindre bras avant
    }
    void shutarm_ar(){
        AX12As.torqueStatus(4, false);//eteindre bras arriere
    }
    int neutral_end_man_tr (int evt){
        switch (evt){
            case TRIGGER_GET:
                return GET;
            case TRIGGER_INSTORE:
                return INSTORE_START;
            case TRIGGER_FROMSTORE:
                return FROMSTORE_START;
            case TRIGGER_PUT:
                return PUT_START;
            case TRIGGER_GETSTAT:
                return GETSTAT_START;
            case TRIGGER_PUTSTAT:
                return PUTSTAT_START;
            case TRIGGER_REPL_HAND_START:
                return START_REPL_HAND;
            default:
                return -1;
        }
    }
    //états 1 de chaque machine
    State st_neutral_noload_end_av (-1, -1, &shutarm_av, &neutral_end_man_tr);
    State st_neutral_noload_end_ar (-1, -1, &shutarm_ar, &neutral_end_man_tr);

//Etat neutre des bras avec transport de palet
    //début du mouvement
    void neutral_load_start_av(){
        AX12As.torqueStatus(6, true); //allumer bras
        AX12As.moveSpeed(6, BRAS_AV_N_P, ARM_SPEED_FAST); // relever le bras en position plus normale
        AX12As.moveSpeed(7, MAIN_AV_P_N, HAND_SPEED); // orienter main en position de sortie
    }
    void neutral_load_start_ar(){
        AX12As.torqueStatus(4, true); //allumer bras
        AX12As.moveSpeed(4, BRAS_AR_N_P, ARM_SPEED_FAST); // relever le bras en position plus normale
        AX12As.moveSpeed(5, MAIN_AR_P_N, HAND_SPEED); // orienter main en position de sortie
    }
    //états 2 de chaque machine
    State st_neutral_load_start_av (NEUTRAL_LOAD_END, N_DELAY, &neutral_load_start_av, &queue_man_events);
    State st_neutral_load_start_ar (NEUTRAL_LOAD_END, N_DELAY, &neutral_load_start_ar, &queue_man_events);

    //fin du mouvement
    int neutral_load_end_man_tr (int evt){
        switch (evt){
            default:
                return -1;
        }
    }
    //états 3 de chaque machine
    State st_neutral_load_end_av (-1, -1, &shutarm_av, &neutral_end_man_tr);
    State st_neutral_load_end_ar (-1, -1, &shutarm_ar, &neutral_end_man_tr);

//Mouvement de récupération d'un palet au sol
    //début mouvement
    void get_av(){
        AX12As.torqueStatus(6, true); // allumer les bras
        AX12As.moveSpeed(7, MAIN_AV_SSol, HAND_SPEED); // orienter la main
        AX12As.moveSpeed(6, BRAS_AV_SSol, ARM_SPEED_SLOW); // baisser le bras
        ev1.putOff(); // fermer EV
        digitalWrite(POMPE1, HIGH); // allumer pompe avant
        av_hand_content = 1;
    }
    void get_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_SSol, HAND_SPEED); // orienter la main
        AX12As.moveSpeed(4, BRAS_AR_SSol, ARM_SPEED_SLOW); // baisser le bras
        ev2.putOff(); // fermer EV
        digitalWrite(POMPE2, HIGH); // allumer pompe avant
        ar_hand_content = 1;
    }
    //états 4 de chaque machine (retournent à neutre avec charge palet)
    State st_get_av (NEUTRAL_LOAD_START, SSol_DELAY, &get_av, &queue_man_events);
    State st_get_ar (NEUTRAL_LOAD_START, SSol_DELAY, &get_ar, &queue_man_events);

//Mouvement de mise en stockage des palets
    //début mouvement
    void instore_start_av(){
        AX12As.torqueStatus(6, true); // allumer les bras
        AX12As.moveSpeed(7, MAIN_AV_M, HAND_SPEED); // orienter la main
    }
    void instore_start_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_M, HAND_SPEED); // orienter la main
    }
    //états 5 de chaque machine
    State st_instore_start_av (INSTORE_MID, METTRE_DELAY_HAND, &instore_start_av, &queue_man_events);
    State st_instore_start_ar (INSTORE_MID, METTRE_DELAY_HAND, &instore_start_ar, &queue_man_events);

    //intermédiaire mouvement
    void instore_mid_av(){
        AX12As.moveSpeed(6, BRAS_AV_M, ARM_SPEED_SLOW); // baisser le bras
        store_content = av_hand_content;
        av_hand_content = 0;
    }
    void instore_mid_ar(){
        AX12As.moveSpeed(4, BRAS_AR_M, ARM_SPEED_SLOW); // baisser le bras
        store_content = ar_hand_content;
        ar_hand_content = 0;
    }
    //états 6 de chaque machine
    State st_instore_mid_av (INSTORE_END, METTRE_DELAY, &instore_mid_av, &queue_man_events);
    State st_instore_mid_ar (INSTORE_END, METTRE_DELAY, &instore_mid_ar, &queue_man_events);

    //fin mouvement
    void release_av(){
        digitalWrite(POMPE1, LOW); //couper pompe
        ev1.putOn(); //ouvrir ev
    }
    void release_ar(){
        digitalWrite(POMPE2, LOW); //couper pompe
        ev2.putOn(); //ouvrir ev
    }
    //états 7 de chaque machine (retournent à neutre sans charge)
    State st_instore_end_av (NEUTRAL_NOLOAD_START, METTRE_DELAY_RELACHER, &release_av, &queue_man_events);
    State st_instore_end_ar (NEUTRAL_NOLOAD_START, METTRE_DELAY_RELACHER, &release_ar, &queue_man_events);

//Récupération depuis la réserve
    //début mouvement
    void fromstore_start_av(){
        AX12As.torqueStatus(6, true); // allumer les bras
        ev1.putOn(); // fermer EV avant
        AX12As.moveSpeed(6, BRAS_AV_S_PRE, ARM_SPEED_SLOW); // baisser le bras avant
        AX12As.moveSpeed(7, MAIN_AV_S, HAND_SPEED); // orienter la main avant
    }
    void fromstore_start_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        ev2.putOn(); // fermer EV arriere
        AX12As.moveSpeed(4, BRAS_AR_S_PRE, ARM_SPEED_SLOW); // baisser le bras arriere
        AX12As.moveSpeed(5, MAIN_AR_S, HAND_SPEED); // orienter la main arriere
    }
    //états 8 de chaque machine
    State st_fromstore_start_av (FROMSTORE_END, SORTIR_DELAY_MAIN, &fromstore_start_av, &queue_man_events);
    State st_fromstore_start_ar (FROMSTORE_END, SORTIR_DELAY_MAIN, &fromstore_start_ar, &queue_man_events);

    //fin mouvement
    void fromstore_end_av(){
        AX12As.moveSpeed(6, BRAS_AV_S, ARM_SPEED_SLOW); // baisser le bras avant
        digitalWrite(POMPE1, HIGH); // allumer pompe avant
        av_hand_content = store_content;
        store_content = 0;
    }
    void fromstore_end_ar(){
        AX12As.moveSpeed(4, BRAS_AR_S, ARM_SPEED_SLOW); // baisser le bras arriere
        digitalWrite(POMPE2, HIGH); // allumer pompe arriere
        ar_hand_content = store_content;
        store_content = 0;
    }
    //états 9 de chaque machine (retour auto à neutre avec charge)
    State st_fromstore_end_av (NEUTRAL_LOAD_START, SORTIR_DELAY, &fromstore_end_av, &queue_man_events);
    State st_fromstore_end_ar (NEUTRAL_LOAD_START, SORTIR_DELAY, &fromstore_end_ar, &queue_man_events);

//Poser le palet au sol
    //début mouvement
    void put_start_av(){
        AX12As.torqueStatus(6, true); //allumer les bras
        AX12As.moveSpeed(7, MAIN_AV_SSol, HAND_SPEED); //orienter la main
        AX12As.moveSpeed(6, BRAS_AV_SSol, ARM_SPEED_SLOW); //baisser le bras
        av_hand_content = 0;
    }
    void put_start_ar(){
        AX12As.torqueStatus(4, true); //allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_SSol, HAND_SPEED); //orienter la main
        AX12As.moveSpeed(4, BRAS_AR_SSol, ARM_SPEED_SLOW); //baisser le bras
        ar_hand_content = 0;
    }
    //états 10 de chaque machine
    State st_put_start_av (PUT_MID, DSol_DELAY, &put_start_av, &queue_man_events);
    State st_put_start_ar (PUT_MID, DSol_DELAY, &put_start_ar, &queue_man_events);

    //intermédiaire mouvement
    //états 11 de chaque machine
    State st_put_mid_av (PUT_END, DSol_DELAY_RELACHER, &release_av, &queue_man_events);
    State st_put_mid_ar (PUT_END, DSol_DELAY_RELACHER, &release_ar, &queue_man_events);

    //fin mouvement
    void small_lift_arm_av(){
        AX12As.torqueStatus(6, true); //allumer les bras
        AX12As.moveSpeed(6, DSol_SMALL_LIFT_AV, ARM_SPEED_SLOW); //baisser le bras
    }
    void small_lift_arm_ar(){
        AX12As.torqueStatus(4, true); //allumer les bras
        AX12As.moveSpeed(4, DSol_SMALL_LIFT_AR, ARM_SPEED_SLOW); //baisser le bras
    }
    //états 12 de chaque machine (retour auto à neutre sans charge)
    State st_put_end_av (NEUTRAL_NOLOAD_START, DSol_DELAY_LIFT, &small_lift_arm_av, &queue_man_events);
    State st_put_end_ar (NEUTRAL_NOLOAD_START, DSol_DELAY_LIFT, &small_lift_arm_ar, &queue_man_events);



// récupérer la statuette
    //début mouvement
    void getstat_start_av(){ //implémentation av pas prioritaire
        AX12As.torqueStatus(6, true);
        AX12As.moveSpeed(6, GETSTAT_ARM_AV, ARM_SPEED_SLOW);
        AX12As.moveSpeed(7, GETSTAT_HAND_AV, HAND_SPEED);
        digitalWrite(POMPE1, HIGH);
    }
    void getstat_start_ar(){
        AX12As.torqueStatus(4, true);
        AX12As.moveSpeed(4, GETSTAT_ARM_AR, ARM_SPEED_SLOW);
        AX12As.moveSpeed(5, GETSTAT_HAND_AR, HAND_SPEED);
        digitalWrite(POMPE2, HIGH);
    }
    //états 13 de chaque machine
    State st_getstat_start_av(GETSTAT_END, GETSTAT_END_DELAY, &getstat_start_av, &queue_man_events);
    State st_getstat_start_ar(GETSTAT_END, GETSTAT_END_DELAY, &getstat_start_ar, &queue_man_events);

    //fin mouvement
    void getstat_end_av(){ //implémentation av pas prioritaire
        av_hand_content = 2;
    }
    void getstat_end_ar(){
        ar_hand_content = 2;
    }
    //états 14 de chaque machine
    State st_getstat_end_av(NEUTRAL_STAT_START, NEUTRAL_STAT_START_DELAY, &getstat_end_av, &queue_man_events);
    State st_getstat_end_ar(NEUTRAL_STAT_START, NEUTRAL_STAT_START_DELAY, &getstat_end_ar, &queue_man_events);

// position neutre avec statuette
    //début mouvement
    void neutral_stat_start_av(){ //implémentation av pas prioritaire
        AX12As.torqueStatus(6, true);
        AX12As.moveSpeed(6, NEUTRAL_ARM_AV+100, ARM_SPEED_SLOW);
        AX12As.moveSpeed(7, NEUTRAL_HAND_AV, HAND_SPEED);
        digitalWrite(POMPE1, HIGH);
    }
    void neutral_stat_start_ar(){
        AX12As.torqueStatus(4, true);
        AX12As.moveSpeed(4, NEUTRAL_ARM_AR-100, ARM_SPEED_SLOW);
        AX12As.moveSpeed(5, NEUTRAL_HAND_AR, HAND_SPEED);
        digitalWrite(POMPE2, HIGH);
    }
    //états 15 de chaque machine
    State st_neutral_stat_start_av(NEUTRAL_STAT_END, NEUTRAL_STAT_END_DELAY, &neutral_stat_start_av, &queue_man_events);
    State st_neutral_stat_start_ar(NEUTRAL_STAT_END, NEUTRAL_STAT_END_DELAY, &neutral_stat_start_ar, &queue_man_events);

    //fin mouvement
    void neutral_stat_end_av(){ //implémentation av pas prioritaire
        AX12As.moveSpeed(6, NEUTRAL_ARM_AV, ARM_SPEED_SLOW);
    }
    void neutral_stat_end_ar(){
        AX12As.moveSpeed(4, NEUTRAL_ARM_AR, ARM_SPEED_SLOW);
    }
    //états 16 de chaque machine
    State st_neutral_stat_end_ar(-1, -1, &neutral_stat_end_av, &neutral_end_man_tr);
    State st_neutral_stat_end_av(-1, -1, &neutral_stat_end_av, &neutral_end_man_tr);

// poser la statuette
    //début mouvement
    void putstat_start_av(){
        AX12As.torqueStatus(6, true);
        AX12As.moveSpeed(6, PUTSTAT_ARM_AV, ARM_SPEED_FAST);
        AX12As.moveSpeed(7, PUTSTAT_HAND_AV, HAND_SPEED);
        digitalWrite(POMPE1, HIGH);
    }
    void putstat_start_ar(){
        AX12As.torqueStatus(4, true);
        AX12As.moveSpeed(4, PUTSTAT_ARM_AR, ARM_SPEED_FAST);
        AX12As.moveSpeed(5, PUTSTAT_HAND_AR, HAND_SPEED);
        digitalWrite(POMPE2, HIGH);
    }
    //états 17 de chaque machine
    State st_putstat_start_av(PUTSTAT_END, PUTSTAT_END_DELAY, &putstat_start_av, &queue_man_events);
    State st_putstat_start_ar(PUTSTAT_END, PUTSTAT_END_DELAY, &putstat_start_ar, &queue_man_events);

    //fin mouvement
    void putstat_end_av(){
        digitalWrite(POMPE1, LOW);
        ev1.putOn();

    }
    void putstat_end_ar(){
        digitalWrite(POMPE2, LOW);
        ev2.putOn();
    }
    //états 18 de chaque machine
    State st_putstat_end_av(NEUTRAL_NOLOAD_START, NEUTRAL_NOLOAD_START_DELAY, &putstat_end_av, &queue_man_events);
    State st_putstat_end_ar(NEUTRAL_NOLOAD_START, NEUTRAL_NOLOAD_START_DELAY, &putstat_end_ar, &queue_man_events);

// démarrer le match avec la réplique dans la main de devant
    //début mouvement
    void start_repl_hand_av(){
        AX12As.torqueStatus(6, true);
        digitalWrite(POMPE1, HIGH); // allumer pompe avant
    }
    void start_repl_hand_ar(){ // implémentation pas prioritaire
        AX12As.torqueStatus(4, true);
        digitalWrite(POMPE2, HIGH); // allumer pompe arriere
    }
    //états 19 de chaque machine
    State st_start_repl_hand_av(NEUTRAL_STAT_START, START_HAND_DELAY, &start_repl_hand_av, &queue_man_events);
    State st_start_repl_hand_ar(NEUTRAL_STAT_START, START_HAND_DELAY, &start_repl_hand_ar, &queue_man_events);


//machines à états
StateMachine bras_main_pompe_ev_av ({st_neutral_noload_start_av, 
                                     st_neutral_noload_end_av,
                                     st_neutral_load_start_av, 
                                     st_neutral_load_end_av,
                                     st_get_av,
                                     st_instore_start_av,
                                     st_instore_mid_av,
                                     st_instore_end_av,
                                     st_fromstore_start_av,
                                     st_fromstore_end_av,
                                     st_put_start_av,
                                     st_put_mid_av,
                                     st_put_end_av,
                                     st_getstat_start_av,
                                     st_getstat_end_av,
                                     st_neutral_stat_start_av,
                                     st_neutral_stat_end_av,
                                     st_putstat_start_av,
                                     st_putstat_end_av,
                                     st_start_repl_hand_av});
StateMachine bras_main_pompe_ev_ar ({st_neutral_noload_start_ar, 
                                     st_neutral_noload_end_ar,
                                     st_neutral_load_start_ar, 
                                     st_neutral_load_end_ar,
                                     st_get_ar,
                                     st_instore_start_ar,
                                     st_instore_mid_ar,
                                     st_instore_end_ar,
                                     st_fromstore_start_ar,
                                     st_fromstore_end_ar,
                                     st_put_start_ar,
                                     st_put_mid_ar,
                                     st_put_end_ar,
                                     st_getstat_start_ar,
                                     st_getstat_end_ar,
                                     st_neutral_stat_start_ar,
                                     st_neutral_stat_end_ar,
                                     st_putstat_start_ar,
                                     st_putstat_end_ar,
                                     st_start_repl_hand_ar});
