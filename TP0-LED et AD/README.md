Configuration du timer :
Fréquence de clock = 80MHz
Notre but, faire une interruption toutes les 100ms/10Hz.
Pour le prescaler, la valeur la plus grande possible à été choisie, à savoir 256.
Après le prescaler, la fréquence de clock passe à 312,5kHz.
Pour arriver à 10Hz, il faut rediviser par 31'250. On prendra donc un compteur allant jusqu'à 31'249. 
Cette valeur est expliquée par le fait que le compteur commence par 0.
Le passage par le pescaler puis par le compteur provoque une interruption toutes les 100ms.

Mesure 1 :
<img width="1280" height="824" alt="1  Mesure chenillard 1 LED" src="https://github.com/user-attachments/assets/5a18d83d-acff-4784-bef9-0c9062b64fee" />
Cette mesure montre la durée que met une LED du chennillard à s'allumer.
À noter que les LEDs sont actives bas.
La durée mesurée est de 200ms pour un temps attendu de 200ms

Mesure 2 :
<img width="1280" height="824" alt="2  Mesure chenillard 8 LEDs" src="https://github.com/user-attachments/assets/0552ab22-1ba3-4b18-b95b-f3315f590351" />
Cette mesure montre la durée totale d'un chanillard. Étant donné que les changements de LEDs sont à des intervalles de 200ms et qu'il y en a 8, le temps attendu serait de 1,6s pour l'ensemble.
Le temps mesuré est de 1.6s, ce qui correspond à nos attentes.

Mesure 3 :
<img width="1280" height="824" alt="3  Mesure 3 secondes" src="https://github.com/user-attachments/assets/d07f701b-d101-45e3-b5c5-551322652c8b" />
Cette mesure montre le délai de 3 secondes en début de programme. Il est intéressant de noter qu'il est compliqué de voir la fin de ce délai en regardant uniquement le signal de la LED0. Puisque celle-ci s'éteint puis se rallume directement. Le signal de celle-ci paraît durer plus longtemps que les autres. Il est important de mesurer la fin des 3 secondes au bon endroit pour éviter une erreur de mesure.
Le temps mesuré est de 3.069 secondes contre 3 secondes attendues. La différence est négligeable.
