#ifndef MenuGen_h
#define MenuGen_h

// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  03.02.2016
// Fichier MenuGen.h
// Gestion du menu  du gÃ©nÃ©rateur
// Traitement cyclique Ã  1 ms du Pec12


#include <stdbool.h>
#include <stdint.h>

#include "GesPec12.h"
#include "DefMenuGen.h"


// *************************************************************************
// Constantes de configuration du menu
// *************************************************************************

#define REBOUCLEMENT true     // Autorise le retour a la valeur minimale/maximale
#define BUTEE false           // Bloque la valeur aux bornes

#define CHAMP_START 1         // Premier champ du menu
#define CHAMP_END   4         // Dernier champ du menu
#define NBCHAMP     4         // Nombre total de champs affichables

#define SAVE_AFFICHAGE_CYCLE 200 // Nombre de cycle a afficher le message de sauvegarde
#define ZERO 0

// *************************************************************************
// Bornes et increments des parametres modifiables
// *************************************************************************

#define FREQ_MAX  2000        // Frequence maximale en Hz
#define FREQ_MIN  20          // Frequence minimale en Hz
#define INC_FREQ  20          // Pas d'increment de frequence

#define AMP_MAX   10000       // Amplitude maximale en mV
#define AMP_MIN   0           // Amplitude minimale en mV
#define INC_AMP   100         // Pas d'increment d'amplitude

#define OFFSET_MAX   5000     // Offset maximal en mV
#define OFFSET_MIN  -5000     // Offset minimal en mV
#define INC_OFFSET   100      // Pas d'increment d'offset

// *************************************************************************
// Enumerations representant les differents etats du menu
// *************************************************************************

// Mode de fonctionnement du menu : navigation ou edition
typedef enum
{
    NAV = 0,      // Navigation entre les champs
    EDIT,         // Edition d'un parametre
} e_MODE;

// Champs modifiables du menu
typedef enum
{
    FORME = 1,    // Forme du signal
    FREQ,         // Frequence
    AMPL,         // Amplitude
    OFFSET,       // Offset
} e_CHAMP;

// Sous-menus disponibles
typedef enum
{
    MAIN_MENU = 0,    // Menu principal
    SUB_MENU_EDIT,    // Sous-menu d'edition
    SUB_MENU_SAVE,    // Sous-menu de sauvegarde
    SUB_MENU_SAVE_OK, // Sauvegarde OK    
    SUB_MENU_SAVE_ESC,// Sauvegarde Annulé     
} e_MENU;

// *************************************************************************
// Structure du curseur de menu
// *************************************************************************
// Cette structure contient l'etat courant du menu :
//   - Champ selectionne
//   - Menu actif
//   - Mode (NAV / EDIT)
//   - Valeur en cours de modification
//   - Forme en cours de modification
// *************************************************************************
typedef struct 
{
    e_CHAMP Champ;            // Champ selectionne
    e_MENU Menu;              // Menu actif
    e_MODE Mode;              // Mode NAV ou EDIT

    int16_t valeurModif;      // Valeur temporaire lors de l'edition
    E_FormesSignal formeModif;// Forme temporaire lors de l'edition

} S_Curseur;


// *************************************************************************
// Prototypes des fonctions du module Menu
// *************************************************************************

// Initialisation du menu et des parametres
void MENU_Initialize(S_ParamGen *pParam);

// Fonction principale du menu, appelee cycliquement
void MENU_Execute(S_ParamGen *pParam, bool local);

// Fonction d'affichage du menu
void MENU_Affichage(S_ParamGen *pParam, S_Curseur *pselection, bool local);

// Fonction de sauvegarde des paramètre
void MENU_DemandeSave(S_ParamGen *pParam);

// Edition generique d'un entier 16 bits d'un des parametres 
void EDIT_ParamInt16(int16_t* pParamInt16,int32_t valeurMax,int32_t valeurMin,int32_t pasIncrement,bool rebouclement);

// Chargement generique d'un entier 16 bits d'un des parametres 
void GET_ParamInt16Champ(S_ParamGen *pParam, S_Curseur *pselection);

// Application generique d'un entier 16 bits d'un des parametres 
void SET_ParamInt16Champ(S_ParamGen *pParam, S_Curseur *pselection);

// Edition de la forme du signal
void EDIT_ParamForme(E_FormesSignal *pParamForme, bool rebouclement);

// Chargement de la forme du signal
void GET_ParamForme(S_ParamGen *pParam, S_Curseur *pselection);

/// application de la forme du signal
void SET_ParamForme(S_ParamGen *pParam, S_Curseur *pselection);

// Affichage de la forme du signal
void AffichageForme(E_FormesSignal forme);

bool MENU_Save(S_ParamGen *pParam);

#endif



  
   







