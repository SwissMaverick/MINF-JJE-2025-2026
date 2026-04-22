//--------------------------------------------------------
//      Mc32_I2cUtilCCS.h
//--------------------------------------------------------
//	Description :	Utilitaire I2C compatible syntaxe CCS
//                  Obtenu par modification de l'exemple harmony
//
//	Auteur 		: 	C. HUBER
//  Date        :   22.05.2014
//	Compilateur	:	XC32 V1.33 & Harmony V1.00
//  Modifications :
//  	CHR 19.03.2015  Migration sur plib_i2c de Harmony 1.00   CHR
//      CHR 12.04.2016  adaptaion détails pour plib_i2c de Harmony 1.06   CHR
//		SCA 04.04.2017  Compléments commentaires i2c_init HighFrequencyEnable/Disable
//  	SCA 18.03.2024  v1.51 MPLABX 5.50/xc32 2.50/Harmony 2.06
//                   Correction commentaire acknowledge i2c_write()
//--------------------------------------------------------

#ifndef MC32_I2CUTILCCS_H
#define MC32_I2CUTILCCS_H

#include <stdbool.h>
#include <stdint.h>


//------------------------------------------------------------------------------
// i2c_init
//
// Initialisationde l'I2c
//   si bool Fast = false   LOW speed
//   si bool Fast = true    HIGH speed
//------------------------------------------------------------------------------

void i2c_init( bool Fast );
void i2c_start(void);
void i2c_reStart(void);
bool i2c_write( uint8_t data );
uint8_t i2c_read(bool ackTodo);
void i2c_stop( void );

#endif
