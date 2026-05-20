// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms



#include <stdint.h>
#include <stdbool.h>
#include "Mc32DriverLcd.h"
#include "MenuGen.h"
#include "Generateur.h"
#include "Mc32gestI2cSeeprom.h"

// Curseur global contenant l'etat du menu (mode, champ, sous-menu, valeur modifiee)
static S_Curseur selection;

// **************************************************************************
// Initialisation du menu et des parametres
// **************************************************************************
// Cette fonction prepare la structure interne du menu. Elle est appelee une
// seule fois au demarrage de l'application.
// **************************************************************************
void MENU_Initialize(S_ParamGen *pParam)
{
    selection.Menu = 0;   // Le menu principal est selectionne au lancement
    selection.Champ = 1;
}


// **************************************************************************
// MENU_Execute
// Fonction centrale du systeme de menu. Elle doit etre appelee cycliquement.
// Elle gere :
//   - les actions du codeur PEC12 (OK, ESC, rotation)
//   - la navigation dans les menus
//   - l'edition des parametres
//   - la sauvegarde via S9
//   - l'affichage
// **************************************************************************
void MENU_Execute(S_ParamGen *pParam, bool local)
{
    
    if(local)//DEBUT Gestion Local
    {
        /**************************************************************************/
        // GESTION DES BOUTONS OK / ESC SELON LE MODE COURANT
        // NAV  : navigation entre les champs
        // EDIT : modification d'un parametre
        /**************************************************************************/
        if((selection.Menu == MAIN_MENU) || (selection.Menu == SUB_MENU_EDIT)){
            switch (selection.Mode)
            {
                case NAV:
                    // Passage en mode edition si OK est presse
                    if (Pec12IsOK())
                    {
                        selection.Mode = EDIT;
                        selection.Menu = SUB_MENU_EDIT;

                        // Chargement des valeurs actuelles dans la structure de travail
                        GET_ParamInt16Champ(pParam, &selection);
                        GET_ParamForme(pParam, &selection);
                    }
                    break;

                case EDIT:
                    // Validation des modifications
                    if (Pec12IsOK())
                    {
                        selection.Mode = NAV;
                        selection.Menu = MAIN_MENU;

                        // Application des valeurs modifiees
                        SET_ParamInt16Champ(pParam, &selection);
                        SET_ParamForme(pParam, &selection);

                        // Mise a jour du signal genere
                        GENSIG_UpdateSignal(pParam);
                        GENSIG_UpdatePeriode(pParam);
                    }

                    // Annulation des modifications
                    if (Pec12IsESC())
                    {
                        selection.Mode = NAV;
                        selection.Menu = MAIN_MENU;
                    }
                    break;
            }

            // Remise a zero des evenements OK / ESC
            Pec12ClearOK();
            Pec12ClearESC();


            /**************************************************************************/
            // GESTION DE LA ROTATION DU CODEUR (PLUS / MOINS)
            // Selon le menu courant, la rotation permet soit :
            //   - de changer de champ (MAIN_MENU)
            //   - de modifier une valeur (SUB_MENU_EDIT)
            /**************************************************************************/
            switch (selection.Menu)
            {
                case MAIN_MENU:
                    // Navigation entre les champs
                    if (Pec12IsPlus())
                    {
                        if (selection.Champ < CHAMP_END) selection.Champ++;
                        else selection.Champ = CHAMP_START;
                    }

                    if (Pec12IsMinus())
                    {
                        if (selection.Champ > CHAMP_START) selection.Champ--;
                        else selection.Champ = CHAMP_END;
                    }
                    break;

                case SUB_MENU_EDIT:
                    // Edition du champ selectionne
                    switch (selection.Champ)
                    {
                        case FORME:
                            EDIT_ParamForme(&(selection.formeModif), BUTEE);
                            break;

                        case FREQ:
                            EDIT_ParamInt16(&(selection.valeurModif),FREQ_MAX, FREQ_MIN,INC_FREQ, REBOUCLEMENT);
                            break;

                        case AMPL:
                            EDIT_ParamInt16(&(selection.valeurModif),AMP_MAX, AMP_MIN,INC_AMP, REBOUCLEMENT);
                            break;

                        case OFFSET:
                            EDIT_ParamInt16(&(selection.valeurModif),OFFSET_MAX, OFFSET_MIN,INC_OFFSET, BUTEE);
                            break;
                    }
                    break;
                    case SUB_MENU_SAVE:
                        break;
                    case SUB_MENU_SAVE_OK:
                        break;
                    case SUB_MENU_SAVE_ESC:
                        break;
            }

            Pec12ClearPlus();
            Pec12ClearMinus();
        }

        /**************************************************************************/
        // GESTION DU MENU DE SAUVEGARDE VIA LE BOUTON S9
        // Appui court  : entrer / sortir du menu de sauvegarde
        // Appui long   : effectuer la sauvegarde 
        /**************************************************************************/
        switch (selection.Menu)
        {
            case SUB_MENU_SAVE:
                if (S9IsPressed())
                { 
                   selection.Menu = SUB_MENU_SAVE_ESC;
                }


                if (S9IsLongPressed())
                {         
                        selection.Menu = SUB_MENU_SAVE_OK;
                        //NVM_WriteBlock((uint32_t*)pParam, sizeof(S_ParamGen));

                        I2C_WriteSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
                }

                break;

            default:
                // Acces au menu de sauvegarde
                if (S9IsPressed())
                {
                    selection.Menu = SUB_MENU_SAVE;
                }
                break;
        }

        S9ClearPressed();
        S9ClearLongPressed();

    }//FIN Gestion Local
    
    /**************************************************************************/
    // GESTION DE LA DUREE DU MESSAGE DU CHOIX DE LA SAUVGARDE
    // Temps d'affichage definis par SAVE_AFFICHAGE_CYCLE (n x 10ms)
    /**************************************************************************/
    static uint16_t countCycle = ZERO;
    //gestion du timeout pour le message du choix de la sauvegarde
    if ((countCycle < SAVE_AFFICHAGE_CYCLE )&&((selection.Menu == SUB_MENU_SAVE_ESC)||(selection.Menu == SUB_MENU_SAVE_OK)))
    {
        countCycle++;  
    }
    else if((countCycle >= SAVE_AFFICHAGE_CYCLE )&&((selection.Menu == SUB_MENU_SAVE_ESC)||(selection.Menu == SUB_MENU_SAVE_OK)))
    { 
        // Retour au menu principal
        selection.Menu = MAIN_MENU;
        countCycle = ZERO;
    }

    /**************************************************************************/
    // AFFICHAGE DU MENU
    // Cette fonction gere l'affichage complet du menu et du pointeur
    /**************************************************************************/
    MENU_Affichage(pParam, &selection, local);
}


