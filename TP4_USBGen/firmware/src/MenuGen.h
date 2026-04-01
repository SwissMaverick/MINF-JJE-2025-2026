#ifndef MenuGen_h
#define MenuGen_h

// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  03.02.2016
// Fichier MenuGen.h
// Gestion du menu  du générateur
// Traitement cyclique à 1 ms du Pec12


#include <stdbool.h>
#include <stdint.h>
#include "DefMenuGen.h"


void MENU_Initialize(S_ParamGen *pParam);


void MENU_Execute(S_ParamGen *pParam, bool local);

//Machines d'état
#define SELECT 0
#define EDIT 1
#define AFFICHAGE 2
#define FORME 3
#define FREQUENCE 4
#define AMPLITUDE 5
#define OFFSET 6
#define SAUVEGARDE_DEMANDE 7
#define SAUVEGARDE_MESSAGE 8

//Valeurs min et max
#define VALFREQMAX 2000
#define VALFREQMIN 20

#define VALAMPLMAX 10000
#define VALAMPLMIN 0

#define VALOFFSETMAX 10000 //Cas spécial : l'offset min est à -5000
#define VALOFFSETMIN 0  //Ajout d'une addition de +5000 pour éviter les -
#define VALASOUSTRAIRE 5000

#endif




  
   







