// GesPec12.c  Canevas pour r?alisation  
// C. HUBER    09/02/2015

// Fonctions pour la gestion du Pec12
//
//
// Principe : Il est n?cessaire d'appeler cycliquement la fonction ScanPec12
//            avec un cycle de 1 ms
//
//  Pour la gestion du Pec12, il y a 9 fonctions ? disposition :
//       Pec12IsPlus       true indique un nouveau incr?ment
//       Pec12IsMinus      true indique un nouveau d?cr?ment
//       Pec12IsOK         true indique action OK
//       Pec12IsESC        true indique action ESC
//       Pec12NoActivity   true indique abscence d'activit? sur PEC12
//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incr?ment
//       Pec12ClearMinus   annule indication de d?cr?ment
//       Pec12ClearOK      annule indication action OK
//       Pec12ClearESC     annule indication action ESC
//
//
//---------------------------------------------------------------------------


// d?finitions des types qui seront utilis?s dans cette application

#include "GesPec12.h"
#include "Mc32Debounce.h"
#include "Mc32DriverLcd.h"

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
// Apr?s l'appel le descripteur est mis ? jour

// Comportement du PEC12
// =====================

// Attention 1 cran g?n?re une pulse compl?te (les 4 combinaisons)
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
   // Traitement antirebond sur A, B et PB
   DoDebounce (&DescrA, ValA);
   DoDebounce (&DescrB, ValB);
   DoDebounce (&DescrPB, ValPB);
    
   //si le bouton est appuyer 
   if(ValPB == 0)
   {
       Pec12.PressDuration++;
       Pec12.NoActivity = 0;
   }
   //si le bouton est relaché
   else if(DebounceIsReleased(&DescrPB))
   {
      //si le bouton est relacher apres le delai de pression longue
       if(Pec12.PressDuration >= PRESSION_LONGUE)
       {
         //on met a 1 la variable d'ESC et on met a 0 la variable OK 
         Pec12.OK = 0;
         Pec12.ESC = 1;
       }
       else
       {
         //on met a 0 la variable d'ESC et on met a 1 la variable OK 
         Pec12.ESC = 0;
         Pec12.OK = 1;
       }
       //dans les cas, on reset le compteur de pression et on reset la variable d'inactivité
       Pec12.PressDuration = 0;
       Pec12.NoActivity = 0;
   }

   //dans le cas ou on incremente,
   else if(DebounceIsPressed(&DescrB) && (DebounceGetInput(&DescrA) == 0))
   {
      //on met a 1 la variable d'incrementation, on met a 0 la variable de decrementation et on reset l'inactivité
      Pec12.Inc = 1;
      Pec12.Dec = 0;
      Pec12.NoActivity = 0;
   }

   else if(DebounceIsPressed(&DescrB) && (DebounceGetInput(&DescrA) == 1))
   {
      //on met a 0 la variable d'incrementation, on met a 1 la variable de decrementation et on reset l'inactivité
      Pec12.Inc = 0;
      Pec12.Dec = 1;
      Pec12.NoActivity = 0;
   }

   DebounceClearPressed(&DescrB);
   DebounceClearReleased(&DescrB);

   DebounceClearPressed(&DescrPB);
   DebounceClearReleased(&DescrPB);
   
   if(Pec12.NoActivity)
   {
       if(Pec12.InactivityDuration >= TEMPS_INACTIVITE)
       {
         //si on est inactif depuis trop longtemps, on eteint le backlight
           //lcd_bl_off();    
       }
       else
       {
         //si on est inactif depuis peu, on incremente un compteur pour savoir depuis quand on l'est.
           Pec12.InactivityDuration++;
       }
   }
   else
   {
      //si il y a eu de l'activité,
      //on r'allume le backlight et on reset les variables de non activité
       Pec12.NoActivity = 1;
       Pec12.InactivityDuration = 0;
       lcd_bl_on();    
   }
  
   
 } // ScanPec12


void Pec12Init (void)
{
   // Initialisation des descripteurs de touches Pec12
   DebounceInit(&DescrA);
   DebounceInit(&DescrB);
   DebounceInit(&DescrPB);
   
   // Init de la structure PEc12
    Pec12.Inc = 0;             // ?v?nement incr?ment  
    Pec12.Dec = 0;             // ?v?nement d?cr?ment 
    Pec12.OK = 0;              // ?v?nement action OK
    Pec12.ESC = 0;             // ?v?nement action ESC
    Pec12.NoActivity = 0;      // Indication d'activit?
    Pec12.PressDuration = 0;   // Pour dur?e pression du P.B.
    Pec12.InactivityDuration = 0; // Dur?e inactivit?
  
 } // Pec12Init


//       Pec12IsPlus       true indique un nouveau incr?ment
bool Pec12IsPlus    (void) {
   return (Pec12.Inc);
}

//       Pec12IsMinus      true indique un nouveau d?cr?ment
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

//       Pec12NoActivity   true indique abscence d'activit? sur PEC12
bool Pec12NoActivity    (void) {
   return (Pec12.NoActivity);
}

//  Fonctions pour quittance des indications
//       Pec12ClearPlus    annule indication d'incr?ment
void Pec12ClearPlus   (void) {
   Pec12.Inc = 0;
}

//       Pec12ClearMinus   annule indication de d?cr?ment
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

//      Pec12ClearInactivity    Clear l'inactivit?
void Pec12ClearInactivity   (void) {
  Pec12.NoActivity = 0;
  Pec12.InactivityDuration = 0;
}