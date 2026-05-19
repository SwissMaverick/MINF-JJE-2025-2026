// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du g?n?rateur

// Pr?vu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber

#include "xc.h"
#include "Generateur.h"
#include "Mc32NVMUtil.h"
#include "Mc32DriverLcd.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "Mc32gestI2cSeeprom.h"
#include <stdbool.h>
#include "peripheral/tmr/plib_tmr.h"
// T.P. 2016 100 echantillons
#define MAX_ECH 100


// Variables globales
S_ParamGen valueParamGen;  //Structure intermediaire pour la sauvegarde
static uint32_t Sig_Tabl[TAILLE_TABLEAU_MAX]; //tableau a 100 cases pour le stockage des echantillons du generateur

// Initialisation du  generateur
void  GENSIG_Initialize(S_ParamGen *pParam)
{
    //lecture de la flash pour retrouver les potentiels données sauvegarder
    I2C_ReadSEEPROM((uint32_t*)&valueParamGen,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
    
    //Test si MaGIC = MAGIC pour savoir si quelque chose a été sauvegarder
    if(valueParamGen.Magic == MAGIC)
    {
        //met dans la variable de retour les données sauvegarder
        *pParam = valueParamGen;
        
        //Lignes servant à remettre des valeurs valables dans l'EEPROM
        //Decommenter pour reparer
        //pParam->Amplitude = 2500;
        //pParam->Forme = SignalSinus;
        //pParam->Frequence = 20;
        //pParam->Magic = MAGIC;
        //pParam->Offset = 2500; 

    }
    else //si rien n'etait sauvegarder
    {
        
        // Initialisation des valeurs par defaut du generateur
        pParam->Amplitude = 2500;
        pParam->Forme = SignalSinus;
        pParam->Frequence = 20;
        pParam->Magic = MAGIC;
        pParam->Offset = 2500; 
    }
}
  

// Mise a jour de la periode du timer 3
void  GENSIG_UpdatePeriode(S_ParamGen *pParam)
{
    //calcule de la periode
    uint16_t period = (((80000000 / pParam->Frequence) / 2) / MAX_ECH) - 1;

    //set de la nouvelle valeur du timer counter
    PLIB_TMR_Period16BitSet(TMR_ID_3,period);
}
#define val_max_counter 10

// Mise ? jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
    switch(pParam->Forme)
        {   //recalcule tout le tableau de données a affiché en fonction de la forme choisi
            case SignalCarre: 
                GENSIG_Calcul_Carre(Sig_Tabl,TAILLE_TABLEAU_MAX,pParam);
                break;
           case SignalDentDeScie:
                GENSIG_Calcul_DentDeScie(Sig_Tabl,TAILLE_TABLEAU_MAX,pParam);
                break;
            case SignalTriangle:
                GENSIG_Calcul_Triangle(Sig_Tabl,TAILLE_TABLEAU_MAX,pParam);
                break;
            case SignalSinus:
                GENSIG_Calcul_Sinus(Sig_Tabl,TAILLE_TABLEAU_MAX,pParam);
                break;
        }  
}
    


// Convertit une tension en millivolts vers une valeur numérique
// utilisable par notre DAC 16 bits
uint32_t VoltageToDAC(float V_mV)
{
    // Variable contenant la valeur calculée
    float k;

    // Conversion de la tension en valeur DAC
    // 65536 correspond à la résolution d'un DAC 16 bits (2^16)
    // 65536 / 2 = valeur centrale du DAC (32768)
    // (V_mV / 20000) normalise la tension par rapport à une plage de ±20V
    // On multiplie ensuite par 65536 pour obtenir l'échelle complète du DAC
    // Le résultat est soustrait à la valeur centrale pour avoir une tension possitive si 
    // V_mV est positive et negative dans le cas ou elle est negative
    k = 65536 / 2 - ((V_mV / 20000.0f) * (65536.0f));
    
    // Protection : si la valeur calculée est négative,
    // on la force à la valeur minimale du DAC
    if (k < 0) k = 0;

    // Protection : si la valeur dépasse la valeur maximale du DAC,
    // on la limite à 65535
    if (k > 65535) k = 65535;

    return ((uint32_t)k);
}
 


 
void  GENSIG_Execute(void)
{
    //variable de comptage de 0 a 99 pour faire les 100 echantillons du signal
    static int cpt = 0;
    if(cpt == 99){
        cpt = 0;
    }
    else
    {
        cpt++;
    }
    //envoie la valeur du tableau a la channel 0 du dac 
    SPI_WriteToDac(0,Sig_Tabl[cpt]);
}

void GENSIG_Calcul_Sinus(uint32_t *tabl, uint8_t taillemax,S_ParamGen *pParam)
{
    static int i ;
    for(i = 0; i < 100; i++)
    {
        float val;
        val = (pParam->Amplitude* (sin(2 * 3.14159265f * i / 100)))+pParam->Offset;
        tabl[i] = VoltageToDAC(val); 
    }
}

void GENSIG_Calcul_Carre(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam)
{
    static int i ;
    int16_t val;
    for(i = 0; i < 100; i++)
    {
        if(i < 50)
            val = pParam->Amplitude + pParam->Offset;
        else
            val = -pParam->Amplitude + pParam->Offset;

        tabl[i] = VoltageToDAC(val);
    }
}

void GENSIG_Calcul_Triangle(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam)
{
    static int i ;
    for (i = 0; i < taillemax; i++)
    {
        float val;

        if (i < taillemax / 2)
        {
            val = -pParam->Amplitude + (4.0f * pParam->Amplitude * i / taillemax);
        }
        else
        {
            val = pParam->Amplitude - (4.0f * pParam->Amplitude * (i - taillemax / 2) / taillemax);
        }

        val += pParam->Offset;
        tabl[i] = VoltageToDAC(val);
    }
}

void GENSIG_Calcul_DentDeScie(uint32_t *tabl, uint8_t taillemax, S_ParamGen *pParam)
{
    static int i ;
    for (i = 0; i < taillemax; i++)
    {
        float val;

        val = (-pParam->Amplitude) + (2.0f * pParam->Amplitude * i / taillemax);
        val += pParam->Offset;

        tabl[i] = VoltageToDAC(val);
    }
} 