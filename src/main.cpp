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
        if (sensorValue<500)Serial.println("un obstacle est sur le chemin");
    {
        if (sensorValue>500)Serial.println("aucun obstacle sur le chemin");
    }
    
  }
  // Attendre 100ms
  delay(100);
}