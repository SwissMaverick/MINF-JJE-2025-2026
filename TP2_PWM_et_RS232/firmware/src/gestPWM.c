/*--------------------------------------------------------*/
// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/


#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "GestPWM.h"
#include "bsp.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdcAlt.h"



S_pwmSettings PWMData;      // pour les settings

void GPWM_Initialize(S_pwmSettings *pData)
{
   /*Initialisation des datas*/ 
   pData->AngleSetting = 0;
   pData->SpeedSetting = 0;
   pData->absAngle = 0;
   pData->absSpeed = 0;
   
   /*Initialisation du pont en H*/
   BSP_EnableHbrige();
   
   /*Initialise le TIMER 0*/ 
   DRV_TMR0_Initialize();
   /*Initialise le TIMER 1*/  
   DRV_TMR1_Initialize();
   /*Initialise le TIMER 2*/ 
   DRV_TMR2_Initialize(); 
   
   /*Initialise l'OC2 (Output Compare 2)*/ 
   DRV_OC0_Initialize();
   /*Initialise l'OC3 (Output Compare 3)*/ 
   DRV_OC1_Initialize();
   
   /*Démarre le Timer 1*/
   DRV_TMR0_Start();
   /*Démarre le Timer 2*/
   DRV_TMR1_Start();
   /*Démarre le Timer 3*/
   DRV_TMR2_Start();
   
   /*Démarre l'OC2 (Output Compare 2)*/
   DRV_OC0_Start();
   /*Démarre l'OC3 (Output Compare 3)*/
   DRV_OC1_Start();
}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{
    /*Initialisation des tableaux et des variables*/
    static uint32_t valADC1[TAILLEMOYENNEADC] = {0};
    static uint32_t valADC2[TAILLEMOYENNEADC] = {0};
    static uint32_t i = ZERO;
    uint8_t n;
    uint32_t somme1 = ZERO;
    uint32_t somme2 = ZERO;
    uint32_t moyenneADC1, moyenneADC2;
    int32_t valVariantADC1, valeurVariantADC2;
    APP_DATA appData;

    /*Lecture des valeurs de l'ADC*/
    appData.AdcRes = BSP_ReadADCAlt();
    /*Stockage des valeurs du channel 0 de l'ADC dans le tableau valADC1*/
    valADC1[i] = appData.AdcRes.Chan0;
    /*Stockage des valeurs du channel 1 de l'ADC dans le tableau valADC2*/
    valADC2[i] = appData.AdcRes.Chan1;
    /*Incrémentation de i*/
    i++;
    /*Si la valeur de i est plus grande que 9*/
    if (i > 9)
    {
        /*Remise à 0 de i*/
        i = ZERO;
    }
    
    /*Calcul de la moyenne des échantillons pour lisser le signal*/
    for (n = ZERO; n < TAILLEMOYENNEADC; n++)
    {
        /*Calcul de la somme des valeurs de toutes les cases 
         * du tableau valADC1*/
        somme1 += valADC1[n];
        /*Calcul de la somme des valeurs de toutes les cases 
         * du tableau valADC2*/
        somme2 += valADC2[n];
    }
    /*Calcul de la moyenne de l'ADC1*/
    moyenneADC1 = somme1 / TAILLEMOYENNEADC;
    /*Calcul de la moyenne de l'ADC2*/
    moyenneADC2 = somme2 / TAILLEMOYENNEADC;

    /*Conversion des valeurs ADC en unités appropriées*/
    valVariantADC1 = ((CHAN0MAX * moyenneADC1) / ADCBRUTEMAX) + 0.5;
    valVariantADC1 = valVariantADC1 - NINTYNINE;
    valeurVariantADC2 = ((CHAN1MAX * moyenneADC2) / ADCBRUTEMAX) + 0.5;

    /*Stockage des valeurs converties dans la structure S_pwmSettings*/ 
    pData->absAngle = valeurVariantADC2;
    valeurVariantADC2 = (valeurVariantADC2 - MOITIEANGLEMAX);
    pData->AngleSetting = valeurVariantADC2;
    pData->SpeedSetting = valVariantADC1;
    pData->absSpeed = abs(valVariantADC1);
    
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    /*Affichage de la valeur de la vitesse signée (de -99 à +99)*/
    /*Aller à la ligne 2 sur la colonne 1*/
    lcd_gotoxy(1,2);
    /*Si la valeur de la vitesse est plus grande que 0*/
    if(pData->SpeedSetting > ZERO)
    {
        /*Afficher la valeur de la vitesse*/
        printf_lcd("SpeedSetting +%2d", pData->SpeedSetting);
    }
    else
    {
       /*Afficher la valeur de la vitesse*/
        printf_lcd("SpeedSetting %3d", pData->SpeedSetting); 
    }
    /*Affichage de la valeur de la vitesse absolue (de 0 à 99)*/
    /*Aller à la ligne 3 sur la colonne 1*/
    lcd_gotoxy(1,3);
    /*Affiche "absSpeed" sur le LCD*/
    printf_lcd("absSpeed");
    /*Aller à la ligne 3 sur la colonne 14
     *(pour que l'unité de absSpeed soit alignée avec l'unité de SpeedSetting
     *et de Angle)*/
    lcd_gotoxy(14,3);
    /*Affiche la valeur absolue de la vitesse sur le LCD*/
    printf_lcd("%3d", pData->absSpeed);
    /*Affichage de la valeur de l'angle (de -90 à +90)*/
    /*Aller à la ligne 4 sur la colonne 1*/
    lcd_gotoxy(1,4);
    /*Affiche "Angle" sur le LCD*/
    printf_lcd("Angle");
    /*Aller à la ligne 4 sur la colonne 14
     *(pour que l'unité de Angle soit alignée avec l'unité de SpeedSetting
     *et de absSpeed)*/
    lcd_gotoxy(14,4);
    /*Si la valeur de l'angle est plus grande que 0*/
    if(pData->AngleSetting > ZERO)
    {
        /*Afficher la valeur d'AngleSetting convertie en valeur absolue*/
        printf_lcd("+%2d", abs(pData->AngleSetting));
    }
    if (pData->AngleSetting < ZERO)
    {
        /*Afficher la valeur d'AngleSetting convertie en valeur absolue*/
        printf_lcd("-%2d", abs(pData->AngleSetting));
    }
    if (pData->AngleSetting == ZERO)
    {
        /*Afficher la valeur d'AngleSetting convertie en valeur absolue*/
        printf_lcd("%3d", abs(pData->AngleSetting));
    }
}



// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    /*Initialisation de la variable NbImpulsionOC2*/
    static uint16_t NbImpulsionOC2;
    /*Initialisation de la variable NbImpulsionOC3*/
    static uint16_t NbImpulsionOC3;
    
    /*Mise en marche du pont en H dans un sens*/
    /*Si la valeur de la vitesse absolue est plus grande que 0*/
    if(pData->absSpeed > ZERO)
    {
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    
    /*Mise en marche du pont en H dans l'autre sens*/
    /*Si la valeur de la vitesse absolue est plus petite que 0*/
    if(pData->absSpeed < ZERO)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinSet(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    
    /*Arrêt du pont en H*/
    /*Si la valeur de la vitesse absolue est égale à 0*/
    if(pData->absSpeed == ZERO)
    {
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN1_HBRIDGE_PORT, AIN1_HBRIDGE_BIT);
        PLIB_PORTS_PinClear(PORTS_ID_0, AIN2_HBRIDGE_PORT, AIN2_HBRIDGE_BIT);
    }
    
    /*Calcule du rapport cyclique  en fonction de la vitesse absolue*/
    NbImpulsionOC2 = (pData->absSpeed * DRV_TMR1_PeriodValueGet()) / TAUXPWMMAX;
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, NbImpulsionOC2);
    
    /*Calcule de la largeur d'impulsion voulue en fonction de l'angle*/
    NbImpulsionOC3 = ((pData->absAngle * PULSEWIDTHMAX) / ANGLEMAX) + PULSEWIDTHMIN;
    PLIB_OC_PulseWidth16BitSet(OC_ID_3, NbImpulsionOC3);
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    /*Initialisation du compteur PWMSoft*/
    static uint8_t countPWMSoft = ZERO;
    
    /*Si la valeur de la vitesse est plus grande que la valeur du compteur*/
    if(pData->absSpeed > countPWMSoft)
    {
        /*Eteint la LED2 (D7)*/
        //BSP_LEDOff(BSP_LED_2);
        BSP_LEDStateSet(BSP_LED_2, BSP_LED_STATE_OFF);
    }
    else
    {
        /*Allume la LED2 (D7)*/
        //BSP_LEDOn(BSP_LED_2);
        BSP_LEDStateSet(BSP_LED_2, BSP_LED_STATE_ON);
    }
    /*Incrémentation du compteur*/
    countPWMSoft ++;
    
    /*Si compteur vaut 99*/
    if(countPWMSoft == NINTYNINE)
    {
        /*Remise à 0 du compteur*/
        countPWMSoft = ZERO;
    }
    
}


