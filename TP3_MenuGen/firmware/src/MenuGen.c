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
    lcd_gotoxy(1,1);
    printf_lcd(" Forme =");
    lcd_gotoxy(1,2);
    printf_lcd(" Freq [Hz] =");
    lcd_gotoxy(1,3);
    printf_lcd(" Ampl [mV] =");
    lcd_gotoxy(1,4);
    printf_lcd(" Offset [mV] =");
}


// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam)
{
    uint8_t Incremente;
    uint8_t Decremente;
    static uint8_t indiceAsterisque = 0;
    static uint8_t indiceForme = 0;
    static uint8_t indiceFrequence = 0;
    static uint8_t indiceAmplitude = 0;
    static uint16_t valeurTest = 50;
    
    Incremente = Pec12IsPlus();
    Decremente = Pec12IsMinus();
    
    /* Test PEC 12
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
    }*/
    
    /* Machine d'état menu */
    switch()
    {
        case ASTERISQUE :
                    
            switch(indiceAsterisque)
            {
                case 0 :
                    lcd_gotoxy(1,1);
                    printf_lcd("*Forme =");
                    break;
                    
                case 1 :
                    lcd_gotoxy(1,2);
                    printf_lcd("*Freq [Hz] =");
                    break;
                    
                case 2 :
                    lcd_gotoxy(1,3);
                    printf_lcd("*Ampl [mV] =");
                    break;
                    
                case 3 :
                    lcd_gotoxy(1,4);
                    printf_lcd("*Offset [mV] =");
                    break;
                    
                default :
                    
                    break;
            }
            
            break;
            
        case AFFICHAGE :
            
            switch()
            {
                case FORME :
                    
                    switch(indiceForme)
                    {
                        case 0 :
                            lcd_gotoxy(1,1);
                            printf_lcd("Forme = Sinus");
                            break;
                            
                        case 1 :
                            lcd_gotoxy(1,1);
                            printf_lcd("Forme = Triangle");
                            break;
                            
                        case 2 :
                            lcd_gotoxy(1,1);
                            printf_lcd("Forme = DentDeScie");
                            break;
                            
                        case 3 :
                            lcd_gotoxy(1,1);
                            printf_lcd("Forme = Carre");
                            break;
                            
                        default :
                            
                            break;
                    }
                    
                    break;
                    
                case FREQUENCE :
                    
                    switch(indiceFrequence)
                    {
                        
                    }
                    
                    break;
                    
                case AMPLITUDE :
                    
                    switch(indiceAmplitude)
                    {
                        
                    }
                    
                    break;
                    
                default :
                    
                    break;
            }
            
            break;
        
        case FORME :
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceForme ++;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceForme --;
            }
            
            break;
        
        case FREQUENCE :
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceFrequence ++;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceFrequence --;
            }
            
            break;
        
        case AMPLITUDE :
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceAmplitude ++;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceAmplitude --;
            }
            
            break;
        
        default :
            
            break;
    }
    
}




