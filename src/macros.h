#ifndef __MACROS__
#define __MACROS__

#include "config.h"
#include <Arduino.h>
#include "AX12A.h"
#include "elecvannes.h"

const int POS_BRAS_AVANT_NEUTRE = 400;
const int POS_BRAS_ARRIERE_NEUTRE = 400;

const int POS_MAIN_AVANT_NEUTRE = 400;
const int POS_MAIN_ARRIERE_NEUTRE = 400;

const int POS_MAIN_AVANT_SAISIR = 400;
const int POS_BRAS_AVANT_SAISIR = 400;
const int AVANT_SAISIR_DELAY = 100;
void saisirPaletAvant();

const int POS_MAIN_ARRIERE_SAISIR = 400;
const int POS_BRAS_ARRIERE_SAISIR = 400;
const int ARRIERE_SAISIR_DELAY = 100;
void saisirPaletArriere();

const int POS_MAIN_AVANT_METTRE = 400;
const int POS_BRAS_AVANT_METTRE = 400;
const int AVANT_METTRE_DELAY = 100;
void mettrePaletAvant();

const int POS_MAIN_ARRIERE_METTRE = 400;
const int POS_BRAS_ARRIERE_METTRE = 400;
const int ARRIERE_METTRE_DELAY = 100;
void mettrePaletArriere();

const int POS_MAIN_AVANT_SORTIR = 400;
const int POS_BRAS_AVANT_SORTIR = 400;
const int AVANT_SORTIR_DELAY = 100;
void sortirPaletAvant();

const int POS_MAIN_ARRIERE_SORTIR = 400;
const int POS_BRAS_ARRIERE_SORTIR = 400;
const int ARRIERE_SORTIR_DELAY = 100;
void sortirPaletArriere();


#endif //__MACROS__