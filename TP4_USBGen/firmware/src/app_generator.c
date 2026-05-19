/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app_generator.c

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

#include "app_generator.h"
#include "Mc32gestSpiDac.h"
#include "MenuGen.h"
#include "GesPec12.h"
#include "Generateur.h"
#include "GesS9.h"
#include "Mc32DriverLcd.h"
#include "Mc32gest_SerComm.h"
#include "Mc32gestI2cSeeprom.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

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

APP_GENERATOR_DATA app_generatorData;
extern APP_DATA appData;
S_ParamGen LocalParamGen;
S_ParamGen USBParamGen;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_GENERATOR_Initialize ( void )

  Remarks:
    See prototype in app_generator.h.
 */

void APP_GENERATOR_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    
    app_generatorData.state = APP_GENERATOR_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_GENERATOR_Tasks ( void )

  Remarks:
    See prototype in app_generator.h.
 */
char buffer2[50];
bool need_to_save;
void APP_GENERATOR_Tasks ( void )
{
    
    /* Check the application's current state. */
    switch ( app_generatorData.state )
    {
        /* Application's initial state. */
        case APP_GENERATOR_STATE_INIT:
        {
            app_generatorData.once_was_configured = false;
            //initialisation du LCD et allumage du backlight
            lcd_init();
            lcd_bl_on();
            Init_error_type();
            // Init SPI DAC
            SPI_InitLTC2604();

            // Initialisation PEC12 et du bouton S9
            Pec12Init();
            S9Init();
            I2C_InitMCP79411();
            // Initialisation du generateur
            GENSIG_Initialize(&LocalParamGen);
            
            //affichage des informations relative au TP
            lcd_gotoxy(1,1);
            printf_lcd("TP4 GenSIG USB 2026");
            lcd_gotoxy(1,2);
            printf_lcd("BSH - JJE");
            lcd_gotoxy(1,3);
            printf_lcd("");
            

            // Active les timers 
            DRV_TMR0_Start();
            DRV_TMR1_Start();

            //creation du premier signal en fonction de la memoire ou de la valeur de base 
            GENSIG_UpdateSignal(&LocalParamGen);
            GENSIG_UpdatePeriode(&LocalParamGen);
            app_generatorData.state = APP_GENERATOR_STATE_WAIT;
        }

        case APP_GENERATOR_STATE_WAIT :
          // nothing to do
        break;
        
        case APP_GENERATOR_STATE_SERVICE_TASKS:
        {
            // toggle de la led 2
            BSP_LEDToggle(BSP_LED_2);
                        
            if(app_generatorData.once_was_configured && !appData.isConfigured){
                app_generatorData.once_was_configured = false;
                LocalParamGen = USBParamGen;
            }
            
            if(!app_generatorData.once_was_configured && appData.isConfigured){
                app_generatorData.once_was_configured = true;
                USBParamGen = LocalParamGen;
            }

             if(appData.isConfigured){
                // Execution du menu
                MENU_Execute(&USBParamGen,true);
            }
            else{
                MENU_Execute(&LocalParamGen,false);
            }        
            
            lcd_bl_on();
            
            if(app_generatorData.Get_Message_Flag == 1){
                app_generatorData.Get_Message_Flag = 0;
                strcpy(buffer2 ,app_generatorData.buffer_char);
                GetMessage(app_generatorData.buffer_char,&USBParamGen,&need_to_save);
                SendMessage(buffer2,&USBParamGen,&need_to_save);
            }



            
            app_generatorData.state = APP_GENERATOR_STATE_WAIT;
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

void APP_UpdateGeneratorState ( APP_GENERATOR_STATES NewState )
{
    app_generatorData.state = NewState;
}
/*******************************************************************************
 End of File
 */