// **************************************************************************
// EDIT_ParamForme
// Incremente ou decremente la forme du signal selon la rotation du codeur.
// **************************************************************************
void EDIT_ParamForme(E_FormesSignal* pParamForme, bool rebouclement)
{
    /**************************************************************************/
    // Rotation vers la droite
    /**************************************************************************/
    if (Pec12IsPlus())
    {
        switch (*pParamForme)
        {
            case SignalSinus:       *pParamForme = SignalTriangle; 
                break;
            case SignalTriangle:    *pParamForme = SignalDentDeScie; 
                break;
            case SignalDentDeScie:  *pParamForme = SignalCarre; 
                break;
            case SignalCarre:       if (rebouclement) *pParamForme = SignalSinus; 
                break;
        }
    }

    /**************************************************************************/
    // Rotation vers la gauche
    /**************************************************************************/
    if (Pec12IsMinus())
    {
        switch (*pParamForme)
        {
            case SignalSinus:       if (rebouclement) *pParamForme = SignalCarre; 
                break;
            case SignalTriangle:    *pParamForme = SignalSinus; 
                break;
            case SignalDentDeScie:  *pParamForme = SignalTriangle; 
                break;
            case SignalCarre:       *pParamForme = SignalDentDeScie; 
                break;
        }
    }
}


// **************************************************************************
// EDIT_ParamInt16
// Edition generique d'un entier 16 bits avec bornes et rebouclement optionnel.
// **************************************************************************
void EDIT_ParamInt16(int16_t* pParamInt16,int32_t valeurMax,int32_t valeurMin,int32_t pasIncrement,bool rebouclement)
{
    /**************************************************************************/
    // Rotation vers la droite
    /**************************************************************************/
    if (Pec12IsPlus())
    {
        if (*pParamInt16 < valeurMax) *pParamInt16 += pasIncrement;
        else if (rebouclement)        *pParamInt16 = valeurMin;
        else                          *pParamInt16 = valeurMax;
    }

    /**************************************************************************/
    // Rotation vers la gauche
    /**************************************************************************/
    if (Pec12IsMinus())
    {
        if (*pParamInt16 > valeurMin) *pParamInt16 -= pasIncrement;
        else if (rebouclement)        *pParamInt16 = valeurMax;
        else                          *pParamInt16 = valeurMin;
    }
}


// **************************************************************************
// GET_ParamInt16Champ
// Charge dans la structure curseur la valeur du champ selectionne.
// **************************************************************************
void GET_ParamInt16Champ(S_ParamGen *pParam, S_Curseur *pselection)
{
    switch (pselection->Champ)
    {
        case FORME:  pselection->valeurModif = (int16_t)pParam->Frequence; 
            break;
        case FREQ:   pselection->valeurModif = pParam->Frequence; 
            break;
        case AMPL:   pselection->valeurModif = pParam->Amplitude; 
            break;
        case OFFSET: pselection->valeurModif = pParam->Offset; 
            break;
    }
}


