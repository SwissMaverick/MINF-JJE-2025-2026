#ifndef Mc32Gest_RS232_H
#define Mc32Gest_RS232_H
/*--------------------------------------------------------*/
// Mc32Gest_RS232.h
/*--------------------------------------------------------*/
//	Description :	emission et reception spécialisée
//			        pour TP2 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.3
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "GesFifoTh32.h"
#include "gestPWM.h"

/*--------------------------------------------------------*/
// Définition des fonctions prototypes
/*--------------------------------------------------------*/

// prototypes des fonctions
void InitFifoComm(void);
bool GetMessage(S_pwmSettings *pData);
void SendMessage(S_pwmSettings *pData);
bool VerifierVitesse(int8_t valVitesse);
bool VerifierAngle(int8_t valAngle);

// Constantes
#define ANGLE_MAX 90
#define VITESSE_MAX 99
#define AA 0xAA

// Descripteur des fifos
extern S_fifo descrFifoRX;
extern S_fifo descrFifoTX;

#endif
