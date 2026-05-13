// Mc32Gest_SerComm.C
// fonction d'émission et de réception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "Mc32gest_SerComm.h"
#include "Mc32gestI2cSeeprom.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Fonction de reception  d'un  message
// Met à jour les paramètres du generateur a partir du message recu
// Format du message
//  !S=TF=2000A=10000O=+5000D=100W=0#
//  !S=PF=2000A=10000O=-5000D=100W=1#


bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{
    //Déclaration de variables
    char *pt_Forme = 0;
    char *pt_Frequence = 0;
    char *pt_Amplitude = 0;
    char *pt_Offset = 0;
    char *pt_Sauvegarde = 0;

    // Recherche des différents paramètres dans le buffer reçu
    pt_Forme = strstr((char*) USBReadBuffer, "S");
    pt_Frequence = strstr((char*) USBReadBuffer, "F");
    pt_Amplitude = strstr((char*) USBReadBuffer, "A");
    pt_Offset = strstr((char*) USBReadBuffer, "O");
    pt_Sauvegarde = strstr((char*) USBReadBuffer, "W");

    // Vérifie si le message commence par '!'
    if (USBReadBuffer[0] == '!') // On peut remplacer '!' par une constante définie
    {
        // Identification de la forme du signal
        switch (pt_Forme[2])
        {
            case 'T':
                pParam->Forme = Triangle;
                break;
            case 'S':
                pParam->Forme = Sinus;
                break;
            case 'C':
                pParam->Forme = Carre;
                break;
            case 'D':
                pParam->Forme = DentDeScie;
                break;
            default:
                break;
        }

        // Mise à jour des paramètres à partir du message reçu
        pParam->Frequence = atoi(pt_Frequence + 2); // Décalage de 2 pour ignorer 'F='
        pParam->Amplitude = atoi(pt_Amplitude + 2); // Décalage de 2 pour ignorer 'A='
        pParam->Offset = atoi(pt_Offset + 2); // Décalage de 2 pour ignorer 'O='
        *SaveTodo = atoi(pt_Sauvegarde + 2); // Décalage de 2 pour ignorer 'W='

        // Si la sauvegarde est demandée, écrire les paramètres dans la EEPROM
        if (*SaveTodo) {
            I2C_WriteSEEPROM((uint32_t*) pParam, MCP79411_EEPROM_BEG , sizeof (S_ParamGen));
        }

        return true; //La lecture a aboutie  
    } else {
        return false; //La lecture n'a pas aboutie
    }
} // GetMessage


// Fonction d'envoi d'un  message
// Rempli le tampon d'émission pour USB en fonction des paramètres du générateur
// Format du message
// !S=TF=2000A=10000O=+5000D=25WP=0#
// !S=TF=2000A=10000O=+5000D=25WP=1#    // ack sauvegarde



void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved )
{
    char *indiceFormeEnvoie;

    // Détermine la forme du signal à envoyer
    switch (pParam->Forme) {
        case Triangle:
            indiceFormeEnvoie = "T";
            break;
        case Sinus:
            indiceFormeEnvoie = "S";
            break;
        case Carre:
            indiceFormeEnvoie = "C";
            break;
        case DentDeScie:
            indiceFormeEnvoie = "D";
            break;
        default:
            break;
    }

    // Formate le message à envoyer avec les paramètres du générateur
    sprintf((char*) USBSendBuffer, "!S=%sF=%dA=%dO=%+dWP=%d#", indiceFormeEnvoie, pParam->Frequence, pParam->Amplitude, pParam->Offset, Saved);

} // SendMessage