// **************************************************************************
// SET_ParamInt16Champ
// Applique la valeur modifiee au parametre reel.
// **************************************************************************
void SET_ParamInt16Champ(S_ParamGen *pParam, S_Curseur *pselection)
{
    switch (pselection->Champ)
    {
        case FORME:  pParam->Forme = (E_FormesSignal)pselection->valeurModif; 
            break;
        case FREQ:   pParam->Frequence = pselection->valeurModif; 
            break;
        case AMPL:   pParam->Amplitude = pselection->valeurModif; 
            break;
        case OFFSET: pParam->Offset = pselection->valeurModif; 
            break;
    }
}


// **************************************************************************
// GET / SET ParamForme
// **************************************************************************
void GET_ParamForme(S_ParamGen *pParam, S_Curseur *pselection)
{
    pselection->formeModif = pParam->Forme;
}

void SET_ParamForme(S_ParamGen *pParam, S_Curseur *pselection)
{
    pParam->Forme = pselection->formeModif;
}


// **************************************************************************
// MENU_Affichage
// Gere l'affichage complet du menu et du pointeur de selection.
// **************************************************************************
void MENU_Affichage(S_ParamGen *pParam, S_Curseur *pselection, bool local)
{
    /**************************************************************************/
    // AFFICHAGE DES VALEURS SELON LE MENU COURANT
    /**************************************************************************/
    switch (pselection->Menu )
    {
        case MAIN_MENU:
            lcd_gotoxy(2,1);
            AffichageForme(pParam->Forme);

            lcd_gotoxy(2,2);
            printf_lcd("Freq [Hz]   = %5d", pParam->Frequence);

            lcd_gotoxy(2,3);
            printf_lcd("Ampl [mV]   = %5d", pParam->Amplitude);

            lcd_gotoxy(2,4);
            printf_lcd("Offset [mV] = %+5d", pParam->Offset);
            break;

        case SUB_MENU_EDIT:
            if (pselection->Champ == FORME)
            {
                lcd_gotoxy(2, pselection->Champ);
                AffichageForme(pselection->formeModif);
            }
            else
            {
                lcd_gotoxy(16, pselection->Champ);
                printf_lcd("%5d", pselection->valeurModif);
            }
            break;

        case SUB_MENU_SAVE:
            lcd_ClearLine(1);
            lcd_gotoxy(1,2);
            printf_lcd("   Sauvegarde ?     ");
            lcd_gotoxy(1,3);
            printf_lcd("   appui long       ");
            lcd_ClearLine(4);
            break;
        case SUB_MENU_SAVE_OK:
            lcd_ClearLine(1);
            lcd_gotoxy(1,2);
            printf_lcd("        OK!         ");
            lcd_ClearLine(3);
            lcd_ClearLine(4);
            break;
        case SUB_MENU_SAVE_ESC :
            lcd_ClearLine(1);
            lcd_gotoxy(1,2);
            printf_lcd("      ANNULEE !     ");
            lcd_ClearLine(3);
            lcd_ClearLine(4);
            break;
                    
    }

    /**************************************************************************/
    // AFFICHAGE DU POINTEUR (* en NAV, ? en EDIT)
    /**************************************************************************/
    uint8_t champ;
    for (champ = 1; champ <= NBCHAMP; champ++)
    {
        lcd_gotoxy(1, champ);
        if ((champ == pselection->Champ) && ((selection.Menu == MAIN_MENU) || (selection.Menu == SUB_MENU_EDIT)) && local)
        {
            switch (pselection->Mode)
            {
                case NAV:  printf_lcd("*"); 
                    break;
                case EDIT: printf_lcd("?"); 
                    break;
            }
        }
        else if (local)
        {
            printf_lcd(" ");
        }
        else if (selection.Menu == SUB_MENU_SAVE_OK)
        {
           //afficha rien
           //printf_lcd("#");
        }
        else
        {
            printf_lcd("#");
        }
    }
}


// **************************************************************************
// AffichageForme
// Affiche le nom de la forme du signal.
// **************************************************************************
void AffichageForme(E_FormesSignal forme)
{
    /**************************************************************************/
    switch (forme)
    {
        case SignalSinus:       printf_lcd("Forme = %11s", SINUS); 
            break;
        case SignalTriangle:    printf_lcd("Forme = %11s", TRIANGLE); 
            break;
        case SignalDentDeScie:  printf_lcd("Forme = %11s", DENTDESCIE); 
            break;
        case SignalCarre:       printf_lcd("Forme = %11s", CARRE); 
            break;
    }
    /**************************************************************************/
}

// **************************************************************************
// MENU_DemandeSave
// **************************************************************************
// Sauvegard des parametre actuelle dans la memoire de l'SEEPROM 
// **************************************************************************
bool MENU_Save(S_ParamGen *pParam)
{
    //S_ParamGen ControleParam;
    bool saved = false;
    I2C_WriteSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
    selection.Menu = SUB_MENU_SAVE_OK;
    
    
//    I2C_ReadSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
//    selection.Menu = SUB_MENU_SAVE_OK;
//    if(ControleParam.Magic == MAGIC)
//    {
//            saved = true;
//    }
     saved = true;
    return saved;
}



    

















