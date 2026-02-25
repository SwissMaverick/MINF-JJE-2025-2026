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


void MENU_Execute(S_ParamGen *pParam);

#define ASTERISQUE 0
#define AFFICHAGE 1
#define FORME 2
#define FREQUENCE 3
#define AMPLITUDE 4
#define OFFSET 5

#endif




  
   







