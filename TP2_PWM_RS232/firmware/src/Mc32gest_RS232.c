// Mc32Gest_RS232.C
// Canevas manipulatio TP2 RS232 SLO2 2017-18
// Fonctions d'émission et de réception des message
// CHR 20.12.2016 ajout traitement int. error
// CHR 22.12.2016 evolution des marqueurs observation int. Usart
// SCA 03.01.2018 nettoyé réponse interrupt pour ne laisser que les 3 ifs
// SCA 4.05.2025 modif. GetMessage() pour valeur retour bool

#include <xc.h>
#include <sys/attribs.h>
#include "system_definitions.h"
// Ajout CHR
#include <GenericTypeDefs.h>
#include "app.h"
#include "GesFifoTh32.h"
#include "Mc32gest_RS232.h"
#include "gestPWM.h"
#include "Mc32CalCrc16.h"


typedef union {
        uint16_t val;
        struct {uint8_t lsb;
                uint8_t msb;} shl;
} U_manip16;


// Definition pour les messages
#define MESS_SIZE  5
// avec int8_t besoin -86 au lieu de 0xAA
#define STX_code  (-86)

// Structure décrivant le message
typedef struct {
    uint8_t Start;
    int8_t  Speed;
    int8_t  Angle;
    uint8_t MsbCrc;
    uint8_t LsbCrc;
} StruMess;


// Struct pour émission des messages
StruMess TxMess;
// Struct pour réception des messages
StruMess RxMess;

// Declaration des FIFO pour réception et émission
#define FIFO_RX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages
#define FIFO_TX_SIZE ( (4*MESS_SIZE) + 1)  // 4 messages

int8_t fifoRX[FIFO_RX_SIZE];
// Declaration du descripteur du FIFO de réception
S_fifo descrFifoRX;


int8_t fifoTX[FIFO_TX_SIZE];
// Declaration du descripteur du FIFO d'émission
S_fifo descrFifoTX;


// Initialisation de la communication sérielle
void InitFifoComm(void)
{    
    // Initialisation du fifo de réception
    InitFifo ( &descrFifoRX, FIFO_RX_SIZE, fifoRX, 0 );
    // Initialisation du fifo d'émission
    InitFifo ( &descrFifoTX, FIFO_TX_SIZE, fifoTX, 0 );
    
    // Init RTS 
    RS232_RTS = 1;   // interdit émission par l'autre
   
} // InitComm

//Verif Vitesse
bool VerifierVitesse(int8_t valVitesse)
{
    uint8_t valAbsAngle = 0;
    bool valToReturn = false;
    valAbsAngle = abs(valVitesse);
    if(valAbsAngle > VITESSE_MAX)
    {
        valToReturn = false;
    }
    else
    {
        valToReturn = true;
    }
    return valToReturn;
}

//Verif Angle 
bool VerifierAngle(int8_t valAngle)
{
    uint8_t valAbsAngle = 0;
    int8_t valAngleLocal = 0;
    bool valToReturn = false;
    valAngleLocal = valAngle;
    valAbsAngle = abs(valAngleLocal);
    if(valAbsAngle > ANGLE_MAX)
    {
        valToReturn = false;
    }
    else
    {
        valToReturn = true;
    }
    return valToReturn;
} 

