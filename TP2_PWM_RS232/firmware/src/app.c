/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "Mc32DriverAdcAlt.h"
#include "Mc32DriverLcd.h"
#include "Mc32DriverAdc.h"
#include "Mc32gest_RS232.h"
#include "bsp.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
S_pwmSettings pData; 
S_pwmSettings pDataToSend;
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void callback_timer1(void)
 * Sert à rentrer dans l'état APP_STATE_SERVICE_TASKS
  Remarks:
    See prototype in app.h.
 */
void callback_timer1(void)
{
    APP_UpdateState(APP_STATE_SERVICE_TASKS);
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void AllLedsOn ( void )
 * Allume toutes les LEDs
  Remarks:
    See prototype in app.h.
 */
void AllLedsOn ( void )
{
    BSP_LED ledNr;
    for(ledNr = BSP_LED_0; ledNr <= BSP_LED_7; ledNr ++)
    {
        BSP_LEDStateSet(ledNr, BSP_LED_STATE_ON);
    }
}


/*******************************************************************************
  Function:
    void AllLedsOff ( void )
 *  Eteiint toutes les LEDs
  Remarks:
    See prototype in app.h.
 */

void AllLedsOff ( void )
{
    BSP_LED ledNr;
    for(ledNr = BSP_LED_0; ledNr <= BSP_LED_7; ledNr ++)
    {
        BSP_LEDStateSet(ledNr, BSP_LED_STATE_OFF);
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    /*Initialisation du LCD*/
    lcd_init();
    /*Activation de la lumière arrière du LCD*/
    lcd_bl_on();
    /*Initialisation de l' ADC via le BSP*/
    BSP_InitADC10();
    /*Initialisation des timers et des OCs*/
    GPWM_Initialize(&pData);
}

/*******************************************************************************
  Function:
    void APP_UpdateState ( APP_STATES newState )

  Remarks:
    See prototype in app.h.
 */
void APP_UpdateState ( APP_STATES NewState )
{
    appData.state = NewState;
}

/*******************************************************************************

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //A voir si replacer
            InitFifoComm();
            /*Déclaration et initialisation de la variable Initialisation*/
            static bool Initialisation = false; 
            /*Si Initialisation n'as pas été faite (false)*/
            if(Initialisation == false)
            {
                /*Appel de la fonction permettant de tous initialiser*/
                //APP_Initialize();
                /*Eteindre toutes les LEDs*/
                AllLedsOff();
                LED0_W = 1;
                LED1_W = 1;
                LED2_W = 1;
                LED3_W = 1;
                LED4_W = 1;
                LED5_W = 1;
                LED6_W = 1;
                LED7_W = 1;
                /*Aller sur la colonne 1 à la ligne 1*/
                lcd_gotoxy(1,1);
                /*Afficher Tp1 PWM et AD <2026> sur le LCD*/
                printf_lcd("TP1 PWM et AD <2026>");
                /*Aller sur la colonne 1 à la ligne 2*/
                lcd_gotoxy(1,2);
                /*Afficher Karol Stopa sur le LCD*/
                printf_lcd("Jeremie Jean-Elie");
                /*Aller sur la colonne 1 à la ligne 3*/
                lcd_gotoxy(1,3);
                /*Afficher Kirian Gruber sur le LCD*/
                printf_lcd("Kirian Gruber");
                /*L'initialisation à été faite (true)*/
                Initialisation = true;
            }
            /*mise à jour de l'état*/
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        case APP_STATE_WAIT:
        {
            /*On ne fait rien*/
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:
        {
            /*Déclaration de la variable servant à savoir si on est
            * connecter à l'autre carte*/
            bool CommStatus = false;
            static uint8_t sendCounter  = 0;
            /*Reception du paramètre Remote*/
            CommStatus = GetMessage(&pData);
            if(CommStatus == false)
            {
                /*Gestion du code en local (Comme sur le TP1)*/
                /*Envoi des datas dans la fonction pour obtenir la vitesse et l'angle*/
                GPWM_GetSettings(&pData);
            }
            else
            {
                /*Gestion du code en Remote*/
                /*Envoie des datas dans la fonction pour obtenir la vitesse et l'angle*/
                GPWM_GetSettings(&pDataToSend);
            }
            //Affichage
            GPWM_DispSettings(&pData, CommStatus);
            
            //Execution PWM et gestion moteur
            GPWM_ExecPWM(&pData);
            
            if(sendCounter == 5)
            {
                //Envoi valeurs
                if(CommStatus == false)
                {
                    //Gestion du code en local (Comme sur le TP1)
                    //Appel de la fonction SendMessage
                    SendMessage(&pData);
                }
                else
                {
                    /*Gestion du code en Remote*/
                    /*Appel de la fonction SendMessage*/
                    SendMessage(&pDataToSend);
                }
            }
            else
            {
                sendCounter++;
            }
            
            
            /*mise à jour de l'état*/
            APP_UpdateState(APP_STATE_WAIT);
            break;
        }

        /* The default state should never be executed. */
        default:
        {
            lcd_gotoxy(1,1);
            printf_lcd("A problem");
            lcd_gotoxy(1,2);
            printf_lcd("Has occurred.");
            lcd_gotoxy(1,3);
            printf_lcd("Please, retry.");
            
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
