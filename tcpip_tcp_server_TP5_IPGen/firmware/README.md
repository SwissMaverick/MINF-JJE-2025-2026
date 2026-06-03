# Changements éffectués dans app.c
## Modification 1  
```C
lcd_gotoxy(1,4);
printf_lcd("IP:%03d.%03d.%03d.%03d", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
```
Affichage de l'adresse IP lorsque celle-ci change  
  
## Modification 2  
```C
// Perform the operation on each data byte
for(w2 = 0; w2 < wCurrentChunk; w2++)
{
    i = AppBuffer[w2];
    if(i == '!' )
    {
        GetMessage((int8_t*)AppBuffer , &paramGen, &appData.saveTodo);

        APP_GEN_SetParam(&paramGen); // passage des parametre
                    
        APP_GEN_DemandeUpdate(); // demande de mise a jour des parametre
                        
        if(appData.saveTodo == true)
        {
            appData.saveTodo = false;
            APP_GEN_DemandeSave(); // demande de sauvegarde
            appData.Saved = true;          
        }
        else
        {
            appData.Saved = false;
        }
                        
        /********************************************************************************************  <---  SEND */
        APP_GEN_GetParam (&paramGen);
        SendMessage((int8_t*)AppBuffer,&paramGen, appData.Saved );

        // Transfer the data out of our local processing buffer and into the TCP TX FIFO.
        SYS_CONSOLE_PRINT("Server Sending %s\r\n", AppBuffer);

        TCPIP_TCP_ArrayPut(appData.socket, AppBuffer, wCurrentChunk);
    }
    else if(i == '\e')   //escape
    {
        appData.state = APP_TCPIP_CLOSING_CONNECTION;
        SYS_CONSOLE_MESSAGE("Connection was closed\r\n");
    }
}
```
Réception du début de la trame par le caractère "!". Réception de la trame entière par "GetMessage".  Enregistrement des paramètres ainsi que gestion du mode de sauvegarde dans l'EEPROM.  
À la fin de la réception du message, renvoi de la trame au client en ajoutant la lettre "P" dans la trame.  
Exemple : 
```C
!S=TF=2000A=10000O=+5000WP=0# 
```  
Si l'utilisateur appuie sur "Esc", la connection s'interromp.
  
## Modification 3  
```C
// Transfer the data out of our local processing buffer and into the TCP TX FIFO.
SYS_CONSOLE_PRINT("Server Sending %s\r\n", AppBuffer);
TCPIP_TCP_ArrayPut(appData.socket, AppBuffer, wCurrentChunk);
```
Enlèvement de ces lignes
