// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms



#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"
#include "GesPec12.h"
#include "Mc32DriverLcd.h"


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
    uint8_t OK;
    uint8_t ESC;
    static uint8_t etatActuel = 0;
    // static uint8_t indiceParametre = 0;
    static uint8_t indiceAsterisque = 0;
    static uint8_t indiceEdit = 0;
    static uint8_t indiceForme = 0;
    static uint8_t indiceFrequence = 0;
    static uint8_t indiceAmplitude = 0;
    static uint8_t indiceOffset = 0;
    static uint16_t offsetPos = 0;
    // static uint16_t valeurTest = 50;
    
    Incremente = Pec12IsPlus();
    Decremente = Pec12IsMinus();
    OK = Pec12IsOK();
    ESC = Pec12IsESC();
    
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
    switch(etatActuel)
    {
        case SELECT :
                    
            switch(indiceAsterisque)
            {
                case 0 :
                    lcd_gotoxy(1,1);
                    printf_lcd("*Forme =");
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceAsterisque ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceAsterisque --;
                    }
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = EDIT;
                    }
                    
                    indiceEdit = indiceAsterisque;
                    
                    break;
                    
                case 1 :
                    lcd_gotoxy(1,2);
                    printf_lcd("*Freq [Hz] =");
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceAsterisque ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceAsterisque --;
                    }
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = EDIT;
                    }
                    
                    indiceEdit = indiceAsterisque;
                    
                    break;
                    
                case 2 :
                    lcd_gotoxy(1,3);
                    printf_lcd("*Ampl [mV] =");
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceAsterisque ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceAsterisque --;
                    }
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = EDIT;
                    }
                    
                    indiceEdit = indiceAsterisque;
                    
                    break;
                    
                case 3 :
                    lcd_gotoxy(1,4);
                    printf_lcd("*Offset [mV] =");
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceAsterisque ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceAsterisque --;
                    }
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = EDIT;
                    }
                    
                    indiceEdit = indiceAsterisque;
                            
                    break;
                    
                default :
                    
                    break;
            }
            
            break;
            
        case EDIT :
            
            switch(indiceEdit)
            {
                case 0 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme =");
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = FORME;
                    }
                    
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceEdit ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceEdit --;
                    }
                    break;
                    
                case 1 :
                    lcd_gotoxy(1,2);
                    printf_lcd("?Freq [Hz] =");
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = FREQUENCE;
                    }
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceEdit ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceEdit --;
                    }
                    break;
                    
                case 2 :
                    lcd_gotoxy(1,3);
                    printf_lcd("?Ampl [mV] =");
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = AMPLITUDE;
                    }
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceEdit ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceEdit --;
                    }
                    break;
                    
                case 3 :
                    lcd_gotoxy(1,4);
                    printf_lcd("?Offset [mV] =");
                    if((OK == 1) && (ESC == 0))
                    {
                        etatActuel = OFFSET;
                    }
                    if((Incremente == 1) && (Decremente == 0))
                    {
                        indiceEdit ++;
                    }
                    if((Decremente == 1) && (Incremente == 0))
                    {
                        indiceEdit --;
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
            
            switch(indiceForme)
            {
                case 0 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme = Sinus");
                    break;
                            
                case 1 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme = Triangle");
                    break;
                            
                case 2 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme = DentDeScie");
                    break;
                            
                case 3 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme = Carre");
                    break;
                            
                default :
                            
                    break;
                }
                    
            break;
                    
        case FREQUENCE :
            
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceFrequence ++;
                pParam->Frequence = pParam->Frequence + 20;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceFrequence --;
                pParam->Frequence = pParam->Frequence - 20;
            }
            
            //Dépassement de valeurs (Rebouclement)
            if(pParam->Frequence < VALFREQMIN) // 20Hz
            {
                pParam->Frequence = VALFREQMAX; // 2000Hz
            }
            if(pParam->Frequence > VALFREQMAX) // 2000Hz
            {
                pParam->Frequence = VALFREQMIN; // 20Hz
            }
                    
            break;
                    
        case AMPLITUDE :
            
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceAmplitude ++;
                pParam->Amplitude = pParam->Amplitude + 100;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceAmplitude --;
                pParam->Amplitude = pParam->Amplitude - 100;
            }
            
            //Dépassement de valeurs (Rebouclement)
            if(pParam->Amplitude < VALAMPLMIN) // 0mV
            {
                pParam->Amplitude = VALAMPLMAX; // 10'000mV
            }
            if(pParam->Amplitude > VALAMPLMAX) // 10'000mV
            {
                pParam->Amplitude = VALAMPLMIN; // 0mV
            }
                    
            break;
                    
        case OFFSET :
            
            if((Incremente == 1) && (Decremente == 0))
            {
                indiceOffset ++;
                pParam->Offset = pParam->Offset + 100;
            }
            if((Decremente == 1) && (Incremente == 0))
            {
                indiceOffset --;
                pParam->Offset = pParam->Offset - 100;
            }
                    
            //Dépassement de valeurs (Pas de rebouclement)
            if(pParam->Offset < VALOFFSETMIN) // 0mV
            {
                offsetPos = VALOFFSETMIN; // 0mV
            }
            if(pParam->Offset > VALOFFSETMAX) // 10'000mV
            {
                offsetPos = VALOFFSETMAX; // 10'000mV
            }
                    
            pParam->Offset = offsetPos - VALASOUSTRAIRE; // -5'000mV
                    
            break;
        
        default :
            
            break;
    }
}