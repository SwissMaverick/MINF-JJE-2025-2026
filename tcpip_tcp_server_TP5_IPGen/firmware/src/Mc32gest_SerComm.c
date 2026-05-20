// Mc32Gest_SerComm.C
// fonction d'émission et de réception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "Mc32gest_SerComm.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char check;
// Fonction de reception  d'un  message
// Met à jour les paramètres du generateur a partir du message recu
// Format du message
//  !S=TF=2000A=10000O=+5000D=100W=0#
//  !S=DF=2000A=10000O=-5000D=100W=1#


bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{ 
    
    char *pt_Signal    = NULL;
    char *pt_Frequence = NULL;
    char *pt_Amplitude = NULL;
    char *pt_Offset    = NULL;
    char *pt_Save      = NULL;


    
    
//    //Vérification présence des champs obligatoires
//    if (USBReadBuffer[0] != '!')
//        return false;
//    if (strstr((char *)USBReadBuffer, "S=") == NULL)
//        return false;
//
//    if (strstr((char *)USBReadBuffer, "F=") == NULL)
//        return false;
//
//    if (strstr((char *)USBReadBuffer, "A=") == NULL)
//        return false;
//
//    if (strstr((char *)USBReadBuffer, "O=") == NULL)
//        return false;
//
//    if (strstr((char *)USBReadBuffer, "W=") == NULL)
//        return false;
//    
//    if (strstr((char *)USBReadBuffer, "!") == NULL)
//        return false;

   
    /*Lecture de la chaîne de caractère*/
    
    pt_Signal = strstr((char*)USBReadBuffer, "S=");
    pt_Frequence = strstr((char*)USBReadBuffer, "F=");
    pt_Amplitude = strstr((char*)USBReadBuffer, "A=");
    pt_Offset = strstr((char*)USBReadBuffer, "O=");
    pt_Save = strstr((char*)USBReadBuffer, "W=");
    
//    // controle des parametre
//    if((*pt_Signal != NUMSINUS)|(*pt_Signal != NUMTRIANGLE)|(*pt_Signal != NUMDENTDESCIE)||(*pt_Signal != NUMCARRE))
//        return false;
//    if((*pt_Frequence < FREQ_MIN)&&(*pt_Frequence >FREQ_MAX) && ((*pt_Frequence%INC_FREQ)==ZERO))
//        return false;
//    if((*pt_Amplitude < AMP_MIN)&&(*pt_Amplitude >AMP_MAX) && ((*pt_Amplitude%INC_AMP)==ZERO))
//        return false;
//    if((*pt_Offset < OFFSET_MIN)&&(*pt_Offset >OFFSET_MAX) && ((*pt_Offset%INC_OFFSET)==ZERO))
//        return false;
    
     // récupération des parametre
    if((USBReadBuffer[0] == '!') && (USBReadBuffer[1] == '#'))
    {
        APP_GEN_GetParam(pParam);
        check= '!';
        return true;
    }
    
    // set des parametre
   if(USBReadBuffer[0] == '!')
   {
        switch(*(pt_Signal + 2))
        {
            case 'T':
                pParam->Forme = SignalTriangle;
                break;

            case 'S':
                pParam->Forme = SignalSinus;
                break;

            case 'C':
                pParam->Forme = SignalCarre;
                break;
            
            case 'D':
                pParam->Forme = SignalDentDeScie;
                break;
                
            default:
                break;
        }
        pParam->Frequence = atoi(pt_Frequence + 2);
        pParam->Amplitude = atoi(pt_Amplitude + 2);
        //pParam->Offset = atoi(pt_Offset + 2);
        
        
        char *endPtr;

        /* Décodage de l'offset avec gestion du signe */
        pParam->Offset = (int)strtol(pt_Offset + 2, &endPtr, 10);

        *pt_Save = atoi(pt_Save + 2);
        
        if(*pt_Save == true)
        {
           *SaveTodo = true;
        }
        else
        {
           *SaveTodo = false; 
        }
        check= '!';
        return true;
   }
   else
   {
       check= '?';
       return false;
   }
 
        
    
} // GetMessage


// Fonction d'envoi d'un  message
// Rempli le tampon d'émission pour USB en fonction des paramètres du générateur
// Format du message
// !S=TF=2000A=10000O=+5000D=25WP=0#
// !S=TF=2000A=10000O=+5000D=25WP=1#    // ack sauvegarde



void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved )
{
    
    char pt_Signal;
    
    
    switch(pParam->Forme)
        {
            case SignalTriangle:
                pt_Signal = 'T';
                break;

            case SignalSinus:
                pt_Signal = 'S';
                break;

            case SignalCarre:
                pt_Signal = 'C';
                break;
            
            case SignalDentDeScie:
                pt_Signal = 'D';
                break;
        default:
            break;
        }
    
    
    
    sprintf((char*)USBSendBuffer,"%cS=%cF=%dA=%dO=%+dWP=%d#", check ,pt_Signal, pParam->Frequence, pParam->Amplitude, pParam->Offset, Saved);
} // SendMessage
