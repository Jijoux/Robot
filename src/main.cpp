#include "Arduino.h"

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

// GPIO for TB6612FNG for motor 1
#define MOTOR_1_IN1 35
#define MOTOR_1_IN2 37
#define MOTOR_1_PWM 39

// GPIO for TB6612FNG for motor 2
#define MOTOR_2_IN1 33
#define MOTOR_2_IN2 18
#define MOTOR_2_PWM 16

// PWM for motors
#define PWM_MOTOR_1 0
#define PWM_MOTOR_2 1

void setup() {
  Serial.begin(9600);

  // 100 kHz per default. Can be 400 kHz too. But nothing else.
  while (!Wire.begin(7, 9, 100 * 1000)) {
    Serial.println("Failed to initialize I2C!");
    delay(1000);
  }


  sensor.setTimeout(500);

  // init(true) => 2v8 mode (for 3.3v compatibility). This is the default
  while (!sensor.init(true)) {
    Serial.println("Failed to detect and initialize sensor!");
    delay(1000);
  }

  sensor.startContinuous(100);


  // Set GPIO connected to TB6612FNG as output and low (0)
  pinMode(MOTOR_1_IN1, OUTPUT);
  digitalWrite(MOTOR_1_IN1, 0);

  pinMode(MOTOR_1_IN2, OUTPUT);
  digitalWrite(MOTOR_1_IN2, 0);

  pinMode(MOTOR_2_IN1, OUTPUT);
  digitalWrite(MOTOR_2_IN1, 0);

  pinMode(MOTOR_2_IN2, OUTPUT);
  digitalWrite(MOTOR_2_IN2, 0);


  // PWM for motor 1 (22kHz, 8 bits resolution)
  ledcSetup(PWM_MOTOR_1, 22000, 8);
  ledcAttachPin(MOTOR_1_PWM, PWM_MOTOR_1);

  // PWM for motor 2 (22kHz, 8 bits resolution)
  ledcSetup(PWM_MOTOR_2, 22000, 8);
  ledcAttachPin(MOTOR_2_PWM, PWM_MOTOR_2);
}

void stop() {
  ledcWrite(PWM_MOTOR_1, 255);
  ledcWrite(PWM_MOTOR_2, 255);

  digitalWrite(MOTOR_1_IN1, 0);
  digitalWrite(MOTOR_1_IN2, 0);

  digitalWrite(MOTOR_2_IN1, 0);
  digitalWrite(MOTOR_2_IN2, 0);
}

void forward(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  stop();

  ledcWrite(PWM_MOTOR_1, speed);
  ledcWrite(PWM_MOTOR_2, speed);

  digitalWrite(MOTOR_1_IN1, 1);
  digitalWrite(MOTOR_1_IN2, 0);

  digitalWrite(MOTOR_2_IN1, 1);
  digitalWrite(MOTOR_2_IN2, 0);
}

void backward(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  stop();

  ledcWrite(PWM_MOTOR_1, speed);
  ledcWrite(PWM_MOTOR_2, speed);

  digitalWrite(MOTOR_1_IN1, 0);
  digitalWrite(MOTOR_1_IN2, 1);

  digitalWrite(MOTOR_2_IN1, 0);
  digitalWrite(MOTOR_2_IN2, 1);
}

void spinCounterClockwise(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  stop();

  ledcWrite(PWM_MOTOR_1, speed);
  ledcWrite(PWM_MOTOR_2, speed);

  digitalWrite(MOTOR_1_IN1, 1);
  digitalWrite(MOTOR_1_IN2, 0);

  digitalWrite(MOTOR_2_IN1, 0);
  digitalWrite(MOTOR_2_IN2, 1);
}

void sensorReset() {
  Serial.println("Resetting sensor");

  // bool Wire.begin()

  // Reset the sensor
  sensor.writeReg(VL53L0X::SOFT_RESET_GO2_SOFT_RESET_N, 0x00);
  delay(10);
  // Releasing the reset
  sensor.writeReg(VL53L0X::SOFT_RESET_GO2_SOFT_RESET_N, 0x01);

  // Configuring the sensor
  sensor.setTimeout(500);

  bool sensorInitialization = sensor.init(true);
  if (!sensorInitialization) {
    Serial.println("Failed to detect and initialize sensor!");
    return;
  }
  sensor.startContinuous(100);
}


bool test = false;
void loop() {
  // Lire la valeur mesurée par le capteur
  uint16_t sensorValue = sensor.readRangeContinuousMillimeters();

  // // Afficher une erreur dans le cas où le capteur ne répond pas dans le temps imparti
  // if (sensor.timeoutOccurred()) {
  //   Serial.println("Sensor timeout!");
  //   stop();
  //   sensorReset();
  //   delay(100);
  //   return;
  // }
  // // The sensor seems to return 8191 when there is an error. In that case, we reset it.
  // else if (sensorValue == 8191) {
  //   Serial.println("Sensor error!");
  //   stop();
  //   sensorReset();
  //   delay(100);
  //   return;
  // }

  Serial.println(sensorValue);
  Serial.println(Wire.getClock());



  // if (sensorValue < 200) {
  //   Serial.println("Un obstacle est sur le chemin");
  //   spinCounterClockwise(25);
  // }
  // else {
  //   Serial.println("Aucun obstacle sur le chemin");
  //   forward(25);
  // }

  if (test) {
    forward(25);
  }
  else {
    backward(25);
  }
  test = !test;

  // Attendre 100ms
  delay(250);
}