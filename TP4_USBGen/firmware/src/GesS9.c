/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "GesS9.h"
#include "GesPec12.h"
#include "Mc32Debounce.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

S_SwitchDescriptor DescrS9;

S_Pec12_Descriptor S9;
/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */


void ScanS9(bool ValS9)
{
   // Traitement antirebond
   DoDebounce (&DescrS9, ValS9);
   
   //si le bouton est appuyer 
   if(ValS9 == 0)
   {
       S9.PressDuration++;
   }
   
   //si le bouton est relaché
   if(DebounceIsReleased(&DescrS9))
   {
       //si le bouton est relacher apres le delai de pression longue
       if(S9.PressDuration >= PRESSION_LONGUE)
       {
           //on met a 1 la variable d'ESC et on met a 0 la variable OK 
           S9.ESC = 1;
           S9.OK = 0;
       }
       else
       {
           //on met a 0 la variable d'ESC et on met a 1 la variable OK 
           S9.OK = 1;
           S9.ESC = 0;
       }
       S9.PressDuration = 0;    //dans les cas, on reset le compteur de pression
   }


   DebounceClearPressed(&DescrS9);
   DebounceClearReleased(&DescrS9);
}

//       S9IsOK         true indique action OK
bool S9IsOK    (void) {
   return (S9.OK);
}

//       S9IsESC        true indique action ESC
bool S9IsESC    (void) {
   return (S9.ESC);
}

//       S9ClearOK      annule indication action OK
void S9ClearOK   (void) {
   S9.OK = 0;
}

//       S9ClearESC     annule indication action ESC
void S9ClearESC   (void) {
   S9.ESC = 0;
}

void S9Init (void)
{
   // Initialisation du descripteur de S9
   DebounceInit(&DescrS9);
   
   // Init de la structure S9
    S9.Inc = 0;             // ?v?nement incr?ment  
    S9.Dec = 0;             // ?v?nement d?cr?ment 
    S9.OK = 0;              // ?v?nement action OK
    S9.ESC = 0;             // ?v?nement action ESC
    S9.NoActivity = 0;      // Indication d'activit?
    S9.PressDuration = 0;   // Pour dur?e pression du P.B.
    S9.InactivityDuration = 0; // Dur?e inactivit?
  
 } // Pec12Init

/* *****************************************************************************
 End of File
 */