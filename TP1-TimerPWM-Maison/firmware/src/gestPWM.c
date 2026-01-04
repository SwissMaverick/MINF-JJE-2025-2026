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
#include "system_config/default/framework/driver/tmr/drv_tmr_static.h"
#include "driver/oc/drv_oc_static.h"
#include "peripheral/oc/processor/oc_p32mx795f512l.h"


S_pwmSettings PWMData;      // pour les settings
APP_DATA appData;

void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data 
    PWMData.absSpeed = 0;
    PWMData.absAngle = 0;
    PWMData.SpeedSetting = 0;
    PWMData.AngleSetting = 0;
    
   // Init état du pont en H
   BSP_EnableHbrige();
   
   // Lance les timers et OC
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
    // Variables canal 0
    static uint16_t valeursCanal_0[10];
    static uint8_t pointeurCanal_0 = 0;
    static uint16_t sommeCanal_0 = 0;
    static uint16_t derniereValeurCanal_0 = 0;
    
    // Variables canal 1
    static uint16_t valeursCanal_1[10];
    static uint8_t pointeurCanal_1 = 0;
    static uint16_t sommeCanal_1 = 0;
    static uint16_t derniereValeurCanal_1 = 0;
    
    // Lecture du convertisseur AD
    appData.AdcRes = BSP_ReadAllADC();
    
    //Canal 0
    derniereValeurCanal_0 = appData.AdcRes.Chan0;
    //Enregistrer dans un tableau 10 variables du canal 0
    sommeCanal_0 -= valeursCanal_0[pointeurCanal_0];
    valeursCanal_0[pointeurCanal_0] = derniereValeurCanal_0;
    sommeCanal_0 += valeursCanal_0[pointeurCanal_0];
    pointeurCanal_0 = (pointeurCanal_0 + 1) % 10;
    //Faire une moyenne de ces 10 variables
    uint16_t moyenneCanal_0 = sommeCanal_0 / 10;
    
    //Obtention de la vitesse absolue avec une règle de trois (0 à 198)
    PWMData.absSpeed = (moyenneCanal_0 * 198) / 1023;
    
    //Calcul pour obtenir la valeur de vitesse signée (-99 à 99)
    PWMData.SpeedSetting = PWMData.absSpeed - 99;
    
    if (moyenneCanal_0 >= 99) 
    {
        PWMData.absSpeed = PWMData.SpeedSetting; // Vitesse positive
    } 
    else 
    {
        PWMData.absSpeed = abs(PWMData.SpeedSetting); // Vitesse négative
    }
    
    //Canal 1
    derniereValeurCanal_1 = appData.AdcRes.Chan1;
    //Enregistrer dans un tableau 10 variables du canal 1
    sommeCanal_1 -= valeursCanal_1[pointeurCanal_1];
    valeursCanal_1[pointeurCanal_1] = derniereValeurCanal_1;
    sommeCanal_1 += valeursCanal_1[pointeurCanal_1];
    pointeurCanal_1 = (pointeurCanal_1 + 1) % 10;
    //Faire une moyenne de ces 10 variables
    uint16_t moyenneCanal_1 = sommeCanal_1 / 10;
    
    //Obtention de l'angle absolu avec une règle de trois (0 à 180)
    PWMData.absAngle = (moyenneCanal_1 * 180) / 1023;
    //Calcul pour obtenir la valeur de l'angle signée (-90 à +90)
    PWMData.AngleSetting = PWMData.absAngle - 90;
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    lcd_gotoxy(1,1);
    printf_lcd("TP1 PWM 2025-2026");
    
    lcd_gotoxy(1,2);
    printf_lcd("SpeedSetting %4d", PWMData.SpeedSetting);
    
    lcd_gotoxy(1,3);
    printf_lcd("absSpeed %4d", PWMData.absSpeed);

    lcd_gotoxy(1,4);
    printf_lcd("AngleSetting %4d", PWMData.AngleSetting);
        
}

// Execution PWM et gestion moteur à partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    //Gestion du pont en H
    if(PWMData.SpeedSetting < 0)//Counter clockwise
    {
        //STBY = High
        STBY_HBRIDGE_W = 1;
        //IN1 = Low, OUT2 = High
        AIN1_HBRIDGE_W = 0;
        AIN2_HBRIDGE_W = 1;
        
    }
    else if(PWMData.SpeedSetting > 0)//Clockwise
    {
        //STBY = High
        STBY_HBRIDGE_W = 1;
        //IN1 = High, OUT2 = Low
        AIN1_HBRIDGE_W = 1;
        AIN2_HBRIDGE_W = 0;
        
    }
    else
    {
        //STBY = High
        STBY_HBRIDGE_W = 1;
        //IN1 = High, IN2 = High
        AIN1_HBRIDGE_W = 1;
        AIN2_HBRIDGE_W = 1;
        
    }
    
    // Calcul de la valeur du nombre d'impulsions pour OC2 (à partir de absSpeed)
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, ((PWMData.absSpeed * 1023) / 99)*2);
    
    // Calcul de la valeur du nombre d'impulsions pour OC3 (à partir de absAngle)
    PLIB_OC_PulseWidth16BitSet(OC_ID_3, ((PWMData.absAngle + 90) * 1023 / 180)*2);
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    
}


