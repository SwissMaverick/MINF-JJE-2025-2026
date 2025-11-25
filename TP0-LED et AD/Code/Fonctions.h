/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _FONCTIONS_H    /* Guard against multiple inclusion */
#define _FONCTIONS_H

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

/* Initialisation des constantes */

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7
    
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define EIGHT 8
#define MAXCOUNTER 29

/*Prototypes des fonctions*/

void LedAllOff(void);

void LedAllOn(void);

void Chenillard(void);

void AdcPot(void);
    
void Init (void);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
