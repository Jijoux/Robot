## Capteur VL53LOX-V2

C'est un capteur laser de type TOF (Time of Flight) qui envoie une lumière laser et mesure son temps de retour pour en déduire la distance de l'objet qui reflète cette lumière.
Il est capable de mesurer à environs 2 mètres de distance.
Il coute environs 1,50€.

Il fonctionne en I2C, un protocol très connu en électronique, qui est notamment utilisé dans les ordinateurs pour communiquer avec les différentes sondes de température.
L'I2C fonctionne avec 2 cables : SDA et SCL.


### Cablage

Nous allons le cabler comme ceci :

- VIN => 3.3V (alimentation)
- GND => GND (alimentation)
- SCL => GPIO 8 (SCL => horloge)
- SDA => GPIO 10 (SDA => données)


### Préparation

Nous allons commencer simplement avec un capteur.

1. Brancher le capteur sur l'ESP32-S2
1. Renommer le fichier `main.cpp` en `main.cpp.old` pour ne pas mélanger l'ancien code avec le nouveau
1. Créer un nouveau fichier `main.cpp` et y ajouter l'include d'`Arduino.h` et les fonctions `setup` et `loop` (vides pour le moment)
1. Télécharger et installer la librairie qui va gérer le capteur VL53LOX : `pio pkg install --library "pololu/VL53L0X@^1.3.1"`


### Tests


#### Utiliser le port série

L'ESP32-S2 est relié à l'ordinateur via un cable USB et utilise le protocol "série".
Ce protocol permet d'envoyer le firmware (le programme) depuis l'ordinateur vers l'ESP32-S2.

Il permet aussi d'envoyer de la donnée depuis l'ESP32-S2 vers l'ordinateur.
Cela va nous permettre d'envoyer du texte depuis l'ESP32-S2 vers l'ordinateur.

Voici un exemple à tester :

```cpp
#include <Arduino.h>

void setup() {
  // Initialiser le port série avec une vitesse de 9600 bauds
  Serial.begin(9600);
}

void loop() {
  // Envoyer du texte vers le port série
  Serial.println("Je suis l'ESP et j'envoie des données à l'ordinateur via le port série");

  // Attendre une seconde
  delay(1000);
}
```

Envoyer le code sur l'ESP32-S2 puis lancer la console série : `pio device monitor`.
Ceci doit afficher le texte sur la console toutes les secondes.
