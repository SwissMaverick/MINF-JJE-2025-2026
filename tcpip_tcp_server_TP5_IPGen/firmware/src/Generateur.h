#ifndef Generateur_h
#define Generateur_h

// TP3 MenuGen 2016
// C. HUBER  03.02.2016
// Fichier Generateur.h
// Prototypes des fonctions du generateur  de signal

#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "DefMenuGen.h"
// Moitier de la valeur maximale DAC
#define DAC_HALF_RES_MAX 32767
#define DAC_RES_MAX 65536
#define DAC_CH0 0

#define AMPL_MAX 10000

// Nombre total d'echantillons utilises pour une periode
#define ECH_MAX 100
#define ECH_TROIS_QUARTS 75
#define ECH_HALF 50
#define ECH_UN_QUARTS 25
#define ECH_START 0

//valeurs par defauts
#define  VAL_DEFAUT_FREQ  20
#define  VAL_DEFAUT_AMPL   1000
#define  VAL_DEFAUT_OFFSET   0


// Structure definissant les parametres d'amplitude
typedef struct {
    uint16_t amplTic;         // Nombre de tics correspondant a l'amplitude
    uint16_t amplMin;      // Valeur minimale du signal
    uint16_t amplMax;      // Valeur maximale du signal
} S_Amplitude;

//// Structure definissant les parametres d'amplitude
//typedef struct {
//    uint16_t Nb_Tic;         // Nombre de tics correspondant a l'amplitude
//    uint16_t Min;      // Valeur minimale du signal
//    uint16_t Max;      // Valeur maximale du signal
//} S_Amplitude;

// Initialise les parametres du generateur
void GENSIG_Initialize(S_ParamGen *pParam);

// Met a jour la periode d'echantillonnage selon la frequence
void GENSIG_UpdatePeriode(S_ParamGen *pParam);

// Met a jour les valeurs du signal (forme, amplitude, offset)
void GENSIG_UpdateSignal(S_ParamGen *pParam);

// Fonction appelee dans l'interruption du Timer3 pour generer le signal
void GENSIG_Execute(void);

#endif
