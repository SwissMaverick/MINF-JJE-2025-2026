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



#include "gestPWM.h"
#include "app.h"
#include "Fonctions.h"
#include "Mc32DriverAdc.h"
#include "Mc32DriverLcd.h"


S_pwmSettings PWMData;      // pour les settings
APP_DATA appData;

void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data 
   
   // Init état du pont en H
   BSP_EnableHnridge();  
   
   // lance les timers et OC
   DRV_TMR0_Start();
   DRV_TMR1_Start();
   DRV_TMR2_Start();
   DRV_TMR3_Start();
   DRV_OC0_Start();
   DRV_OC1_Start();
   
}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{
    // Lecture du convertisseur AD
    appData.AdcRes = BSP_ReadAllADC();
    //Canal 0
    valCanal_0 = appData.AdcRes.Chan0:
    //Enregistrer dans un tableau 10 variables du canal 0
    //Faire une moyenne de ces 10 variables
    //Nom de la moyenne : moyenneCanal_0
    //Obtention de la vitesse absolue avec une règle de trois (0 à 198)
    PWMData.absSpeed = (moyenneCanal_0 * 198) / 1023;
    //Calcul pour obtenir la valeur de vitesse signée (-99 à 99)
    PWMData.SpeedSetting = PWMData.absSpeed - 198;
    
    //Canal 1
    valCanal_1 = appData.AdcRes.Chan1;
    //Enregistrer dans un tableau 10 variables du canal 1
    //Faire une moyenne de ces 10 variables
    //Nom de la moyenne : moyenneCanal_1
    //Obtention de l'angle absolu avec une règle de trois (0 à 180)
    PWMData.absAngle = (moyenneCanal_1 * 180) / 1023;
    //Calcul pour obtenir la valeur de l'angle signée (-90 à +90)
    PWMData.AngleSetting = PWMData.absAngle - 180;
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    lcd_gotoxy(1,1);
    printf_lcd("TP1 PWM 2025-2026");
    
    //Affichage SpeedSetting
    if(PWMData.SpeedSetting < 0)
    {
        lcd_gotoxy(1,2);
        printf_lcd("SpeedSetting -%3d", PWMData.SpeedSetting);
    }
    else if(PWMData.SpeedSetting > 0)
    {
        lcd_gotoxy(1,2);
        printf_lcd("SpeedSetting +%3d", PWMData.SpeedSetting);
    }
    else
    {
        lcd_gotoxy(1,2);
        printf_lcd("SpeedSetting %3d", PWMData.SpeedSetting);
    }
    
    //Affichage absSpeed
    if(PWMData.absSpeed == 0)
    {
        lcd_gotoxy(1,3);
        printf_lcd("absSpeed %2d", PWMData.absSpeed);
    }
    else
    {
        lcd_gotoxy(1,3);
        printf_lcd("absSpeed +%2d", PWMData.absSpeed);
    }
    
    //Affichage AngleSetting
    if(PWMData.AngleSetting < 0)
    {
        lcd_gotoxy(1,4);
        printf_lcd("AngleSetting -%3d", PWMData.AngleSetting);
    }
    else if(PWMData.AngleSetting > 0)
    {
        lcd_gotoxy(1,4);
        printf_lcd("AngleSetting +%3d", PWMData.AngleSetting);
    }
    else
    {
        lcd_gotoxy(1,4);
        printf_lcd("AngleSetting %3d", PWMData.AngleSetting);
    }
    
}

// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    //Gestion du pont en H
    if(PWMData.SpeedSetting < 0)//Counter clockwise
    {
        //STBY = High
        STBY_HBridge = 1;
        //IN1 = Low, OUT2 = High
        AIN1_HBridge = 0;
        AIN2_HBridge = 1;
        
    }
    else if(PWMData.SpeedSetting > 0)//Clockwise
    {
        //STBY = High
        STBY_HBridge = 1;
        //IN1 = High, OUT2 = Low
        AIN1_HBridge = 1;
        AIN2_Hbridge = 0;
        
    }
    else
    {
        //STBY = High
        STBY_HBridge = 1;
        //IN1 = High, IN2 = High
        AIN1_HBridge = 1;
        AIN2_HBridge = 1;
        
    }
    
    PLIB_OC_PulseWidth16BitSET();
    
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    
}


