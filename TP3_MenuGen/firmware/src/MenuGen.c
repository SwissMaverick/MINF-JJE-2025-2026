// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms



#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"
#include "GesPec12.h"


// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam)
{
}


// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam)
{
    uint8_t Incremente;
    uint8_t Decremente;
    static uint16_t valeurTest = 50;
    
    Incremente = Pec12IsPlus();
    Decremente = Pec12IsMinus();
    
    if((Incremente == 1) && (Decremente == 0))
    {
        valeurTest ++;
        lcd_gotoxy(1,4);
        printf_lcd("Valeur = %d", valeurTest);
    }
    if((Decremente == 1) && (Incremente == 0))
    {
        valeurTest --;
        lcd_gotoxy(1,4);
        printf_lcd("Valeur = %d", valeurTest);
    }
}




