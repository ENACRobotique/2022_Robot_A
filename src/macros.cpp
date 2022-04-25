#include "macros.h"

//Etat neutre des bras sans charge transportée
    //début mouvement
    void neutral_noload_start_av(){
        AX12As.torqueStatus(6, true); //allumer bras
        AX12As.moveSpeed(6, BRAS_AV_N, 200); // relever le bras en position plus normale
        AX12As.moveSpeed(7, MAIN_AV_N, 400); // orienter main en position de sortie
    }
    void neutral_noload_start_ar(){
        AX12As.torqueStatus(4, true); //allumer bras
        AX12As.moveSpeed(4, BRAS_AR_N, 200); // relever le bras en position plus normale
        AX12As.moveSpeed(5, MAIN_AR_N, 400); // orienter main en position de sortie
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
        AX12As.moveSpeed(6, BRAS_AV_N_P, 200); // relever le bras en position plus normale
        AX12As.moveSpeed(7, MAIN_AV_P_N, 400); // orienter main en position de sortie
    }
    void neutral_load_start_ar(){
        AX12As.torqueStatus(4, true); //allumer bras
        AX12As.moveSpeed(4, BRAS_AR_N_P, 200); // relever le bras en position plus normale
        AX12As.moveSpeed(5, MAIN_AR_P_N, 400); // orienter main en position de sortie
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
        AX12As.moveSpeed(7, MAIN_AV_SSol, 400); // orienter la main
        AX12As.moveSpeed(6, BRAS_AV_SSol, 150); // baisser le bras
        ev1.putOff(); // fermer EV
        digitalWrite(POMPE1, HIGH); // allumer pompe avant
    }
    void get_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_SSol, 400); // orienter la main
        AX12As.moveSpeed(4, BRAS_AR_SSol, 150); // baisser le bras
        ev2.putOff(); // fermer EV
        digitalWrite(POMPE2, HIGH); // allumer pompe avant
    }
    //états 4 de chaque machine (retournent à neutre avec charge palet)
    State st_get_av (NEUTRAL_LOAD_START, SSol_DELAY, &get_av, &queue_man_events);
    State st_get_ar (NEUTRAL_LOAD_START, SSol_DELAY, &get_ar, &queue_man_events);

//Mouvement de mise en stockage des palets
    //début mouvement
    void instore_start_av(){
        AX12As.torqueStatus(6, true); // allumer les bras
        AX12As.moveSpeed(7, MAIN_AV_M, 400); // orienter la main
    }
    void instore_start_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_M, 400); // orienter la main
    }
    //états 5 de chaque machine
    State st_instore_start_av (INSTORE_MID, METTRE_DELAY_HAND, &instore_start_av, &queue_man_events);
    State st_instore_start_ar (INSTORE_MID, METTRE_DELAY_HAND, &instore_start_ar, &queue_man_events);

    //intermédiaire mouvement
    void instore_mid_av(){
        AX12As.moveSpeed(6, BRAS_AV_M, 150); // baisser le bras
    }
    void instore_mid_ar(){
        AX12As.moveSpeed(4, BRAS_AR_M, 150); // baisser le bras
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
        AX12As.moveSpeed(6, BRAS_AV_S_PRE, 150); // baisser le bras avant
        AX12As.moveSpeed(7, MAIN_AV_S, 400); // orienter la main avant
    }
    void fromstore_start_ar(){
        AX12As.torqueStatus(4, true); // allumer les bras
        ev2.putOn(); // fermer EV avant
        AX12As.moveSpeed(4, BRAS_AR_S_PRE, 150); // baisser le bras avant
        AX12As.moveSpeed(5, MAIN_AR_S, 400); // orienter la main avant
    }
    //états 8 de chaque machine
    State st_fromstore_start_av (FROMSTORE_END, SORTIR_DELAY_MAIN, &fromstore_start_av, &queue_man_events);
    State st_fromstore_start_ar (FROMSTORE_END, SORTIR_DELAY_MAIN, &fromstore_start_ar, &queue_man_events);

    //fin mouvement
    void fromstore_end_av(){
        AX12As.moveSpeed(6, BRAS_AV_S, 150); // baisser le bras avant
        digitalWrite(POMPE1, HIGH); // allumer pompe avant
    }
    void fromstore_end_ar(){
        AX12As.moveSpeed(4, BRAS_AR_S, 150); // baisser le bras avant
        digitalWrite(POMPE2, HIGH); // allumer pompe avant
    }
    //états 9 de chaque machine (retour auto à neutre avec charge)
    State st_fromstore_end_av (NEUTRAL_LOAD_START, SORTIR_DELAY, &fromstore_end_av, &queue_man_events);
    State st_fromstore_end_ar (NEUTRAL_LOAD_START, SORTIR_DELAY, &fromstore_end_ar, &queue_man_events);

//Poser le palet au sol
    //début mouvement
    void put_start_av(){
        AX12As.torqueStatus(6, true); //allumer les bras
        AX12As.moveSpeed(7, MAIN_AV_SSol, 400); //orienter la main
        AX12As.moveSpeed(6, BRAS_AV_SSol, 150); //baisser le bras
    }
    void put_start_ar(){
        AX12As.torqueStatus(4, true); //allumer les bras
        AX12As.moveSpeed(5, MAIN_AR_SSol, 400); //orienter la main
        AX12As.moveSpeed(4, BRAS_AR_SSol, 150); //baisser le bras
    }
    //états 10 de chaque machine
    State st_put_start_av (PUT_END, DSol_DELAY, &put_start_av, &queue_man_events);
    State st_put_start_ar (PUT_END, DSol_DELAY, &put_start_ar, &queue_man_events);

    //fin mouvement
    //états 11 de chaque machine (retour auto à neutre sans charge)
    State st_put_end_av (NEUTRAL_NOLOAD_START, DSol_DELAY_RELACHER, &release_av, &queue_man_events);
    State st_put_end_ar (NEUTRAL_NOLOAD_START, DSol_DELAY_RELACHER, &release_ar, &queue_man_events);

