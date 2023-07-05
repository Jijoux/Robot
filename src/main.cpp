#include "Arduino.h"

#define GPIO_A1 6
#define GPIO_A2 4
#define GPIO_B1 2
#define GPIO_B2 1

#define PWM_A1 0
#define PWM_A2 1
#define PWM_B1 2
#define PWM_B2 3

void setup() {
  Serial.begin(9600);

  // Set PWM "0" (PWM_A1) on GPIO A1 (5kHz, 8 bits resolution)
  ledcSetup(PWM_A1, 5000, 8);
  ledcAttachPin(GPIO_A1, PWM_A1);

  // Set PWM "1" (PWM_A2) on GPIO A2 (5kHz, 8 bits resolution)
  ledcSetup(PWM_A2, 5000, 8);
  ledcAttachPin(GPIO_A2, PWM_A2);

  // Set PWM "2" (PWM_B1) on GPIO B1 (5kHz, 8 bits resolution)
  ledcSetup(PWM_B1, 5000, 8);
  ledcAttachPin(GPIO_B1, PWM_B1);

  // Set PWM "3" (PWM_B2) on GPIO B2 (5kHz, 8 bits resolution)
  ledcSetup(PWM_B2, 5000, 8);
  ledcAttachPin(GPIO_B2, PWM_B2);
}

void forward(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  ledcWrite(PWM_A1, speed);
  ledcWrite(PWM_A2, 0);

  ledcWrite(PWM_B1, speed);
  ledcWrite(PWM_B2, 0);
}

void backward(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  ledcWrite(PWM_A1, 0);
  ledcWrite(PWM_A2, speed);

  ledcWrite(PWM_B1, 0);
  ledcWrite(PWM_B2, speed);
}

void spinCounterClockwise(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  ledcWrite(PWM_A1, 0);
  ledcWrite(PWM_A2, speed);

  ledcWrite(PWM_B1, speed);
  ledcWrite(PWM_B2, 0);
}

void spinClockwise(uint8_t percent) {
  uint8_t speed = static_cast<uint8_t>(((static_cast<float>(percent) / 100) * 55) + 200);

  ledcWrite(PWM_A1, speed);
  ledcWrite(PWM_A2, 0);

  ledcWrite(PWM_B1, 0);
  ledcWrite(PWM_B2, speed);
}

void stop() {
  ledcWrite(PWM_A1, 0);
  ledcWrite(PWM_A2, 0);

  ledcWrite(PWM_B1, 0);
  ledcWrite(PWM_B2, 0);
}

void loop() {
  spinCounterClockwise(0);
  delay(1000);

  spinClockwise(0);
  delay(1000);
}