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
#include "bsp.h"

#define MAGIC_VALUE 0x12345678

// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam)
{
    S_ParamGen paramTemp;
    
    if(paramTemp.Magic == MAGIC_VALUE)
    {
        // Restauration des paramètres sauvegardés
        pParam->Forme = paramTemp.Forme;
        pParam->Frequence = paramTemp.Frequence;
        pParam->Amplitude = paramTemp.Amplitude;
        pParam->Offset = paramTemp.Offset;
        pParam->Magic = paramTemp.Magic;
    }
    else
    {
        // Valeurs par défaut si la mémoire est vide ou corrompue
        pParam->Forme = 0; // Sinus
        pParam->Frequence = 1000;
        pParam->Amplitude = 5000;
        pParam->Offset = 0;
        pParam->Magic = MAGIC_VALUE;
    }
    
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
    
    static uint8_t etatActuel = SELECT;
    static uint8_t indiceAsterisque = 0;
    static int16_t valeurEdit = 0;
    
    static uint16_t saveTimer = 0;
    static uint8_t saveStatus = 0;
    
    Incremente = Pec12IsPlus();
    if(Incremente) 
    {
        Pec12ClearPlus();
    }

    Decremente = Pec12IsMinus();
    if(Decremente)
    {
        Pec12ClearMinus();
    }

    OK = Pec12IsOK();
    if(OK)
    {
        Pec12ClearOK();
    }

    ESC = Pec12IsESC();
    if(ESC)
    {
       Pec12ClearESC();
    }
    
    // Le rétroéclairage s'éteint après 5 secondes
    if(Pec12NoActivity() == 1)
    {
        lcd_bl_off(); // Éteint le rétroéclairage si inactif depuis 5s
    }
    else
    {
        lcd_bl_on();  // Rallume (ou maintient allumé) dès qu'il y a de l'activité
    }
        
    /* Machine d'état menu */
    switch(etatActuel)
    {
        case SELECT :
            // 1. Mise à jour de l'affichage des curseurs
            // L'opérateur (condition) ? 'Vrai' : 'Faux' permet de choisir le caractère
            lcd_gotoxy(1,1);
            if(pParam->Forme <= 3)
            {
                printf_lcd("%cForme = %-10s", (indiceAsterisque == 0) ? '*' : ' ', MenuFormes[pParam->Forme]);
            }
            else
            {
                // Si aucune forme n'est valide/sélectionnée, on n'affiche rien après le =
                printf_lcd("%cForme =           ", (indiceAsterisque == 0) ? '*' : ' ');
            }
            
            lcd_gotoxy(1,2); 
            printf_lcd("%cFreq [Hz] = %-4d  ", (indiceAsterisque == 1) ? '*' : ' ', pParam->Frequence);
            
            lcd_gotoxy(1,3); 
            printf_lcd("%cAmpl [mV] = %-5d ", (indiceAsterisque == 2) ? '*' : ' ', pParam->Amplitude);
            
            lcd_gotoxy(1,4); 
            printf_lcd("%cOffset[mV]= %-5d ", (indiceAsterisque == 3) ? '*' : ' ', pParam->Offset);

            // 2. Logique de navigation
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
                if(indiceAsterisque == 0)
                {
                    valeurEdit = pParam->Forme;
                    etatActuel = FORME; // Remplaçant de ton EDIT
                }
                if(indiceAsterisque == 1)
                {
                    valeurEdit = pParam->Frequence;
                    etatActuel = FREQUENCE;
                }
                if(indiceAsterisque == 2)
                {
                    valeurEdit = pParam->Amplitude;
                    etatActuel = AMPLITUDE;
                }
                if(indiceAsterisque == 3)
                {
                    valeurEdit = pParam->Offset;
                    etatActuel = OFFSET;
                }
            }
            
            break;
            
        case EDIT :
            if(valeurEdit > 3) valeurEdit = 0; // Sécurité si vide
            
            if((Incremente == 1) && (valeurEdit < 3))
            {
                valeurEdit++;
            }
            if((Decremente == 1) && (valeurEdit > 0))
            {
                valeurEdit--;
            }
            
            lcd_gotoxy(1,1); 
            printf_lcd("?Forme = %-10s", MenuFormes[valeurEdit]);

            if(OK == 1)
            {
                pParam->Forme = valeurEdit; // APPLICATION REELLE ICI !
                etatActuel = SELECT;
                GENSIG_UpdateSignal(pParam); 
            }
            if(ESC == 1)
            {
                etatActuel = SELECT; // Annulation : on ne touche pas à pParam->Forme
            }
            break;
                    
        case FORME :
            if(valeurEdit > 3) 
            {
                valeurEdit = 0; // Sécurité si vide
            }
            
            if((Incremente == 1) && (valeurEdit < 3))
            {
                valeurEdit++;
            }
            if((Decremente == 1) && (valeurEdit > 0))
            {
                valeurEdit--;
            }
            
            lcd_gotoxy(1,1); 
            printf_lcd("?Forme = %-10s", MenuFormes[valeurEdit]);

            if(OK == 1)
            {
                pParam->Forme = valeurEdit;
                etatActuel = SELECT;
                GENSIG_UpdateSignal(pParam); 
            }
            if(ESC == 1)
            {
                etatActuel = SELECT;
            }
            break;
            
        case FREQUENCE :
            if(Incremente == 1)
            {
                valeurEdit += 20;
            }
            if(Decremente == 1)
            {
                valeurEdit -= 20;
            }
            
            // Rebouclement selon la donnée [cite: 63, 64]
            if(valeurEdit < 20)
            {
                valeurEdit = 2000;
            }
            if(valeurEdit > 2000)
            {
                valeurEdit = 20;
            }
            
            lcd_gotoxy(1,2); 
            printf_lcd("?Freq [Hz] = %-4d  ", valeurEdit);

            if(OK == 1)
            {
                pParam->Frequence = valeurEdit;
                etatActuel = SELECT;
                GENSIG_UpdatePeriode(pParam);
            }
            if(ESC == 1)
            {
                etatActuel = SELECT;
            }
                    
            break;
                    
        case AMPLITUDE :
            if(Incremente == 1)
            {
                valeurEdit += 100;
            }
            if(Decremente == 1)
            {
                valeurEdit -= 100;
            }
            
            // Rebouclement selon la donnée [cite: 70]
            if(valeurEdit < 0)
            {
                valeurEdit = 10000;
            }
            if(valeurEdit > 10000)
            {
                valeurEdit = 0;
            }
            
            lcd_gotoxy(1,3); 
            printf_lcd("?Ampl [mV] = %-5d ", valeurEdit);

            if(OK == 1)
            {
                pParam->Amplitude = valeurEdit;
                etatActuel = SELECT;
                GENSIG_UpdateSignal(pParam);
            }
            if(ESC == 1)
            {
                etatActuel = SELECT;
            }
            
            break;
                    
        case OFFSET :
            if(Incremente == 1)
            {
                valeurEdit += 100;
            }
            if(Decremente == 1)
            {
                valeurEdit -= 100;
            }
                    
            // Butée (Pas de rebouclement) selon la donnée [cite: 75]
            if(valeurEdit < -5000)
            {
                valeurEdit = -5000;
            }
            if(valeurEdit > 5000)
            {
                valeurEdit = 5000;
            }
            
            lcd_gotoxy(1,4); 
            printf_lcd("?Offset[mV]= %-5d ", valeurEdit);

            if(OK == 1)
            {
                pParam->Offset = valeurEdit;
                etatActuel = SELECT;
                GENSIG_UpdateSignal(pParam);
            }
            if(ESC == 1)
            {
                etatActuel = SELECT;
            }
            
            break;
        
        case SAUVEGARDE_DEMANDE :
            // --- AFFICHAGE DE LA DEMANDE ---
            lcd_gotoxy(1,1); 
            printf_lcd(" Sauvegarde ?       ");
            lcd_gotoxy(1,2); 
            printf_lcd(" (appui long)       ");
            lcd_gotoxy(1,3); 
            printf_lcd("                    "); // Efface la ligne 3
            lcd_gotoxy(1,4); 
            printf_lcd("                    "); // Efface la ligne 4

            // --- LOGIQUE APPUI LONG (Validation) ---
            if(BSP_SwitchStateGet(BSP_SWITCH_3) == 0) // Si le bouton S9 est maintenu
            {
                saveTimer++;
                if(saveTimer >= 100) // 100 cycles de 10ms = 1 seconde d'appui continu
                {
                    saveStatus = 1; // Succès
                    etatActuel = SAUVEGARDE_MESSAGE;
                    saveTimer = 0;
                    
                    // --- ECRITURE EN MEMOIRE NVM ---
                    pParam->Magic = MAGIC_VALUE; // On s'assure que le mot magique est bien là
                    
                    NVM_WriteBlock(pParam); 
                }
            }
            else
            {
                // Si on relâche le bouton avant 1 seconde (Annulation)
                if(saveTimer > 0) 
                {
                    saveStatus = 0; // Annulé
                    etatActuel = SAUVEGARDE_MESSAGE;
                    saveTimer = 0;
                }
            }
            
            if((Incremente == 1) || (Decremente == 1) || (OK == 1) || (ESC == 1))
            {
                 saveStatus = 0;
                 etatActuel = SAUVEGARDE_MESSAGE;
                 saveTimer = 0;
            }
            break;

        case SAUVEGARDE_MESSAGE :
            // --- AFFICHAGE DU RÉSULTAT ---
            lcd_gotoxy(1,1); 
            if(saveStatus == 1)
            {
                printf_lcd(" Sauvegarde OK!     ");
            }
            else
            {
                printf_lcd(" Sauvegarde ANNULEE!");
            }
            lcd_gotoxy(1,2); 
            printf_lcd("                    "); // Efface la ligne du dessous
            
            saveTimer++;
            if(saveTimer >= 200) // 200 cycles de 10ms = 2 secondes
            {
                etatActuel = SELECT;
                saveTimer = 0;
            }
            break;
            
        default :
            
            break;
    }
}