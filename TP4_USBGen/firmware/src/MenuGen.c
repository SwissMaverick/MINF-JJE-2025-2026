



#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"

#include "Mc32DriverLcd.h"
#include "GesPec12.h"
#include "GesS9.h"
#include "Mc32NVMUtil.h"
#include "Generateur.h"
#include "app.h"
#include "Mc32gestI2cSeeprom.h"

extern APP_DATA appData;
S_ParamGen valeursParamGen;
const char MenuFormes[4][21] = { " Sinus", " Triangle", " DentDeScie", " Carre" };
// Initialisation du menu et des param?tres
void MENU_Initialize(S_ParamGen *pParam)
{
    lcd_gotoxy(2,1);
    printf_lcd("Forme =%10s ",MenuFormes[pParam->Forme]);

    lcd_gotoxy(2,2);
    printf_lcd("Freq [Hz] = %4d  ",pParam->Frequence);

    lcd_gotoxy(2,3);
    printf_lcd("Ampl [mV] = %5d",pParam->Amplitude);

    lcd_gotoxy(2,4);
    printf_lcd("Offset [mV] = %4d",pParam->Offset);
}

#define CHOIX 0
#define MODIFICATION 1
#define SAUVEGARDE 2

    static uint8_t Menu_Mode = CHOIX; // Variable de la machine d'etat du menu
    
// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam, bool remote_status)
{
    
    static uint8_t menu_select = 0; 
    static bool enable_cpt = 0; //variable qui active le compteur du menu de sauvegarde
    static bool saving_mode = 0; // variable pour afficher une seule fois le menu de sauvegarde
    static uint8_t Saving_counter = 0; // Variable de comptage pour le menu de sauvegarde
    static S_ParamGen buffer;
   
    static int index; //index etant utiliser dans les boucles for
    static uint8_t first_time = 0;   // Variable indiquant si on est au premier passage

    
    // Initialisation lors du premier passage
    if(!first_time)
    {
        // Initialisation du menu
        MENU_Initialize(pParam);
        //mise a 1 de la valeur du premier passage
        first_time++;
    }
    
    switch (Menu_Mode){
        //dans le cas ou l'on doit choisir quoi modifier
        case CHOIX :
            if ( Pec12IsPlus()) { // test si incrémentation
                Pec12ClearPlus(); // reset di flag d'incrementation du pec12
                
                //si la selection du menu n'est pas au max
                if(menu_select < 3)
                    //incrementation
                    menu_select ++;
                else
                    //remise a 0 de la variable
                    menu_select = 0;
            }

            if ( Pec12IsMinus() ) { // test si décrémentation
                Pec12ClearMinus();// reset di flag de decrementation du pec12

                //si la selection du menu n'est pas au min
                if(menu_select > 0)
                    //decrementation
                    menu_select --;
                else
                    //remise au max de la variable
                    menu_select = 3;
            }

            if(Pec12IsOK()){ //test si bouton pec 12 ok
                Pec12ClearOK(); // reset du flag OK du bouton pec12
                Menu_Mode = MODIFICATION; //menu en mode modification de variable

                //mise en memoire de toutes les valeurs actuelles dans un buffer
                buffer.Forme = pParam->Forme; 
                buffer.Frequence = pParam->Frequence;
                buffer.Amplitude = pParam->Amplitude;
                buffer.Offset = pParam->Offset;
            }
            if(S9IsOK()||S9IsESC() ){ //test si bouton S9 est ok ou esc
                //clear des flags relatif a l'appuie du bouton S9
                S9ClearESC();    
                S9ClearOK();
                //reset du flag d'inactivité
                Pec12ClearInactivity(); 
                //passage en mode sauvegade
                if(remote_status == false)
                Menu_Mode = SAUVEGARDE;
            }
            break;
        case MODIFICATION :
            if(Pec12IsESC()){ //sorti du mode de modification sans sauvegarde
                Pec12ClearESC(); //clear du flag du bouton S9 
                Menu_Mode = CHOIX;
            }

            if ( Pec12IsPlus()) { // test si incrémentation
                Pec12ClearPlus(); // reset di flag d'incrementation du pec12
                switch (menu_select) {
                    case 0 :  //forme
                        //si la valeur à modifier n'est pas au max
                        if(buffer.Forme < 3){
                            buffer.Forme++;//incrementation
                        }
                        else{
                            buffer.Forme = 0;//remise a 0 de la variable
                        }
                        break;
                    case 1 : //freq
                        //si la valeur à modifier n'est pas au max
                        if(buffer.Frequence < 2000){
                            buffer.Frequence +=20;//incrementation
                        }
                        //si la valeur a modifier est au max
                        else if(buffer.Frequence == 2000){
                            buffer.Frequence = 0;//remise a 0 de la variable
                        }
                        break;
                    case 2: //ampli
                        //si la valeur à modifier n'est pas au max
                        if(buffer.Amplitude < 10000){
                            buffer.Amplitude+=100;//incrementation
                        }
                        break;
                    case 3 : //offset
                        //si la valeur à modifier n'est pas au max
                        if(buffer.Offset < 5000){
                            buffer.Offset+=100;//incrementation
                        }
                        break;
                    }
            }

            if ( Pec12IsMinus()) { // test si décrémentation
                Pec12ClearMinus(); // reset di flag de decrementation du pec12
                switch (menu_select) {
                    case 0 :  //forme
                        //si la valeur à modifier n'est pas au min
                        if(buffer.Forme > 0){
                            buffer.Forme--;//decrementation
                        }
                        else{
                            buffer.Forme = 3;
                        }
                        break;
                    case 1 : //freq
                        //si la valeur à modifier n'est pas au min
                        if(buffer.Frequence > 20){
                            buffer.Frequence -=20;//decrementation
                        }
                        //si la valeur à modifier est a 0
                        else if(buffer.Frequence == 0){
                            buffer.Frequence = 2000; //remise au max de la variable
                        }
                        break;
                    case 2: //ampli
                        //si la valeur à modifier n'est pas au min
                        if(buffer.Amplitude >= 100){
                            buffer.Amplitude-=100;//decrementation
                        }
                        break;
                    case 3 : //offset
                        //si la valeur à modifier n'est pas au min
                        if(buffer.Offset > -5000){
                            buffer.Offset-=100;//decrementation
                        }
                        break;
                    }
            }

            if(Pec12IsOK()){ //test si bouton pec 12 ok
                Pec12ClearOK(); //clear du flag ok du bouton pec12

                //validation des nouvelles valeur et retour dans le choix de la valeur a modifier
                Menu_Mode = CHOIX;
                pParam->Forme = buffer.Forme;
                pParam->Frequence = buffer.Frequence;
                pParam->Amplitude = buffer.Amplitude;
                pParam->Offset = buffer.Offset;

                //update du signal et de la periode
                GENSIG_UpdateSignal(&buffer);
                GENSIG_UpdatePeriode(&buffer);
            }
    
            break;
        case SAUVEGARDE :
            if(saving_mode == 0){ //si c'est la premiere fois,
                saving_mode = 1; //modification de la variable pour n'afficher le menu qu'une seule fois

                //clear et affichage sur le LCD
                lcd_ClearLine(1);
                lcd_ClearLine(2);
                lcd_ClearLine(3);
                lcd_ClearLine(4);
                lcd_gotoxy(4,2);
                printf_lcd("sauvegarde ?");
                lcd_gotoxy(4,3);
                printf_lcd("(appuie long)");
            }
            if(remote_status == false){
                if(S9IsESC()){ //si le bouton S9 est ESC
                    S9ClearESC(); //clear du flag EST du bouton S9
                    //affichage du message sur le lcd
                    lcd_ClearLine(3);
                    lcd_gotoxy(2,2);
                    printf_lcd("Sauvegarde OK !");
                    //ecriture de la valeur a sauvegarder dans la flash
                    I2C_WriteSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
                    //active le compteur pour le menu de sauvegarde
                    enable_cpt = 1;
                }
                else if(Pec12IsMinus()||Pec12IsOK()||Pec12IsPlus()||Pec12IsESC()||S9IsOK()){ //si un autre bouton à été activer,
                    //clear de tout les flags
                    Pec12ClearOK();
                    Pec12ClearMinus();
                    Pec12ClearPlus();
                    Pec12ClearESC();
                    S9ClearOK();
                    //affichage du message sur le lcd
                    lcd_ClearLine(3);
                    lcd_gotoxy(1,2);
                    printf_lcd("Sauvegarde ANNULEE");
                    //active le compteur pour le menu de sauvegarde
                    enable_cpt = 1;
                }
                break;
            }
            if(remote_status == true){
                lcd_ClearLine(3);
                lcd_gotoxy(2,2);
                printf_lcd("Sauvegarde OK !");
                //ecriture de la valeur a sauvegarder dans la flash
                I2C_WriteSEEPROM((uint32_t*)pParam,MCP79411_EEPROM_BEG, sizeof(S_ParamGen));
                enable_cpt = 1;
            }
    }

    
    if(enable_cpt == 1){ //si le compteur est activé,
        if(Saving_counter >= 200){ //si le compteur à fini de compter
            Menu_Mode = CHOIX; //retour au mode de selection de la valeur a modifier
            //reset de toutes les variables relative a la sauvegarde
            Saving_counter =0 ;
            saving_mode = 0;
            enable_cpt = 0;
        }
        else{ //si le compteur n'est pas fini, continu de compter
            Saving_counter ++;
        }
    }

    if(remote_status == true){
        if(pParam->Forme != buffer.Forme ||
           pParam->Frequence != buffer.Frequence ||
           pParam->Amplitude != buffer.Amplitude ||
           pParam->Offset != buffer.Offset){
            
                buffer.Forme = pParam->Forme; 
                buffer.Frequence = pParam->Frequence;
                buffer.Amplitude = pParam->Amplitude;
                buffer.Offset = pParam->Offset;
                //update du signal et de la periode
                GENSIG_UpdateSignal(&buffer);
                GENSIG_UpdatePeriode(&buffer);
        }
    }
    //si le menu est en mode de modification ou de selection
    if(Menu_Mode == CHOIX || Menu_Mode == MODIFICATION){
        if(remote_status == true){
            for(index =1; index <=4; index ++){
                lcd_gotoxy(1,index);
                printf_lcd("#");
                affichage_LCD(pParam);
            }
        }
        else{
            //efface la premiere ligne de toute les colones
            for(index =1; index <=4; index ++){
                lcd_gotoxy(1,index);
                printf_lcd(" ");
            }
            //ecrit le * ou ? en fonction de ou nous sommes.
            lcd_gotoxy(1,(menu_select+1));
            if(Menu_Mode == CHOIX ){
                printf_lcd("*");
                affichage_LCD(pParam);
            }
            if(Menu_Mode == MODIFICATION ){
                printf_lcd("?");
                affichage_LCD(&buffer);
            }
        }
    }

}

//fonction qui affiche les valeurs selons ce qui est demander dans la données
void affichage_LCD(S_ParamGen *pParam){

    lcd_gotoxy(2,1);
    printf_lcd("Forme =%10s ",MenuFormes[pParam->Forme]);

    lcd_gotoxy(2,2);
    printf_lcd("Freq [Hz] = %4d ",pParam->Frequence);

    lcd_gotoxy(2,3);
    printf_lcd("Ampl [mV] = %5d  ",pParam->Amplitude);

    lcd_gotoxy(2,4);
    printf_lcd("Offset [mV] = %4d",pParam->Offset);
}

void MENU_DemandeSave(void){
    Menu_Mode = SAUVEGARDE;
}