// Valeur de retour false = pas de message reçu donc local (data non modifié)
// Valeur de retour true = message reçu donc en remote (data mis à jour)
bool GetMessage(S_pwmSettings *pData)
{
    bool commStatus = false;
    bool verifVitesse = false, verifAngle = false;
    uint8_t nbChartoRead = 0;
    static uint8_t erreur = 0;
    uint32_t verifCRC = 0xFFFF;
    U_manip16 CRC;
    // Traitement de réception à introduire ICI
    // Lecture et décodage fifo réception
    /*On regarde le nombre de caractères à lire dans la FIFO*/
    nbChartoRead = GetReadSize(&descrFifoRX);
    /*Si le nombre de caractère à lire est plus grand ou 
     *égal à 5.*/
    if(nbChartoRead >= MESS_SIZE)
    {
        /*Récupération du caractère de début du message*/
        GetCharFromFifo(&descrFifoRX, &RxMess.Start);
        /*Vérification si le caractère de début du message est le bon*/
        if(RxMess.Start == AA)
        {
            /*Récupération des caractères de vitesse, angle et 
             *du CRC (MSB puis LSB)*/
            GetCharFromFifo(&descrFifoRX, &RxMess.Speed);
            GetCharFromFifo(&descrFifoRX, &RxMess.Angle);
            GetCharFromFifo(&descrFifoRX, &RxMess.MsbCrc);
            GetCharFromFifo(&descrFifoRX, &RxMess.LsbCrc);
            
            /*Calcul de la valeur du CRC*/
            CRC.shl.lsb = RxMess.LsbCrc;
            CRC.shl.msb = RxMess.MsbCrc;
            
            /*Calcul du CRC avec les valeurs les valeurs Start, Vitesse
             et Angle*/
            verifCRC = updateCRC16(verifCRC, RxMess.Start);
            verifCRC = updateCRC16(verifCRC, RxMess.Speed);
            verifCRC = updateCRC16(verifCRC, RxMess.Angle);
            
            /*Si la valeur du CRC calculer est la même que celle du CRC reçu*/
            if(verifCRC == CRC.val)
            {
                LED6_W = 1;
                /*Vérification que la valeur de la vitesse ne 
                 *dépasse pas -99 ou +99*/
                verifVitesse = VerifierVitesse(RxMess.Speed);
                /*Vérification que la valeur de l'angle ne 
                 *dépasse pas -90 ou +90*/
                verifAngle = VerifierAngle(RxMess.Angle);
                
                /*Si les vérifications des valeurs Vitesse et Angle sont bons*/
                if((verifVitesse == true) && (verifAngle == true))
                {
                    /*Mise à jour du paramètre de la vitesse*/
                    pData->SpeedSetting = RxMess.Speed;
                    /*Calcul de la valeur absolue de la vitesse,
                     *mise à jour du paramètre de la vitesse en valeur absolue*/
                    pData->absSpeed = abs(RxMess.Speed);
                    /*Mise à jour du paramètre de l'angle*/
                    pData->AngleSetting = RxMess.Angle;
                    /*Calcul de la valeur absolue de l'angle,
                     *mise à jour du paramètre de l'angle en valeur absolue*/
                    pData->absAngle = abs(RxMess.Angle);
                    /*Remise à 0 du compteur d'erreur*/
                    erreur = 0;
                }
                else
                {
                    erreur ++;
                }
            }
            else
            {
                LED6_W = 0;
                erreur ++;
            }
        }
        else
        {
            erreur ++;
        }
    }
    else
    {
        erreur ++;
    }
    
    if(erreur >= 10)
    {
        commStatus = false;
        if(erreur > 20)
        {
            erreur = 10;
        }
    }
    else
    {
        commStatus = true;
    }

    // Gestion controle de flux de la réception
    if(GetWriteSpace ( &descrFifoRX) >= (2*MESS_SIZE)) {
        // autorise émission par l'autre
        RS232_RTS = 0;
    }
    return commStatus;
} // GetMessage

// Fonction d'envoi des messages, appel cyclique
void SendMessage(S_pwmSettings *pData)
{
    int8_t freeSize;
    
    // Traitement émission à introduire ICI
    // Formatage message et remplissage fifo émission
    // Test si place pour écrire 1 message
    freeSize = GetWriteSpace(&descrFifoTX);
    if(freeSize >= MESS_SIZE)
    {
        // Compose le message (Start)
        TxMess.Start = 0xAA;
                
        // Compose le message (Speed)
        TxMess.Speed = pData->SpeedSetting;
                
        // Compose le message (Angle)
        TxMess.Angle = pData->AngleSetting;
        
        //Calcul CRC
        uint16_t valCRC16 = 0xFFFF;
        valCRC16 = updateCRC16(valCRC16, 0xAA);
        valCRC16 = updateCRC16(valCRC16, pData->SpeedSetting);
        valCRC16 = updateCRC16(valCRC16, pData->AngleSetting);
        
        //Séparation de ValCrc16 en 2 bytes
        uint8_t valCRC_Byte_1; //Byte MSB (envoyé en premier)
        uint8_t valCRC_Byte_2; //Byte LBS (envoyé en dernier)
        
        valCRC_Byte_1 = (uint8_t)(valCRC16 >> 8);
        valCRC_Byte_2 = (uint8_t)(valCRC16 & 0x00FF);
        
        // Compose le message (MsbCrc)
        TxMess.MsbCrc = valCRC_Byte_1;
        
        // Compose le message (LsbCrc)
        TxMess.LsbCrc = valCRC_Byte_2;
        
        // Dépose le message dans le FIFO (Start)
        PutCharInFifo(&descrFifoTX, TxMess.Start);
        // Dépose le message dans le FIFO (Speed)
        PutCharInFifo(&descrFifoTX, TxMess.Speed);
        // Dépose le message dans le FIFO (Angle)
        PutCharInFifo(&descrFifoTX, TxMess.Angle);
        // Dépose le message dans le FIFO (LSBCRC)
        PutCharInFifo(&descrFifoTX, TxMess.MsbCrc);
        // Dépose le message dans le FIFO (MSBCRC)
        PutCharInFifo(&descrFifoTX, TxMess.LsbCrc);
        
    }
    
    
    // Gestion du controle de flux
    // si on a un caractère à envoyer et que CTS = 0
    freeSize = GetReadSize(&descrFifoTX);
    if ((RS232_CTS == 0) && (freeSize > 0))
    {
        // Autorise int. émission    
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);                
    }
}


