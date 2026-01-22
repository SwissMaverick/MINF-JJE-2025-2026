#ifndef GestPWM_H
#define GestPWM_H
/*--------------------------------------------------------*/
// GestPWM.h
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
//  Modification : 1.12.2023 SCA : enleve decl. PWMData extern
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include <math.h>
#include "app.h"
#include "peripheral/oc/plib_oc.h"

/*--------------------------------------------------------*/
// Définition des fonctions prototypes
/*--------------------------------------------------------*/


typedef struct {
    uint8_t absSpeed;    // vitesse 0 à 99
    uint8_t absAngle;    // Angle  0 à 180
    int8_t SpeedSetting; // consigne vitesse -99 à +99
    int8_t AngleSetting; // consigne angle  -90 à +90
} S_pwmSettings;

extern S_pwmSettings pData;
extern S_pwmSettings PWMData;

void GPWM_Initialize(S_pwmSettings *pData);

// Ces 4 fonctions ont pour paramètre un pointeur sur la structure S_pwmSettings.
/*Obtention vitesse et angle*/
void GPWM_GetSettings(S_pwmSettings *pData);
/*Affichage*/
void GPWM_DispSettings(S_pwmSettings *pData, bool Remote);
/*Execution PWM et gestion moteur.*/
void GPWM_ExecPWM(S_pwmSettings *pData);
/*Execution PWM software.*/
void GPWM_ExecPWMSoft(S_pwmSettings *pData);

/*--------------------------------------------------------*/
// Définition des définitions
/*--------------------------------------------------------*/
/*largeur d'impulsion min/(Période/nbr de pas) = 0.6ms/(7ms/35000) = 3000
 * on note 2999 car on compte à partir de 0*/
#define PULSEWIDTHMIN 2999     

/*largeur d'impulsion max/(Période/nbr de pas) = 1.8ms/(7ms/35000) = 9000*/
#define PULSEWIDTHMAX 9000

/*Valeur maximale de l'angle*/
#define ANGLEMAX 180

/*Valeur de la moitié de l'angle maximale*/
#define MOITIEANGLEMAX 90

/*Valeur du taux PWM max*/
#define TAUXPWMMAX 100

/*Definition de la valeur 0 pour évité le Hardcodage*/
#define ZERO 0

/*Nombre de pas de 1% maximum*/
#define NINTYNINE 99

/*Taille moyenne de l'ADC*/
#define TAILLEMOYENNEADC 10  

/*Valeur maximale du Canal 0*/
#define CHAN0MAX 198

/*Valeur maximale du Canal 1*/
#define CHAN1MAX 180

/*Valeur brute maximale de l'ADC*/
#define ADCBRUTEMAX 1023

#endif
