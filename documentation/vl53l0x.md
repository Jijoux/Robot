## Capteur VL53L0X

C'est un capteur laser de type TOF (Time of Flight) qui envoie une lumière laser et mesure son temps de retour pour en déduire la distance de l'objet qui reflète cette lumière.
Il est capable de mesurer à environs 2 mètres de distance.
Il coute environs 1,50€.

Il fonctionne en I2C, un protocol très connu en électronique, qui est notamment utilisé dans les ordinateurs pour communiquer avec les différentes sondes de température.
L'I2C fonctionne avec 2 cables : SDA et SCL.


### Cablage

Nous allons le cabler comme ceci :

- VIN => 3.3V (alimentation)
- GND => GND (alimentation)
- SCL => GPIO 9 (SCL => horloge)
- SDA => GPIO 8 (SDA => données)


### Préparation

Nous allons commencer simplement avec un capteur.

1. Brancher le capteur sur l'ESP32-S2
1. Renommer le fichier `main.cpp` en `main.cpp.old` pour ne pas mélanger l'ancien code avec le nouveau
1. Créer un nouveau fichier `main.cpp` et y ajouter l'include d'`Arduino.h` et les fonctions `setup` et `loop` (vides pour le moment)
1. Télécharger et installer la librairie qui va gérer le capteur VL53L0X : `pio pkg install --library "pololu/VL53L0X@^1.3.1"`
  ⚠️ TODO: il faut aussi ajouter Wire, en l'ajoutant dans `platformio.ini`


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


#### Tester le capteur

```cpp
#include <Arduino.h>

// Charger les librairies nécessaires au capteur VL53L0X
#include <Wire.h>
#include <VL53L0X.h>

// Créer une instance de la librairie "VL53L0X" dans la variable "sensor"
VL53L0X sensor;


void setup() {
  // Initialiser le port série avec une vitesse de 9600 bauds
  Serial.begin(9600);

  // Initialiser la librairie "Wire" (nécessaire pour I2C)
  Wire.begin(8, 9);

  // Initialiser le capteur. En cas de retour négatif, afficher une erreur sur le port série.
  sensor.setTimeout(500);
  if (!sensor.init()) {
    while (1) {
      Serial.println("Failed to detect and initialize sensor!");
      delay(1000);
    }
  }

  // Configurer le capteur pour retourner une mesure toutes les 100ms
  sensor.startContinuous(100);
}


void loop() {
  // Lire la valeur mesurée par le capteur
  uint16_t sensorValue = sensor.readRangeContinuousMillimeters();

  // Afficher une erreur dans le cas où le capteur ne répond pas dans le temps imparti
  if (sensor.timeoutOccurred()) {
    Serial.println("Sensor timeout!");
  }
  else {
    // Afficher la valeur retournée par le capteur
    Serial.print("Valeur mesurée : ");
    Serial.println(sensorValue);
  }

  // Attendre 100ms
  delay(100);
}
```