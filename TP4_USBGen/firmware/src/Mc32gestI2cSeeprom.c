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


// Définition pour MCP79411
#define MCP79411_EEPROM_R    0xAF         // MCP79411 address for read
#define MCP79411_EEPROM_W    0xAE         // MCP79411 address for write
// La EEPROM du 79411 est de 1 Kbits donc 128 octets
#define MCP79411_EEPROM_BEG   0x00         // addr. début EEPROM
#define MCP79411_EEPROM_END   0x7F         // addr. fin EEPROM
#define MCP79411_PAGE_SIZE    8            // Taille d'une page EEPROM

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

// Ecriture d'un bloc dans l'EEPROM du MCP79411 
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    bool ack;
    uint8_t i = 0;
    uint16_t y = 0;
    uint8_t *pointeur = (uint8_t*)SrcData; // Pointeur qui prend l'adresse de SrcData pour le prendre comme un tableau
    uint8_t NbBytesPage = 0;
    uint16_t timeout = 0;
    uint32_t current_addr;
    uint8_t espaceRestant;
    
    for(y = 0; y < NbBytes;)
    {
        current_addr = EEpromAddr + y;
        
        espaceRestant = MCP79411_PAGE_SIZE - (current_addr % MCP79411_PAGE_SIZE);
        
        if((NbBytes - y) < espaceRestant)
        {
            NbBytesPage = NbBytes - y;
        }
        else
        {
            NbBytesPage = espaceRestant;
        }
        
        ack = false;
        timeout = 0;
        
        do
        {
            i2c_start();
            ack = i2c_write(MCP79411_EEPROM_W);
            
            if(ack == false)
            {
                i2c_stop();
            }
            
            timeout++;
            if(timeout > 1000) return;
            
        } while (ack == false);
        
        i2c_write((uint8_t)current_addr);
        
        for(i = 0; i < NbBytesPage; i++)
        {
            i2c_write(pointeur[y + i]);
        }
        
        i2c_stop();
        
        y += NbBytesPage;
    }
} // end I2C_WriteSEEPROM

// Lecture d'un bloc dans l'EEPROM du MCP79411
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
{
    uint16_t y; //Variable agissant comme compteur des octets lus
    bool ack = false;
    uint8_t *pointeur = (uint8_t*)DstData;
    uint16_t timeout = 0;
    
    if(NbBytes == 0) //Si demande de lire 0 octets, on quitte
    {
        return;
    }
    
    do
    {
        i2c_start();
        ack = i2c_write(MCP79411_EEPROM_W);
        
        if(ack == false)
        {
            i2c_stop(); //Libère le bus si occupé
        }
        
        timeout ++;
        if(timeout > 1000) // Sécurité anti-blocage
        {
            return;
        }
        
    } while (ack == false);

    i2c_write(EEpromAddr);
    i2c_reStart();
    i2c_write(MCP79411_EEPROM_R);
    
    for(y = 0; y < NbBytes; y++)
    {
        if(y == (NbBytes -1))
        {
            //Dernier octets à lire, pas d'acknowledge car en dernier (page 42)
            *pointeur = i2c_read(false);
        }
        else
        {
            //Il reste des octets à lire, acknowledge
            *pointeur = i2c_read(true);
        }
    }

    i2c_stop();
    
} // end I2C_ReadSEEPROM