TP4\_MINF
=========

Explication complementaire gestion memoire de l'EEPROM
------------------------------------------------------

#### Fonction

```C
void I2C_InitMCP79411(void)
{
   bool Fast = true;
   i2c_init( Fast );
}
```

---

#### Explication

Cette fonction initialise la communication I2C.

```C
bool Fast = true;
```

Cette variable permet de demander une initialisation en mode rapide.

Ensuite :

```C
i2c_init(Fast);
```

configure le module I2C du microcontrôleur.

---

Écriture dans l'EEPROM
----------------------

### Fonction complète

Extrait de code

```C
void I2C_WriteSEEPROM(void *SrcData, uint32_t EEpromAddr, uint16_t NbBytes)
```

#### Paramètres

| Paramètre  | Description                     |
| ---------- | ------------------------------- |
| SrcData    | Adresse des données à écrire    |
| EEpromAddr | Adresse de départ dans l'EEPROM |
| NbBytes    | Nombre d'octets à écrire        |

### Boucle principale d'écriture

Extrait de code

```C
for(y = 0; y <= (NbBytes/8); y++)
```

L'EEPROM fonctionne par pages mémoire de 8 octets.

Cette boucle s'exécute pour chaque page nécessaire à l'écriture globale.

### Calcul du nombre d'octets à écrire

Extrait de code

```C
if(y == (NbBytes/8))  {      NbBytesPage = NbBytes - 8*(y);  }  else  {      NbBytesPage = 8;  }
```

Cette partie définit combien d'octets seront écrits lors du passage actuel.

#### Deux cas possibles

| Situation                       | Action                                           |
| ------------------------------- | ------------------------------------------------ |
| Dernière page à écrire          | Le programme calcule les octets restants précis  |
| Page intermédiaire ou de départ | Le programme écrit une page complète de 8 octets |

### Prévention des transactions vides

Extrait de code

```C
if (NbBytesPage == 0)   {      break;   }
```

Si le nombre d'octets total est un multiple de 8.

La dernière exécution de la boucle calculera 0 octet à écrire.

Cette instruction coupe la boucle pour éviter d'ouvrir une communication I2C inutile.

### Attente de disponibilité du composant

Extrait de code

```C
do  {      i2c_start();  } while(!i2c_write(MCP79411_EEPROM_W));
```

Après une écriture, l'EEPROM grave les données en interne.

Pendant ce temps, elle refuse de communiquer (NACK).

Le programme utilise un "Repeated Start" pour relancer la demande jusqu'à ce que le composant réponde (ACK).

### Envoi de l'adresse mémoire

Extrait de code

```C
i2c_write((uint8_t)EEpromAddr + (y * 8));
```

Cette instruction envoie l'adresse de destination dans l'EEPROM.

L'adresse est décalée de 8 en 8 automatiquement à chaque nouvelle page.

#### Exemple

| Adresse de départ | y                 | Adresse actuelle  |
| ----------------- | ----------------- | ----------------- |
| 0                 | 0                 | 0                 |
| 0                 | 1                 | 8                 |
| 0                 | 2                 | 16                |

### Envoi des données

Extrait de code

```C
for(i = 0; i < NbBytesPage; i++)  {     i2c_write(i2cData[i+(y*8)]);  }
```

Cette boucle envoie les octets un par un pour la page courante.

L'index de lecture cible la bonne donnée dans le tableau source.

### Fin de transmission

Extrait de code

```C
i2c_stop();
```

Cette instruction termine la communication I2C et libère le bus.

Elle déclenche physiquement la gravure de la page à l'intérieur de la puce.

Lecture dans l'EEPROM
---------------------

### Fonction complète

Extrait de code

```C
void I2C_ReadSEEPROM(void *DstData, uint32_t EEpromAddr, uint16_t NbBytes)
```

### Attente de disponibilité

Extrait de code

```C
do  {      i2c_start();      ack = i2c_write(MCP79411_EEPROM_W);  } while (ack == false);
```

Le programme attend que l'EEPROM soit disponible avant de commencer.

Cela évite un plantage si une sauvegarde vient tout juste de se terminer.

### Envoi de l'adresse à lire

