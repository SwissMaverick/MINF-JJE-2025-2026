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







// Initialisation de la communication I2C et du MCP79411
// ------------------------------------------------

void I2C_InitMCP79411(void)
{
   bool Fast = true;
   i2c_init( Fast );
} //end I2C_InitMCP79411

// Ecriture d'un bloc dans l'EEPROM du MCP79411 

void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes) {
    bool Ack = true;
    uint16_t i = 0;
    uint8_t *src = (uint8_t*) SrcData;   

//    do {
//        i2c_start();
//        Ack = i2c_write(MCP79411_EEPROM_W);
//    } while (!Ack);
//
//    i2c_write(EEpromAddr);
//
//    for (i = 0; i < NbBytes < 8; i++) {
//
//        i2c_write(src[i]);
//    }
//
//    i2c_stop();
//    do {
//        i2c_start();
//        Ack = i2c_write(MCP79411_EEPROM_W);
//    } while (!Ack);
//
//    i2c_write(EEpromAddr);
//
//    for (i = 8; i < NbBytes < 16; i++) {
//
//        i2c_write(src[i]);
//    }
//
//    i2c_stop();

    uint16_t NbBytesRestants = NbBytes;
//    uint16_t EEpromAddrCourante = EEpromAddr;
    
    while (NbBytesRestants > 0)
    {
        do {
            i2c_start();
            Ack = i2c_write(MCP79411_EEPROM_W);
        } while (!Ack);

        i2c_write(EEpromAddr+i);

//        for (i = 0; i < NbBytes; i++) {

//        //while(NbBytesRestants>0 && (EEpromAddrCourante%8) != 0)
//        while((NbBytesRestants>0) && (((EEpromAddr+i)%8) != 0 || (i == 0))){
//            i2c_write(src[i]);
//            i++;
////            EEpromAddrCourante++;
//            NbBytesRestants--;
//        }


        do{
            i2c_write(src[i]);
            i++;
            NbBytesRestants--;
        } while((NbBytesRestants>0) && (((EEpromAddr+i)%8) != 0));
            
        i2c_stop();
    }
    
} // end I2C_WriteSEEPROM

// Lecture d'un bloc dans l'EEPROM du MCP79411
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
{
bool Ack = true;
uint16_t i;  
uint8_t *dst = (uint8_t*)DstData;

do
{
    i2c_start();
    Ack = i2c_write(MCP79411_EEPROM_W);
}while (!Ack);
    
    i2c_write(EEpromAddr);
    
    i2c_reStart();
    i2c_write(MCP79411_EEPROM_R);

    for ( i = 0; i < NbBytes; i++)
    {
        dst[i] = i2c_read(i < (NbBytes - 1));
    }

    i2c_stop();

} // end I2C_ReadSEEPROM
   





 



