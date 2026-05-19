// Mc32Gest_SerComm.C
// fonction d'émission et de réception des message
// transmis en USB CDC
// Canevas TP4 SLO2 2015-2015


#include "app.h"
#include "app_generator.h"
#include "Mc32gest_SerComm.h"
#include "Mc32DriverLcd.h"
#include "MenuGen.h"
#include "Mc32gestI2cSeeprom.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern APP_GENERATOR_DATA app_generatorData;
extern APP_DATA appData;
// Fonction de reception  d'un  message
// Met à jour les paramètres du generateur a partir du message recu
// Format du message
//  !S=TF=2000A=10000O=+5000D=100W=0#
//  !S=PF=2000A=10000O=-5000D=100W=1#

 S_Receive_error_type Get_message_error;
 
void Init_error_type(void){
    Get_message_error.Amp_too_big = 0;
    Get_message_error.Amp_too_small = 0;
    Get_message_error.Unknown_signal_type = 0;
    Get_message_error.frequency_too_high = 0;
    Get_message_error.frequency_too_low = 0;
    Get_message_error.off_too_big = 0;
    Get_message_error.off_too_small = 0;
}
bool GetMessage(int8_t *USBReadBuffer, S_ParamGen *pParam, bool *SaveTodo)
{
    uint8_t index;
    uint8_t validation = 0;
    uint8_t start_signal= 0;
    uint8_t start_frequence= 0;
    uint8_t start_amplitude= 0;
    uint8_t start_offset= 0;
    uint8_t offset_signe= 0;
    uint8_t start_sauvegarde= 0;
    bool first_S_found = false;
    int32_t var = 0;
    char buffer[10];
    //lecture et premiere validation de la trame
    if(USBReadBuffer[0] =='!'){
        for(index = 0; index <= appData.numBytesRead; index++){
            if(USBReadBuffer[index] == '#'){
                validation = 1;
            }
        }
    }
    else{
        lcd_gotoxy(1,4);
        printf_lcd("trame invalide debut");
    }
    
    if(validation == 1){
        validation = 0;
        for(index = 0; index <= appData.numBytesRead; index++){
            if(USBReadBuffer[index] == 'S' && first_S_found == false){
                start_signal = index +2;
                first_S_found = true;
                USBReadBuffer[index] = '\0';
            }
            else if(USBReadBuffer[index] == 'F'){
                start_frequence = index +2;
                USBReadBuffer[index] = '\0';
            }
            else if(USBReadBuffer[index] == 'A'){
                start_amplitude = index +2;
                USBReadBuffer[index] = '\0';
            }
            else if(USBReadBuffer[index] == 'O'){
                start_offset = index +2;
                USBReadBuffer[index] = '\0';
            }
            else if(USBReadBuffer[index] == 'W'){
                start_sauvegarde = index +2;
                USBReadBuffer[index] = '\0';
            }
        }

        switch (USBReadBuffer[start_signal]) {
            case 'T':
                pParam->Forme = 1;
                break;
            case 'S':
                pParam->Forme = 0;
                break;
            case 'C':
                pParam->Forme = 3;
                break;
            case 'D':
                pParam->Forme = 2;
                break;
            default:
                Get_message_error.Unknown_signal_type = 1;
                break;
        }
        

        var = atoi(&USBReadBuffer[start_frequence]);
        if(var > 2000){
            pParam->Frequence = 2000 ;
            Get_message_error.frequency_too_high = 1;
        }
        else if(var < 20){
            pParam->Frequence = 20 ;
            Get_message_error.frequency_too_low = 1;
        }
        else{
        pParam->Frequence = var;
        }

        var = atoi(&USBReadBuffer[start_amplitude]);
        if(var > 10000){
            pParam->Amplitude = 10000 ;
            Get_message_error.Amp_too_big = 1;
        }
        else if(var < 100){
            pParam->Amplitude = 100 ;
            Get_message_error.Amp_too_small = 1;
        }
        else{
        pParam->Amplitude = var;
        }

        var = atoi(&USBReadBuffer[start_offset]);
        if(var > 5000){
            pParam->Offset = 5000 ;
            Get_message_error.off_too_big = 1;
        }
        else if(var < -5000){
            pParam->Offset = -5000 ;
            Get_message_error.off_too_small = 1;
        }
        else{
        pParam->Offset = var;
        }
        
        var = atoi(&USBReadBuffer[start_sauvegarde]);
        if(var == 0){
            *SaveTodo = false;
        }
        else{
            *SaveTodo = true;
            //I2C_WriteSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
            MENU_DemandeSave();
        }
        //Error_manager();
    }
    else{
        lcd_gotoxy(1,4);
        printf_lcd("trame invalide fin");
    }
    return 1;
} // GetMessage


// Fonction d'envoi d'un  message
// Rempli le tampon d'émission pour USB en fonction des paramètres du générateur
// Format du message
// !S=TF=2000A=10000O=+5000D=25WP=0#
// !S=TF=2000A=10000O=+5000D=25WP=1#    // ack sauvegarde



void SendMessage(int8_t *USBSendBuffer, S_ParamGen *pParam, bool Saved )
{
    uint8_t index;

    uint8_t start_sauvegarde= 0;
    int32_t var = 0;
    for(index = 0; index <= appData.numBytesRead; index++){
        if(USBSendBuffer[index] == 'W'){
            start_sauvegarde = index ;
        }
    }
    USBSendBuffer[start_sauvegarde+4] = USBSendBuffer[start_sauvegarde+3];
    USBSendBuffer[start_sauvegarde+3] = USBSendBuffer[start_sauvegarde+2];
    USBSendBuffer[start_sauvegarde+2] = USBSendBuffer[start_sauvegarde+1];
    USBSendBuffer[start_sauvegarde+1] = 'P';
    
    USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                        &appData.writeTransferHandle,
                        USBSendBuffer, appData.numBytesRead+1,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
} // SendMessage

void Error_manager(void) {
    // Déclaration du buffer. 
    // 256 octets permettent de stocker plusieurs messages d'erreur à la suite.
    char USBSendBuffer[256]; 
    int msg_len = 0;

    // Initialisation du buffer
    USBSendBuffer[0] = '\0';

    // Construction du message avec des retours à la ligne (\n)
    if (Get_message_error.Unknown_signal_type) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Type de signal inconnu\n");
    }
    if (Get_message_error.Amp_too_big) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Amplitude trop grande\n");
    }
    if (Get_message_error.Amp_too_small) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Amplitude trop petite\n");
    }
    if (Get_message_error.off_too_big) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Offset trop grand\n");
    }
    if (Get_message_error.off_too_small) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Offset trop petit\n");
    }
    if (Get_message_error.frequency_too_high) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Frequence trop haute\n");
    }
    if (Get_message_error.frequency_too_low) {
        msg_len += snprintf(USBSendBuffer + msg_len, sizeof(USBSendBuffer) - msg_len, "ERR: Frequence trop basse\n");
    }

    // Envoi si au moins une erreur a été détectée
    if (msg_len > 0) {
        USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                             &appData.writeTransferHandle,
                             USBSendBuffer, 
                             msg_len,
                             USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
    }
    
    Get_message_error.Amp_too_big = 0;
    Get_message_error.Amp_too_small = 0;
    Get_message_error.Unknown_signal_type = 0;
    Get_message_error.frequency_too_high = 0;
    Get_message_error.frequency_too_low = 0;
    Get_message_error.off_too_big = 0;
    Get_message_error.off_too_small = 0;
}