# Changements éffectués dans app.c
## Ajout 1  

```C
lcd_gotoxy(1,4);
printf_lcd("IP:%03d.%03d.%03d.%03d", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
```
Affichage de l'adresse IP lorsque celle-ci change
