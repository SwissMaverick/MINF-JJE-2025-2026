// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du générateur

// Prévu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber


#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "math.h"
#include "driver/tmr/drv_tmr.h"
#include "app.h"

// T.P. 2016 100 echantillons
#define MAX_ECH 100

S_SampTable Sample;

// Initialisation du  générateur
void  GENSIG_Initialize(S_ParamGen *pParam)
{
    pParam->Forme = SignalTriangle;
    pParam->Amplitude = 2000;
    pParam->Offset = 2000;
    pParam->Frequence = 200;
}
  

// Mise à jour de la periode d'échantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam)
{
    uint16_t periodeTimer = 0;
    uint32_t F_Mcu, F_Timer;
    F_Mcu = FMCU;
    F_Timer = MAX_ECH * pParam->Frequence;
    periodeTimer = F_Mcu / F_Timer;
    PLIB_TMR_Period16BitSet(TMR_ID_3, periodeTimer);
}

// Mise à jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
    static uint16_t center = 32767.0;
    static int16_t Offset_old;
    static int16_t Amplitude_old;
    
    float amplitude = ((float)pParam->Amplitude / 10000.0) * 65535.0;
    float offset = ((float)pParam->Offset / 10000.0) * 65535.0;
    //float amplitude_en_mV = (pParam ->Amplitude / 100) * 2 ;
    uint8_t i;
    
    switch (pParam->Forme)
    {
        case SignalSinus:
            for (i = 0; i < MAX_ECH; i++)
            {
                Sample.SampTable[i] = (uint16_t)(center - offset + (amplitude / 2.0) * sin((2.0 * M_PI * i) / MAX_ECH));
            }
        break;
        
        case SignalTriangle:
            for (i = 0; i < MAX_ECH; i++)
            {
                if (i < (MAX_ECH / 2))
                {
                    // Montée de -Ampl/2 à +Ampl/2
                    Sample.SampTable[i] = (uint16_t)(center - offset - (amplitude / 2.0) + (amplitude * 2.0 * i) / MAX_ECH);
                }
                else
                {
                    // Descente de +Ampl/2 à -Ampl/2
                    Sample.SampTable[i] = (uint16_t)(center - offset + (amplitude / 2.0) - (amplitude * 2.0 * (i - (MAX_ECH / 2))) / MAX_ECH);
                }
            }
        break;
        
        case SignalDentDeScie:
            for (i = 0; i < MAX_ECH; i++) 
            {
                // Montée de -Ampl/2 à +Ampl/2 sur toute la période
                Sample.SampTable[i] = (uint16_t)(center - offset - (amplitude / 2.0) + (amplitude * i) / MAX_ECH);
            }
        break;
        
        case SignalCarre:
            for (i = 0; i < MAX_ECH; i++) 
            {
                if (i < (MAX_ECH / 2))
                {
                    Sample.SampTable[i] = (uint16_t)(center - offset - (amplitude / 2.0)); // Partie basse
                }
                else
                {
                    Sample.SampTable[i] = (uint16_t)(center - offset + (amplitude / 2.0)); // Partie haute
                }
            }
        break;
        
        default:
        break;
    }
    
    Offset_old = offset;
    Amplitude_old = amplitude;
   
}

// Execution du générateur
// Fonction appelée dans Int timer3 (cycle variable variable)

// Version provisoire pour test du DAC à modifier
void  GENSIG_Execute(void)
{
   LED3_W = 0;
    
   static uint16_t EchNb = 0;
  
   SPI_WriteToDac(0, Sample.SampTable[EchNb] );      // sur canal 0
   EchNb++;
   EchNb = EchNb % MAX_ECH;
   
   LED3_W = 1;
}
