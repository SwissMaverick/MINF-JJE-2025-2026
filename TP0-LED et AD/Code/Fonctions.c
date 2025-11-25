/* 
 * File:   fonctions.c
 * Author: Jérémie Jean-Elie
 * 
 * Description : Fonctions utiles au programmes
 * 
 */
#include "Fonctions.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "app.h"
#include "bsp.h"
#include <stdint.h>
#include <stdbool.h>

/*Fonction Eteindre Leds
 Cette fonction éteint toutes les Leds
 */
void LedAllOff(void)
{
    BSP_LEDOff(BSP_LED_0);
    BSP_LEDOff(BSP_LED_1);
    BSP_LEDOff(BSP_LED_2);
    BSP_LEDOff(BSP_LED_3);
    BSP_LEDOff(BSP_LED_4);
    BSP_LEDOff(BSP_LED_5);
    BSP_LEDOff(BSP_LED_6);
    BSP_LEDOff(BSP_LED_7);
}

/*Fonction Allumer les Leds
 Cette fonction allume toutes les Leds
 */
void LedAllOn(void)
{
    BSP_LEDOn(BSP_LED_0);
    BSP_LEDOn(BSP_LED_1);
    BSP_LEDOn(BSP_LED_2);
    BSP_LEDOn(BSP_LED_3);
    BSP_LEDOn(BSP_LED_4);
    BSP_LEDOn(BSP_LED_5);
    BSP_LEDOn(BSP_LED_6);
    BSP_LEDOn(BSP_LED_7);
}

/*Fonction Chenillard
 Cette fonction fait le chenillard des 8 Leds
 */
static bool toggle = true; /* Déclaration d'une variable toggle qui va 
                            * permettre au chenillard de s'éxecuter toutes 
                            * les 2 interruptions */
static uint8_t led = ZERO;    /* Initialisation de la variable de la machine 
                            * d'états à l'état 0 */
void Chenillard(void)
{    
    if(toggle == true)     /* Au tout premier appel de la fonction, le 
                            * chenillard va commencer avec l'allumage
                            * de le LED 0 */
    {
        switch(led)
        {
            case LED0:
                /* Allumage de la LED 0, toutes les autres sont éteintes */
                BSP_LEDOn(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED1:
                /* Allumage de la LED 1, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOn(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED2:
                /* Allumage de la LED 2, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOn(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED3:
                /* Allumage de la LED 3, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOn(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED4:
                /* Allumage de la LED 4, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOn(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED5:
                /* Allumage de la LED 5, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOn(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED6:
                /* Allumage de la LED 6, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOn(BSP_LED_6);
                BSP_LEDOff(BSP_LED_7);
                break;
                
            case LED7:
                /* Allumage de la LED 8, toutes les autres sont éteintes */
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOn(BSP_LED_7);
                break;
        }
        led ++; //On incrémente la machine d'états
        
        if(led == EIGHT)
        {
            led = ZERO;
        }
        /* Dans le cas où le chenillard atteint son état maximal, on 
         remet celui-ci à 0 */
        
        toggle = false; /* On met le toggle à false pour que le chenillard
                         saute une interruption */
    }
    else
    {
        toggle = true;
    }
    /* Dans la seconde interruption, le toggle sera false et il n'y aura
     * aucune éxecution de chenillard. Le toggle est remis à vrai pour passer
     * dans le chanillard à la prochaine interruption */
        
}
/*Fonction ADC 
 Cette fonction lis l'ADC afin obtenir la valeur des potentiomètres.
 Ensuite, elle affiche les valeurs sur le LCD
 */
void LectureADC(void)
{
    APP_DATA appData;
    appData.adcRes = BSP_ReadAllADC();
    lcd_gotoxy(ONE,THREE); //Aller à la ligne 3 du LCD
    printf_lcd("CH0 %4d CH1 %4d", appData.adcRes.Chan0, appData.adcRes.Chan1);
    //Afficher les valeurs des potentiomètres
}

/*Fonction d'initialisation de la carte 
 Initialisation du LCD et de l'ADC */
void Init(void)
{
    lcd_bl_on(); //Allumage du rétroéclairage
    lcd_gotoxy(ONE,ONE); //Aller à la ligne 1
    printf_lcd("TP0 LED+AD 2025-2026"); //Affichage sur le LCD
    lcd_gotoxy(ONE,TWO); //Aller à la ligne 2
    printf_lcd("JEAN-ELIE"); //Affichage sur le LCD
    
    //Allumer toutes les LEDs
    LedAllOn();
    
}