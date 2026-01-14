/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

S_pwmSettings pData; //transfer dans APP

void __ISR(_TIMER_1_VECTOR, ipl4AUTO) IntHandlerDrvTmrInstance0(void)
{
    /*Déclaration et initialisation du compteur de 3s*/
    static uint8_t count3s = 0;                

    /*Si la valeur du compteur de 3s est plus petite que 149*/
    if (count3s < 149)
    {
        /*On reste dans l'état Init*/
        APP_UpdateState(APP_STATE_INIT);
        /*Incrémente du compteur de 3s*/
        count3s++;
    }
    else
    {
        /*Déclaration et initialisation du compteur ClearLine*/
        static uint8_t countClearLine = 0; 
        /*Si le compteur ClearLine est plus petit ou églal à 0*/
        if (countClearLine <= 0)
        {
            /*Clear la ligne 2 en la remplissant d'espace*/
            lcd_ClearLine(2);      
            /*Clear la ligne 3 en la remplissant d'espace*/
            lcd_ClearLine(3);      
            /*Incrémente du compteur ClearLine*/
            countClearLine++;      
        }
        /*Allume la LED D6*/
        BSP_LEDOn(BSP_LED_0);

       
        
        /*Appel de la fonction callback du timer 1*/
        callback_timer1();
        /*Eteint la LED0 (D6)*/
        BSP_LEDOff(BSP_LED_0);
    }

    /*Clear le flag du timer 1*/
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
}
void __ISR(_TIMER_2_VECTOR, ipl0AUTO) IntHandlerDrvTmrInstance1(void)
{
    /*Clear le flag du timer 2*/
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
}
void __ISR(_TIMER_3_VECTOR, ipl0AUTO) IntHandlerDrvTmrInstance2(void)
{
    /*Clear le flag du timer 3*/
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
}

/*******************************************************************************
 End of File
*/
