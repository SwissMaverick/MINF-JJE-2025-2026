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


const char MenuFormes[4][21] = {"Sinus", "Triangle", "DentDeScie", "Carre"};

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
    static int16_t backupValeur = 0;
    // static uint16_t valeurTest = 50;
    
    Incremente = Pec12IsPlus();
    if (Incremente) Pec12ClearPlus();

    Decremente = Pec12IsMinus();
    if (Decremente) Pec12ClearMinus();

    OK = Pec12IsOK();
    if (OK) Pec12ClearOK();

    ESC = Pec12IsESC();
    if (ESC) Pec12ClearESC();
    
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
            // 1. Mise à jour de TOUT l'affichage des curseurs
            // L'opérateur (condition) ? 'Vrai' : 'Faux' permet de choisir le caractère
            lcd_gotoxy(1,1); 
            printf_lcd("%cForme =         ", (indiceAsterisque == 0) ? '*' : ' ');
            
            lcd_gotoxy(1,2); 
            printf_lcd("%cFreq [Hz] =     ", (indiceAsterisque == 1) ? '*' : ' ');
            
            lcd_gotoxy(1,3); 
            printf_lcd("%cAmpl [mV] =     ", (indiceAsterisque == 2) ? '*' : ' ');
            
            lcd_gotoxy(1,4); 
            printf_lcd("%cOffset [mV] =   ", (indiceAsterisque == 3) ? '*' : ' ');

            // J'ai ajouté des espaces après les "=" pour être sûr d'effacer 
            // d'éventuels vieux caractères restés sur l'écran.

            // 2. Logique de navigation (une seule fois suffit !)
            if((Incremente == 1) && (indiceAsterisque < 3))
            {
                indiceAsterisque++;
            }
            if((Decremente == 1) && (indiceAsterisque > 0))
            {
                indiceAsterisque--;
            }
            
            // 3. Validation
            if(OK == 1)
            {
                etatActuel = EDIT;
                indiceEdit = indiceAsterisque;
            }
            
            break;
            
        case EDIT :
            
            // --- AFFICHAGE ---
            lcd_gotoxy(1,1); 
            printf_lcd("%cForme = %-10s", (indiceEdit == 0) ? '?' : ' ', MenuFormes[pParam->Forme]);
            lcd_gotoxy(1,2); 
            printf_lcd("%cFreq [Hz] = %-4d  ", (indiceEdit == 1) ? '?' : ' ', pParam->Frequence);
            lcd_gotoxy(1,3); 
            printf_lcd("%cAmpl [mV] = %-5d ", (indiceEdit == 2) ? '?' : ' ', pParam->Amplitude);
            lcd_gotoxy(1,4); 
            printf_lcd("%cOffset[mV]= %-5d ", (indiceEdit == 3) ? '?' : ' ', pParam->Offset);

            // --- SELECTION DU PARAMETRE A MODIFIER ---
            if(OK == 1)
            {
                // On mémorise la valeur actuelle au cas où l'utilisateur fait ESC
                if (indiceEdit == 0)
                {
                    backupValeur = pParam->Forme;
                    etatActuel = FORME;
                }
                if (indiceEdit == 1)
                {
                    backupValeur = pParam->Frequence;
                    etatActuel = FREQUENCE;
                }
                if (indiceEdit == 2)
                {
                    backupValeur = pParam->Amplitude;
                    etatActuel = AMPLITUDE;
                }
                if (indiceEdit == 3)
                {
                    backupValeur = pParam->Offset;
                    etatActuel = OFFSET;
                }
            }
            if(ESC == 1)
            {
                etatActuel = SELECT; // Annule l'édition et remet l'étoile
            }
            
            break;

        case FORME :
            
            if((Incremente == 1) && (pParam->Forme < 3))
            {
                pParam->Forme++;
            }
            if((Decremente == 1) && (pParam->Forme > 0))
            {
                pParam->Forme--;
            }
            
            // L'affichage se mettra à jour en temps réel si on retourne temporairement dans EDIT
            lcd_gotoxy(1,1); 
            printf_lcd("?Forme = %-10s", MenuFormes[pParam->Forme]);

            if(OK == 1)
            {
                etatActuel = SELECT;
                // Appel de la fonction pour mettre à jour le signal généré [cite: 91]
                // GENSIG_UpdateSignal(pParam); 
            }
            if(ESC == 1)
            {
                pParam->Forme = backupValeur;
                etatActuel = SELECT;
            }
                    
            break;
                    
        case FREQUENCE :
            
            if(Incremente == 1)
            {
                pParam->Frequence += 20;
            }
            if(Decremente == 1)
            {
                pParam->Frequence -= 20;
            }
            
            // Rebouclement selon la donnée [cite: 63, 64]
            if(pParam->Frequence < 20)
            {
                pParam->Frequence = 2000;
            }
            if(pParam->Frequence > 2000)
            {
                pParam->Frequence = 20;
            }
            
            lcd_gotoxy(1,2); 
            printf_lcd("?Freq [Hz] = %-4d  ", pParam->Frequence);

            if(OK == 1)
            {
                etatActuel = SELECT;
                // Appel de la fonction pour modifier la période du timer [cite: 89, 90]
                // GENSIG_UpdatePeriode(pParam);
            }
            if(ESC == 1)
            {
                pParam->Frequence = backupValeur;
                etatActuel = SELECT;
            }
                    
            break;
                    
        case AMPLITUDE :
            
            if(Incremente == 1)
            {
                pParam->Amplitude += 100;
            }
            if(Decremente == 1)
            {
                pParam->Amplitude -= 100;
            }
            
            // Rebouclement selon la donnée [cite: 70]
            if(pParam->Amplitude < 0)
            {
                pParam->Amplitude = 10000;
            }
            if(pParam->Amplitude > 10000)
            {
                pParam->Amplitude = 0;
            }
            
            lcd_gotoxy(1,3); 
            printf_lcd("?Ampl [mV] = %-5d ", pParam->Amplitude);

            if(OK == 1)
            {
                etatActuel = SELECT;
                // Appel de la fonction pour mettre à jour le signal généré [cite: 91]
                // GENSIG_UpdateSignal(pParam);
            }
            if(ESC == 1)
            {
                pParam->Amplitude = backupValeur;
                etatActuel = SELECT;
            }
            
            break;
                    
        case OFFSET :
            
            if(Incremente == 1)
            {
                pParam->Offset += 100;
            }
            if(Decremente == 1)
            {
                pParam->Offset -= 100;
            }
                    
            // Butée (Pas de rebouclement) selon la donnée [cite: 75]
            if(pParam->Offset < -5000)
            {
                pParam->Offset = -5000;
            }
            if(pParam->Offset > 5000)
            {
                pParam->Offset = 5000;
            }
            
            lcd_gotoxy(1,4); 
            printf_lcd("?Offset[mV]= %-5d ", pParam->Offset);

            if(OK == 1)
            {
                etatActuel = SELECT;
                // Appel de la fonction pour mettre à jour le signal généré [cite: 91]
                // GENSIG_UpdateSignal(pParam);
            }
            if(ESC == 1)
            {
                pParam->Offset = backupValeur;
                etatActuel = SELECT;
            }
            
            break;
        
        default :
            
            break;
    }
}