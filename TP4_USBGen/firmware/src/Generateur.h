#ifndef Generateur_h
#define Generateur_h

// TP3 MenuGen 2016
// C. HUBER  03.02.2016
// Fichier Generateur.h
// Prototypes des fonctions du générateur  de signal

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "DefMenuGen.h"
#define TAILLE_TABLEAU_MAX 100
// Initialisation du  générateur
void  GENSIG_Initialize(S_ParamGen *pParam);


// Mise à jour de la periode d'échantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam);

uint32_t VoltageToDAC(float V_mV);
// Mise à jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam);

// A appeler dans int Timer3
void  GENSIG_Execute(void);

void GENSIG_Calcul_Sinus(uint32_t *tabl, uint8_t taillemax,S_ParamGen *pParam);
void GENSIG_Calcul_Carre(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam);
void GENSIG_Calcul_Triangle(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam);
void GENSIG_Calcul_DentDeScie(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam);

#endif