// Interruption USART1
// !!!!!!!!
// Attention ne pas oublier de supprimer la réponse générée dans system_interrupt
// !!!!!!!!
 void __ISR(_UART_1_VECTOR, ipl5AUTO) _IntHandlerDrvUsartInstance0(void)
{
    USART_ERROR UsartStatus;    

    uint8_t freeSize, TXsize;
    int8_t dataChar;
    int8_t i_cts = 0;
    BOOL TxBuffFull;

    // Marque début interruption avec Led3
    LED3_W = 1;
    
    // Is this an Error interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_ERROR) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_ERROR) ) {
        /* Clear pending interrupt */
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_ERROR);
        // Traitement de l'erreur à la réception.
    }
   

    // Is this an RX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_RECEIVE) ) {

        // Oui Test si erreur parité ou overrun
        UsartStatus = PLIB_USART_ErrorsGet(USART_ID_1);

        if ( (UsartStatus & (USART_ERROR_PARITY |
                             USART_ERROR_FRAMING | USART_ERROR_RECEIVER_OVERRUN)) == 0) {

            // Traitement RX à faire ICI
            // Lecture des caractères depuis le buffer HW -> fifo SW
            //  (pour savoir s'il y a une data dans le buffer HW RX : PLIB_USART_ReceiverDataIsAvailable())
			//  (Lecture via fonction PLIB_USART_ReceiverByteReceive())
            while (PLIB_USART_ReceiverDataIsAvailable(USART_ID_1))
            {
                dataChar = PLIB_USART_ReceiverByteReceive(USART_ID_1);
                
                PutCharInFifo(&descrFifoRX, dataChar);
            }
			                      
            LED4_W = !LED4_R; // Toggle Led4
            // buffer is empty, clear interrupt flag
            PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
        } else {
            // Suppression des erreurs
            // La lecture des erreurs les efface sauf pour overrun
            if ( (UsartStatus & USART_ERROR_RECEIVER_OVERRUN) == USART_ERROR_RECEIVER_OVERRUN) {
                   PLIB_USART_ReceiverOverrunErrorClear(USART_ID_1);
            }
        }

        
        // Traitement controle de flux reception à faire ICI
        // Gerer sortie RS232_RTS en fonction de place dispo dans fifo reception
        freeSize = GetWriteSpace(&descrFifoRX);
        // A cause du cas un int pour 6 char 3/4 de 8 = 6
        if(freeSize <= 6)
        {
            // Contrôle de flux : demande stop émission
            RS232_RTS = 1;
        }

        
    } // end if RX

    
    // Is this an TX interrupt ?
    if ( PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) &&
                 PLIB_INT_SourceIsEnabled(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT) ) {

        // Traitement TX à faire ICI
        // Envoi des caractères depuis le fifo SW -> buffer HW
            
        // Avant d'émettre, on vérifie 3 conditions :
        //  Si CTS = 0 autorisation d'émettre (entrée RS232_CTS)
        //  S'il y a un caratères à émettre dans le fifo
        //  S'il y a de la place dans le buffer d'émission (PLIB_USART_TransmitterBufferIsFull)
        //   (envoi avec PLIB_USART_TransmitterByteSend())
        TXsize = GetReadSize(&descrFifoTX); //Sondage FIFO TX
        
        i_cts = RS232_CTS; //Sondage pin CTS
        
        TxBuffFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1); //Sondage buffer TX
        
        if((i_cts == 0) && (TXsize > 0) && (TxBuffFull == false))
        {
            do
            {
                GetCharFromFifo(&descrFifoTX, &dataChar);
                PLIB_USART_TransmitterByteSend(USART_ID_1, dataChar);
                
                i_cts = RS232_CTS;
                TXsize = GetReadSize(&descrFifoTX);
                TxBuffFull = PLIB_USART_TransmitterBufferIsFull(USART_ID_1);
            } while((i_cts == 0) && (TXsize > 0) && (TxBuffFull == false));
        }
	   
        LED5_W = !LED5_R; // Toggle Led5
		
        // disable TX interrupt (pour éviter une interrupt. inutile si plus rien à transmettre)
        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
        
        // Clear the TX interrupt Flag (Seulement apres TX) 
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
    }
    // Marque fin interruption avec Led3
    LED3_W = 0;
 }