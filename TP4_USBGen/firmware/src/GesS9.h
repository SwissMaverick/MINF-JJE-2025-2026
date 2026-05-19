/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _GesS9_H    /* Guard against multiple inclusion */
#define _GesS9_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdbool.h>
#include <stdint.h>
/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */

    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */


    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */



void ScanS9(bool ValS9);

//       S9IsOK         true indique action OK
bool S9IsOK (void);
//       S9IsESC        true indique action ESC
bool S9IsESC (void);
//       S9ClearOK      annule indication action OK
void S9ClearOK (void);
//       S9ClearESC     annule indication action ESC
void S9ClearESC (void);
// Initialisation de S9
void S9Init (void);




#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
