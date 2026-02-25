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
    static uint8_t indiceOffset = 0;
    static uint16_t offsetPos = 0;
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
        case SELECT :
                    
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
            
        case EDIT :
            
            switch(indiceAsterisque)
            {
                case 0 :
                    lcd_gotoxy(1,1);
                    printf_lcd("?Forme =");
                    break;
                    
                case 1 :
                    lcd_gotoxy(1,2);
                    printf_lcd("?Freq [Hz] =");
                    break;
                    
                case 2 :
                    lcd_gotoxy(1,3);
                    printf_lcd("?Ampl [mV] =");
                    break;
                    
                case 3 :
                    lcd_gotoxy(1,4);
                    printf_lcd("?Offset [mV] =");
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
            
            break;
        
        case FORME :
            if((Incremente == true) && (Decremente == false))
            {
                indiceForme ++;
            }
            if((Decremente == true) && (Incremente == false))
            {
                indiceForme --;
            }
            
            if((Pec12IsOK == true)&&(Pec12IsESC == false))
            {
                
            }
            if((Pec12IsESC == true)&&(Pec12IsOK == false))
            {
                
            }
            
            break;
        
        case FREQUENCE :
            if((Incremente == true) && (Decremente == false))
            {
                indiceFrequence ++;
            }
            if((Decremente == true) && (Incremente == false))
            {
                indiceFrequence --;
            }
            
            if((Pec12IsOK == true)&&(Pec12IsESC == false))
            {
                
            }
            if((Pec12IsESC == true)&&(Pec12IsOK == false))
            {
                
            }
            
            break;
        
        case AMPLITUDE :
            if((Incremente == true) && (Decremente == false))
            {
                indiceAmplitude ++;
            }
            if((Decremente == true) && (Incremente == false))
            {
                indiceAmplitude --;
            }
            
            if((Pec12IsOK == true)&&(Pec12IsESC == false))
            {
                
            }
            if((Pec12IsESC == true)&&(Pec12IsOK == false))
            {
                
            }
            
            break;
        
        default :
            
            break;
    }
    
}