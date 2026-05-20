// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du générateur

// Prévu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber

#include <stdint.h>
#include <math.h>

#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "system_config/pic32mx_eth_sk2/framework/driver/drv_tmr_static.h"
#include "Mc32gestI2cSeeprom.h"



//declaration des variabes
S_Amplitude Ampli;
int32_t tb_Amplitude[ECH_MAX];

// Initialisation des parametres du generateur
void GENSIG_Initialize(S_ParamGen *pParam)
{
    // Lecture des parametres sauvegardes en memoire (taille de la structure S_ParamGen = 14oct)
    //NVM_ReadBlock((uint32_t*) pParam, sizeof(S_ParamGen));
    I2C_ReadSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));

    if (pParam->Magic != MAGIC)
    {
        // Chargement des valeurs par defaut
        pParam->Forme = SignalSinus;
        pParam->Frequence = VAL_DEFAUT_FREQ;
        pParam->Amplitude = VAL_DEFAUT_AMPL;
        pParam->Offset = VAL_DEFAUT_OFFSET;
        pParam->Magic = MAGIC;
    }
    else
    {
        // Parametres valides trouves
    }
    // mise a jour du signal, sinon pas de signal en sortie sans modification par l'utilisateur
    GENSIG_UpdateSignal(pParam);
    GENSIG_UpdatePeriode(pParam);
}
  

// Mise a jour de la periode d'echantillonnage selon la frequence
void GENSIG_UpdatePeriode(S_ParamGen *pParam)
{

    uint16_t periodeNbTic;

    // Calcul de la periode du timer en fonction de la frequence et du nombre d'echantillons
    periodeNbTic = (SYS_CLK_FREQ / ((uint32_t)ECH_MAX * pParam->Frequence)) - 1;

    // Application de la periode au timer 3
    PLIB_TMR_Period16BitSet(TMR_ID_3, periodeNbTic);

}

// Mise � jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
   //intialisation de la variable statique offset
int16_t Offset;

//initialisation de l'increment
int i;

//gestion de l'amplitude 
Ampli.amplTic = (pParam->Amplitude * DAC_HALF_RES_MAX /AMPL_MAX);
Ampli.amplMin = ((DAC_HALF_RES_MAX)-(Ampli.amplTic));
Ampli.amplMax =((DAC_HALF_RES_MAX)+(Ampli.amplTic)-1);

// Calcul de l'offset applique au signal
Offset = -((pParam->Offset*DAC_HALF_RES_MAX)/AMPL_MAX);
        

 // Selection de la forme du signal
switch (pParam->Forme)
{
//---Entrer l'amplitude dans le tableau pour obtenir un sinus---/  
    case SignalSinus:
    {
    //boucle for pour remplire le tableau 
        for( i = ECH_START; i < ECH_MAX; i++)
        {
        //calcul pour obtenir un sinus
        // Regle l'amplitude du signal avec amplTic (1.27 ratio correctif).
        // Cree une onde sinus qui monte et descend.
        // 3.6 * i fait avancer la vague (100 points pour un cycle complet).
        // Conversion des degres en radians pour sin().
        // Centre le signal autour du milieu du DAC avec DAC_HALF_RES_MAX.
        // Offset permet de decaler tout le signal vers le haut ou le bas.
        tb_Amplitude[i] = (Ampli.amplTic/1.27)*(4/M_PI * sin( M_PI *(3.6*i)/180)) + DAC_HALF_RES_MAX + Offset;
        }
    
     break;
    }
       // Generation d'un signal triangulaire
    case SignalTriangle:
    {
        float const x = ((float)DAC_HALF_RES_MAX / AMPL_MAX) / ECH_UN_QUARTS;
            float const y = pParam->Amplitude * DAC_RES_MAX / AMPL_MAX + DAC_HALF_RES_MAX;

            for (i = ECH_START; i < ECH_MAX; i++)
            {
                if (i < ECH_UN_QUARTS)
                {
                    
                    // Premiere partie du signal : monte progressivement.
                    // pParam->Amplitude regle la hauteur du signal.
                    // x * i augmente la valeur petit a petit.
                    // Centre le signal autour du milieu du DAC avec DAC_HALF_RES_MAX.
                    // Offset permet de decaler tout le signal.

                    tb_Amplitude[i] = (pParam->Amplitude * (x * i)) + DAC_HALF_RES_MAX + Offset;
                }
                else if (i < ECH_TROIS_QUARTS)
                {
  
                    // Deuxieme partie du signal : descend progressivement.
                    // -x * i fait baisser la valeur.
                    // y sert de point de reference pour cette partie.
                    // Offset decale encore le signal si besoin.
                  
                    tb_Amplitude[i] = (pParam->Amplitude * (-x * i)) + y + Offset;
                }
                else
                {
                    
                    // Derniere partie : remonte vers le debut du cycle.
                    // i - ECH_MAX calcule la position par rapport a la fin.
                    // x * (...) recree une pente.
                    // Centre a nouveau la forme autour du milieu du DAC.
                    // Offset ajuste tout le signal.

                    tb_Amplitude[i] = (pParam->Amplitude * (x * (i - ECH_MAX))) + DAC_HALF_RES_MAX + Offset;
                }
            }
        
    break;
    }
// Generation d'un signal en dent de scie   
    case SignalDentDeScie:
    {
            static uint16_t step_val;
               
            // Calcule la valeur d'increment du signal.
            // amplTic << 1 multiplie l'amplitude par 2.
            // step_val determine de combien le signal augmente a chaque point.

            step_val = (Ampli.amplTic <<1) / ECH_MAX;

            for (i = ECH_START; i < ECH_MAX; i++)
            {
                
                // Cree une rampe qui monte progressivement point par point.
                // step_val * i augmente la valeur a chaque iteration.
                // amplMin est la valeur de depart de la rampe.
                // Offset decale l'ensemble du signal vers le haut ou le bas.

                tb_Amplitude[i] = (step_val * i) + Ampli.amplMin + Offset;
            }
            break;

    break;
    }
    // Generation d'un signal carre
    case SignalCarre:
    {
         for (i = ECH_START; i < ECH_MAX; i++)
            { 
             
                // Si i est dans la premiere moitie, on met la valeur haute du signal.
                // amplMax fixe le niveau haut.
                // Offset permet de decaler le signal.

                if (i < ECH_HALF){tb_Amplitude[i] = Ampli.amplMax + Offset;}
                
                // Sinon on met la valeur basse du signal.
                // amplMin fixe le niveau bas.
                // Offset decale aussi cette partie.

                else{tb_Amplitude[i] = Ampli.amplMin + Offset;}
            }
            break;
    }
}
   
}


// Execution du generateur appelee dans l'interruption du timer 3
void GENSIG_Execute(void)
{
    static uint16_t ech_index = ECH_START;

    // Saturation haute
    if (tb_Amplitude[ech_index] >= (2 * DAC_HALF_RES_MAX ) - 1) // 2 * DAC_HALF_RES_MAX  plage total
    {
        tb_Amplitude[ech_index] = DAC_RES_MAX -1;
    }
    // Saturation basse
    else if (tb_Amplitude[ech_index] < ECH_START)
    {
        tb_Amplitude[ech_index] = ECH_START;
    }

    // Envoi de la valeur au DAC (canal 0)
    SPI_WriteToDac(DAC_CH0, tb_Amplitude[ech_index]);

    // Passage a l'echantillon suivant
    ech_index++;
    ech_index = ech_index % ECH_MAX;
}
