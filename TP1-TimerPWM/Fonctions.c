/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "Fonctions.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "app.h"
#include "bsp.h"
/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*Fonction d'initialisation de la carte 
 Initialisation du LCD et de l'ADC */
void Initialisation_LCD(void)
{
    lcd_bl_on(); //Allumage du rétroéclairage
    lcd_gotoxy(1,1); //Aller à la ligne 1
    printf_lcd("TP1 PWM 2025-2026"); //Affichage sur le LCD
    lcd_gotoxy(1,2); //Aller à la ligne 2
    printf_lcd("JEAN-ELIE"); //Affichage sur le LCD
    lcd_gotoxy(1,3); //Aller à la ligne 3
    printf_lcd("SAVARY"); //Affichage sur le LCD
    
    LedAllOff();
}

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

/* *****************************************************************************
 End of File
 */
