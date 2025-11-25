Fréquence de clock = 80MHz

Notre but, faire une interruption toutes les 100ms/10Hz.

Pour le prescaler, la valeur la plus grande possible à été choisie, à savoir 256.

Après le prescaler, la fréquence de clock passe à 312,5kHz.

Pour arriver à 10Hz, il faut rediviser par 31'250. On prendra donc un compteur allant jusqu'à 31'249. 
Cette valeur est expliquée par le fait que le compteur commence par 0.

Le passage par le pescaler puis par le compteur provoque une interruption toutes les 100ms.