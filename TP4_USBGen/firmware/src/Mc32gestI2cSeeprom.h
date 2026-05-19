#ifndef Mc32GestI2CSEEPROM_H
#define Mc32GestI2CSEEPROM_H
/*--------------------------------------------------------*/
// Mc32GestI2cEEprom.h
/*--------------------------------------------------------*/
//	Description :	Gestion par I2C de l'EEPROM du MCP79411
//                      ( Exercice 9_1 )
//	Auteur 		: 	C. Huber
//	Version		:	V1.6    12.04.2016
//	Compilateur	:	XC32 V1.40 & Harmony 1_06
//
/*--------------------------------------------------------*/

// Définition pour MCP79411
#define MCP79411_EEPROM_R    0xAF         
#define MCP79411_EEPROM_W    0xAE         
#define MCP79411_EEPROM_BEG   0x00         
#define MCP79411_EEPROM_END   0x7F        

#define EEPROM_PAGE_SIZE 8
#include <stdint.h>


// prototypes des fonctions
void I2C_InitMCP79411(void);
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes);
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes);

#endif