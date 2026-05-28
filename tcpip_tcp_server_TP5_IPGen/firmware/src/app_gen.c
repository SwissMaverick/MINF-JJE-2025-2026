/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app_gen.c

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

#include "app_gen.h"
#include "Mc32DriverLcd.h"
#include "driver/tmr/drv_tmr_static.h"
#include "Mc32gestSpiDac.h"
#include "Mc32gestI2cSeeprom.h"
#include "MenuGen.h"
#include "GesPec12.h"
#include "Generateur.h"

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

APP_GEN_DATA app_genData;

S_ParamGen LocalParamGen;
S_ParamGen RemoteParamGen;


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

void APP_GEN_UpdateState ( APP_GEN_STATES NewState  )
{
    app_genData.state = NewState;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_GEN_Initialize ( void )

  Remarks:
    See prototype in app_gen.h.
 */

void APP_GEN_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_genData.state = APP_GEN_STATE_INIT;
    app_genData.infoTCP = false;
    app_genData.demandeSave = false;
    app_genData.demandeUpdate = false;
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
    
    //initialisation des timer
    DRV_TMR0_Initialize();
    DRV_TMR1_Initialize();
    
}


/******************************************************************************
  Function:
    void APP_GEN_Tasks ( void )

  Remarks:
    See prototype in app_gen.h.
 */

void APP_GEN_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_genData.state )
    {
        /* Application's initial state. */
        case APP_GEN_STATE_INIT:
        {
            lcd_init();  
            lcd_bl_on();

            // Init SPI DAC
            SPI_InitLTC2604();
            
            // Init I2C
            I2C_InitMCP79411();

            // Initialisation PEC12
            Pec12Init();

            // Initialisation du menu
            MENU_Initialize(&LocalParamGen);

            // Initialisation du generateur
            GENSIG_Initialize(&LocalParamGen);
            GENSIG_Initialize(&RemoteParamGen);
            
            printf_lcd(" TP4 UsbGen <2026>    ");
            // A adapter pour les 2 noms sur 2 lignes
            lcd_gotoxy(1,2);
            printf_lcd(" Louis Cardinaux");
            lcd_gotoxy(1,3);
            printf_lcd(" Jeremie Jean-Elie");
            

            // Active les timers 
            DRV_TMR0_Start();
            DRV_TMR1_Start();
            app_genData.state = APP_GEN_STATE_WAIT;
            break;
        }
        
        case APP_GEN_STATE_WAIT:
        {
            // nothing to do

            break;
        }

        case APP_GEN_STATE_SERVICE_TASKS:
        {

            BSP_LEDToggle(BSP_LED_2);
            
            // détection D'une connection ethernet
            if(app_genData.infoTCP != APP_GetTCP_Status()) 
            {
                app_genData.infoTCP = APP_GetTCP_Status(); 
                if(app_genData.infoTCP) 
                {
                    // mise a jour du signal selon parametre remote
                    GENSIG_UpdateSignal(&RemoteParamGen);
                    GENSIG_UpdatePeriode(&RemoteParamGen);
                }
                else
                {
                    // mise a jour du signal selon parametre local
                    GENSIG_UpdateSignal(&LocalParamGen);
                    GENSIG_UpdatePeriode(&LocalParamGen);
                }
                
            }
            else
            {
                app_genData.infoTCP = APP_GetTCP_Status(); // lecture pin detection pour mise a jour de infoUsb
            }          
            
            
            // Execution du menu
            if(app_genData.infoTCP)
            {
                MENU_Execute(&RemoteParamGen,(bool)!app_genData.infoTCP);  // inversion de la logique de détection            
            }
            else
            {
                MENU_Execute(&LocalParamGen,(bool)!app_genData.infoTCP);  // inversion de la logique de détection   
            }
            
            if (app_genData.demandeSave == true )
            {
                MENU_Save(&RemoteParamGen);
                
                app_genData.demandeSave = false;
            }
                
            if (app_genData.demandeUpdate == true )
            {
                // mise a jour du signal selon parametre remote
                GENSIG_UpdateSignal(&RemoteParamGen);
                GENSIG_UpdatePeriode(&RemoteParamGen);
                
                app_genData.demandeUpdate = false;
            }
            
            //MENU_Execute(&LocalParamGen);
            app_genData.state = APP_GEN_STATE_WAIT;

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

void APP_GEN_SetParam (S_ParamGen* pParam)
{
    RemoteParamGen.Forme = pParam->Forme;
    RemoteParamGen.Frequence = pParam->Frequence;
    RemoteParamGen.Amplitude = pParam->Amplitude;
    RemoteParamGen.Offset = pParam->Offset;
}

void APP_GEN_GetParam (S_ParamGen* pParam)
{
    pParam->Forme = RemoteParamGen.Forme;
    pParam->Frequence = RemoteParamGen.Frequence;
    pParam->Amplitude = RemoteParamGen.Amplitude;
    pParam->Offset = RemoteParamGen.Offset;
}


void APP_GEN_DemandeSave(void)
{
   app_genData.demandeSave = true;
}

void APP_GEN_DemandeUpdate(void)
{
   app_genData.demandeUpdate = true;
}

/*******************************************************************************
 End of File
 */
