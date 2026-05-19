#ifndef Mc32Gest_SERCOMM_H
#define Mc32Gest_SERCOMM_H
/*--------------------------------------------------------*/
// Mc32Gest_SerComm.h
/*--------------------------------------------------------*/
//	Description :	emission et reception specialisee
//			pour TP4 2015-2016
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.2
//	Compilateur	:	XC32 V1.40 + Harmony 1.06
//
/*--------------------------------------------------------*/

#include <stdint.h>
#include "DefMenuGen.h"

/*--------------------------------------------------------*/
// Prototypes des fonctions 
/*--------------------------------------------------------*/
typedef struct {
            uint8_t Unknown_signal_type : 1;             // événement incrément
            uint8_t Amp_too_big : 1;             // événement décrément
            uint8_t Amp_too_small  : 1;              // événement action OK
            uint8_t off_too_big : 1;             // événement action ESC
            uint8_t off_too_small : 1;             // événement décrément
            uint8_t frequency_too_high  : 1;              // événement action OK
            uint8_t frequency_too_low : 1;             // événement action ESC
} S_Receive_error_type;

void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved);
bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo);
void Init_error_type(void);
void Error_manager(void);

#endif
