// Ecole supérieure SL229_MINF TP
// Manipulation Tp3_MenuGen
// Créé le 9 Mai 2006 CHR
// Version 2016  du 03.02.2016
// Modif 2015 : utilisation de stdint.h
// Modif 2016 : ajout Duty pour PWM
// Modif 2018 SCA : suppression PWM et duty
// Definition pour le menuGen

#ifndef DEFMENUGEN_H
#define DEFMENUGEN_H

#include <stdint.h>

#define MAGIC 0x123455AA

#define SINUS "Sinus"
#define TRIANGLE "Triangle"
#define DENTDESCIE "DentDeScie"
#define CARRE "Carre"

#define NUMSINUS 0
#define NUMTRIANGLE 1
#define NUMDENTDESCIE 2
#define NUMCARRE 3



typedef enum 
{ 
    SignalSinus = 0, 
    SignalTriangle, 
    SignalDentDeScie, 
    SignalCarre 
} E_FormesSignal; //32BIT

// Structure des paramètres du générateur
typedef struct {
      E_FormesSignal Forme;
      int16_t Frequence;
      int16_t Amplitude;
      int16_t Offset;
      uint32_t Magic;
} S_ParamGen;

#endif