Extrait de code

```C
i2c_write(EEpromAddr);
```

Permet d'indiquer au composant l'adresse de départ de la lecture.

### Restart I2C

Extrait de code

```C
i2c_reStart();
```

Le restart permet de conserver le contrôle du bus sans envoyer de STOP.

Cela permet d'enchaîner directement avec la phase de réception.

### Passage en mode lecture

Extrait de code

```C
i2c_write(MCP79411_EEPROM_R);
```

Le composant reçoit l'ordre et passe en mode émetteur.

### Lecture des données

Extrait de code

```C
for(i = 0; i < NbBytes; i++)
```

Boucle principale de réception des octets.

Contrairement à l'écriture, il n'y a pas de limite de page en lecture.

### Gestion des ACK et NACK

#### Cas normal (Octets intermédiaires)

Extrait de code

```C
pointeur[i] = i2c_read(true);
```

Le microcontrôleur stocke la donnée et envoie un ACK (true).

Cela signifie que le PIC a bien reçu les données et que l'EEPROM peut envoyer la suite.

#### Dernier octet

Extrait de code

```C
if (i == (NbBytes - 1))   {      pointeur[i] = i2c_read(false);   }
```

Pour la dernière donnée réclamée, le microcontrôleur envoie un NACK (false).

Cela signifie une lecture terminée

Cette étape est obligatoire pour que le composant arrête d'émettre.

### Fin de lecture

Extrait de code

```C
i2c_stop();
```

Termine la communication I2C proprement et libère le bus.

Explication complementaire decodage de la trame
-----------------------------------------------

Le decodage peut se faire en plusieurs étape pouvant mener a une détection d'erreur.

### 1\. Reperage du debut et fin de trame

dans un premiere temps,

Extrait de code

```C
if(USBReadBuffer[0] =='!')
```

Va regarder si il y a bien le debut de la trame qui est un "!".

ensuite,

Extrait de code

```C
for(index = 0; index <= appData.numBytesRead; index++){      if(USBReadBuffer[index] == '#'){          validation = 1;      }  }
```

Nous allons scanner la trame complète pour trouver s'il y'a le caractere de fin de trame qui est "#".

Si c'est le cas, la trame est conciderée comme valide pour la prochaine étape

### 2\. Repérage des débuts de chaque information

Etant donné que nous devons trouver les infos suivantes :

| Information dans la trame | Caractere qui defini l'information |
| ------------------------- | ---------------------------------- |
| formes                    | S                                  |
| frequence                 | F                                  |
| amplitude                 | A                                  |
| offset                    | O                                  |
| sauvegarde                | W                                  |

Une fois que nous avons trouvé un des caractères qui défini l'information, nous remplacons ce caractère par "\\0" pour définir une fin de chaine.

Nous enregistrons aussi la position dans le tableau de caractères du debut de la valeur numérique.

Extrait de code

```C
for(index = 0; index <= appData.numBytesRead; index++){              if(USBReadBuffer[index] == 'S' && first_S_found == false){                  start_signal = index +2;                  first_S_found = true;                  USBReadBuffer[index] = '\0';              }          }
```

#### Important !

Nous devons faire un "+2" pour trouver le debut d'une valeur car la trame etant xxxF=3000xxxx, nous trouvons la valeur de F a l'adresse 3 et le debut du 3000 a l'adresse 5.

Autre information importante, nous devons avoir une vérification pour trouver si un "S" a été vu car le sinus etant defini aussi par "S", il sera detecté et supprimér ce qui nous fera perdre l'information du sinus.

### 3\. Optention des informations grace a atoi

La fonction atoi est une fonction permettant de transformer une chaine de caractere en int.

En lui donnant une chaine de caractères, la fonction va du début de la chaine jusqu'au caractere de fin de chaine de caractere "\\0", mais il est aussi possible de faire commencer la lecture au milieu d'une chaine donnée.

Comme ci dessus, nous commencons la lecture de l'amplitude au debut de l'amplitude et la fonction va lire jusqu'au caractere de fin mis a la place du debut de la trame de l'offset.

Ce qui fait que nous lirons uniquement la valeur qui nous interesse.
