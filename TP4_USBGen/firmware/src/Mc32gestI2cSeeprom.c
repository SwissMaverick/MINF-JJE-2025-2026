//--------------------------------------------------------
// Mc32gestI2cEEprom.C
//--------------------------------------------------------
// Gestion I2C de la SEEPROM du MCP79411 (Solution exercice)
//	Description :	Fonctions pour EEPROM MCP79411
//
//	Auteur 		: 	C. HUBER
//      Date            :       26.05.2014
//	Version		:	V1.0
//	Compilateur	:	XC32 V1.31
// Modifications :
//
/*--------------------------------------------------------*/



#include "Mc32gestI2cSeeprom.h"
#include "Mc32_I2cUtilCCS.h"
#include <stdbool.h>




// Definitions du bus (pour mesures)
// #define I2C-SCK  SCL2/RA2      PORTAbits.RA2   pin 58
// #define I2C-SDA  SDa2/RA3      PORTAbits.RA3   pin 59




// Initialisation de la communication I2C et du MCP79411
// ------------------------------------------------

void I2C_InitMCP79411(void)
{
   bool Fast = true;
   i2c_init( Fast );
} //end I2C_InitMCP79411
// Ecriture d'un bloc de donnees dans la SEEPROM du MCP79411
// ---------------------------------------------------------

void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint8_t i = 0;              // Index pour la boucle d'écriture des octets
    uint16_t y = 0;             // Index pour la boucle des pages
    uint8_t *i2cData = (uint8_t*)SrcData; // Cast du pointeur générique en tableau d'octets
    uint8_t NbBytesPage = 0;    // Nombre d'octets à écrire dans la page courante
    
    // Parcours des pages nécessaires à l'écriture
    for(y = 0; y <= (NbBytes/8); y++)
    {
        // Vérifie s'il s'agit de la dernière page à écrire
        if(y == (NbBytes/8))
        {
            // Calcule le nombre d'octets restants pour la dernière page
            NbBytesPage = NbBytes - 8*(y);
        }
        else
        {
            // Définit une page complète de 8 octets
            NbBytesPage = 8;
        }

        // Interrompt la boucle si aucun octet ne doit être écrit
        if (NbBytesPage == 0) {
            break; 
        }

        // Boucle d'attente de disponibilité du composant (ACK Polling)
        do
        {
            i2c_start();
        } while(!i2c_write(MCP79411_EEPROM_W));
        
        // Envoi de l'adresse de destination dans l'EEPROM
        i2c_write((uint8_t)EEpromAddr + (y * 8));
        
        // Boucle d'envoi des octets de données pour la page courante
        for(i = 0; i < NbBytesPage; i++)
        {
           i2c_write(i2cData[i+(y*8)]);
        }
        
        // Génère la condition Stop pour clore la transaction et lancer l'écriture interne
        i2c_stop(); 
    }

} // end I2C_WriteSEEPROM




// Lecture d'un bloc de donnees depuis la SEEPROM du MCP79411
// ----------------------------------------------------------

void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    bool ack;
    uint8_t *pointeur = (uint8_t*)DstData; // Cast du pointeur générique en tableau d'octets de destination
    uint16_t i;                 // Index pour la boucle de lecture des octets

    // Boucle d'attente de disponibilité du composant (ACK Polling)
    do
    {
        i2c_start();
        ack = i2c_write(MCP79411_EEPROM_W);
    } while (ack == false);

    // Envoi de l'adresse de départ de la lecture
    i2c_write(EEpromAddr);
    
    // Génère un Repeated Start pour changer le sens de communication du bus
    i2c_reStart();
    
    // Envoi de l'adresse I2C du composant en mode lecture
    i2c_write(MCP79411_EEPROM_R);
    
    // Boucle de réception des octets de données
    for(i = 0; i < NbBytes; i++)
    {
        // Vérifie s'il s'agit du dernier octet à lire
        if (i == (NbBytes - 1)) 
        {
            // Lecture du dernier octet avec génération d'un NACK (false)
            pointeur[i] = i2c_read(false); 
        } 
        else 
        {
            // Lecture des octets intermédiaires avec génération d'un ACK (true)
            pointeur[i] = i2c_read(true);  
        }
    }

    // Génère la condition Stop pour clore la transaction I2C
    i2c_stop();
    
} // end I2C_ReadSEEPROM