// GesPec12.c  Canevas pour réalisation  
// C. HUBER    09/02/2015

// Fonctions pour la gestion du Pec12
//
//
// Principe : Il est nécessaire d'appeler cycliquement la fonction ScanPec12
//            avec un cycle de 1 ms
//
//  Pour la gestion du Pec12, il y a 9 fonctions à disposition :
//       Pec12IsPlus       true indique un nouveau incrément
//       Pec12IsMinus      true indique un nouveau décrément
//       Pec12IsOK         true indique action OK
//       Pec12IsESC        true indique action ESC
//       Pec12NoActivity   true indique abscence d'activité sur PEC12
//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
//       Pec12ClearMinus   annule indication de décrément
//       Pec12ClearOK      annule indication action OK
//       Pec12ClearESC     annule indication action ESC
//
//
//---------------------------------------------------------------------------


// définitions des types qui seront utilisés dans cette application

#include "GesPec12.h"
#include "Mc32Debounce.h"
#include "Mc32DriverLcd.h"
#include "Mc32gestSpiDac.h"
#include "app.h"

// Descripteur des sinaux
S_SwitchDescriptor DescrA;
S_SwitchDescriptor DescrB;
S_SwitchDescriptor DescrPB;

// Structure pour les traitement du Pec12
S_Pec12_Descriptor Pec12;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Principe utilisation des fonctions
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
// ScanPec12 (bool ValA, bool ValB, bool ValPB)
//              Routine effectuant la gestion du Pec12
//              recoit la valeur des signaux et du boutons
//
// s'appuie sur le descripteur global.
// Après l'appel le descripteur est mis à jour

// Comportement du PEC12
// =====================

// Attention 1 cran génère une pulse complète (les 4 combinaisons)
// D'ou traitement uniquement au flanc descendand de B

// Dans le sens horaire CW:
//     __________                      ________________
// B:            |____________________|
//     ___________________                       _________
// A:                     |_____________________|                    

// Dans le sens anti-horaire CCW:
//     ____________________                      _________
// B:                      |____________________|
//     __________                       __________________
// A:            |_____________________|        

void ScanPec12 (bool ValA, bool ValB, bool ValPB)
{
    uint8_t B_Pressed;
    uint8_t A;
    uint8_t Val_PB;
    static uint8_t Val_PB_Old;
    //uint16_t PushButtonCounter;
    //uint16_t ActivityCounter;
    
   /* Traitement antirebond sur A, B et PB */
   DoDebounce (&DescrA, ValA);
   DoDebounce (&DescrB, ValB);
   DoDebounce (&DescrPB, ValPB);
   
   B_Pressed = DebounceIsPressed(&DescrB);
   DebounceClearPressed(&DescrB);
   
   DebounceClearReleased(&DescrB);
   
   Val_PB = DebounceGetInput(&DescrPB);
   A = DebounceGetInput(&DescrA);
   
   /* Détection incrément / décrément */
   if(B_Pressed == 1)
   {
       Pec12ClearInactivity();
       
       if(A == 1)
       {
           
           Pec12.Dec = 1;
           
           Pec12.Inc = 0;
           BSP_LEDToggle(BSP_LED_4);
       }
       else
       {
           
           Pec12.Inc = 1;
           
           Pec12.Dec = 0;
           BSP_LEDToggle(BSP_LED_5);
       }
   }
    
   /* Traitement du PushButton */
   /* Mise en place d'un compteur pour savoir combien de temps le bouton reste pressé */
   //La valeur du compteur reste en revanche à revoir
   if(Val_PB == 0)
   {
       Pec12.PressDuration ++;
       Pec12ClearInactivity(); // Maintient l'écran allumé
   }
   else if (Val_PB == 1 && Val_PB_Old == 0) 
   {
   // Relâchement du bouton détecté (Flanc descendant)
   if(Pec12.PressDuration > 0 && Pec12.PressDuration < 500) 
   {
       Pec12.OK = 1; // Action OK [cite: 202, 204]
       BSP_LEDToggle(BSP_LED_7);
   } 
   else if(Pec12.PressDuration >= 500) 
   {
       Pec12.ESC = 1; // Action ESC [cite: 203, 205]
       BSP_LEDToggle(BSP_LED_6);
   }
    
   // On réinitialise le compteur pour la prochaine pression
   Pec12.PressDuration = 0;
   }
   
   Val_PB_Old = Val_PB; // Mémorisation de l'état pour le prochain cycle
   
   /* Gestion inactivité */
   //La valeur du compteur reste en revanche à revoir
   /*if((Val_PB == Val_PB_Old) && (A = A_Old) && (B_Pressed == B_Released) && (ActivityCounter == 5000))
   {
       //Eteindre rétroéclairage
       Pec12.InactivityDuration = 0;
       Pec12.NoActivity = 1;
   }
   else
   {
       Pec12.InactivityDuration ++;
       Pec12.NoActivity = 0;
   }*/

   
 } // ScanPec12 


void Pec12Init (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA);
   DebounceInit(&DescrB);
   DebounceInit(&DescrPB);
   
   // Init de la structure PEc12
    Pec12.Inc = 0;             // événement incrément  
    Pec12.Dec = 0;             // événement décrément 
    Pec12.OK = 0;              // événement action OK
    Pec12.ESC = 0;             // événement action ESC
    Pec12.NoActivity = 0;      // Indication d'activité
    Pec12.PressDuration = 0;   // Pour durée pression du P.B.
    Pec12.InactivityDuration = 0; // Durée inactivité
  
 } // Pec12Init





//       Pec12IsPlus       true indique un nouveau incrément
bool Pec12IsPlus    (void) {
   return (Pec12.Inc);
}

//       Pec12IsMinus      true indique un nouveau décrément
bool Pec12IsMinus    (void) {
   return (Pec12.Dec);
}

//       Pec12IsOK         true indique action OK
bool Pec12IsOK    (void) {
   return (Pec12.OK);
}

//       Pec12IsESC        true indique action ESC
bool Pec12IsESC    (void) {
   return (Pec12.ESC);
}

//       Pec12NoActivity   true indique abscence d'activité sur PEC12
bool Pec12NoActivity    (void) {
   return (Pec12.NoActivity);
}

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incrément
void Pec12ClearPlus   (void) {
   Pec12.Inc = 0;
}

//       Pec12ClearMinus   annule indication de décrément
void Pec12ClearMinus   (void) {
   Pec12.Dec = 0;
}

//       Pec12ClearOK      annule indication action OK
void Pec12ClearOK   (void) {
   Pec12.OK = 0;
}

//       Pec12ClearESC     annule indication action ESC
void Pec12ClearESC   (void) {
   Pec12.ESC = 0;
}

void Pec12ClearInactivity   (void) {
  Pec12.NoActivity = 0;
  Pec12.InactivityDuration = 0;
}


