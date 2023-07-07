#include "Arduino.h"
#define GPIO_A1 6
#define GPIO_A2 4
#define GPIO_B1 2
#define GPIO_B2 1

#define PWM_A1 0
#define PWM_A2 1
#define PWM_B1 2 
#define PWM_B2 3
void setup(){
// PWM ON A1
   ledcSetup(PWM_A1, 5000, 8);
   ledcAttachPin(GPIO_A1, PWM_A1);
//PWM A2
  ledcSetup(PWM_A2, 5000, 8);
  ledcAttachPin(GPIO_A2, PWM_A2);
//PWM B1
  ledcSetup(PWM_B1, 5000, 8);
  ledcAttachPin(GPIO_B1, PWM_B1);
//PWM B2
  ledcSetup(PWM_B2, 5000, 8);
  ledcAttachPin(GPIO_B2, PWM_B2);

}
void avancer(uint8_t pourcentage) {
  uint8_t vitesse = static_cast<uint8_t>(((static_cast<float>(pourcentage) / 100) * 55) + 200);
  ledcWrite(PWM_A1, vitesse);
  ledcWrite(PWM_A2, 0);
  ledcWrite(PWM_B1, vitesse);
  ledcWrite(PWM_B2, 0);
}
void droite(uint8_t pourcentage) {
   uint8_t vitesse = static_cast<uint8_t>(((static_cast<float>(pourcentage) / 100) * 55) + 200);
  ledcWrite(PWM_A1, 0);
  ledcWrite(PWM_A2, vitesse);
  ledcWrite(PWM_B1, vitesse);
  ledcWrite(PWM_B2, 0);
  }
  void gauche(uint8_t pourcentage) {
   uint8_t vitesse = static_cast<uint8_t>(((static_cast<float>(pourcentage) / 100) * 55) + 200);
  ledcWrite(PWM_A1, vitesse);
  ledcWrite(PWM_A2, 0);
  ledcWrite(PWM_B1, 0);
  ledcWrite(PWM_B2, vitesse);
  }
void reculer(uint8_t pourcentage) {
   uint8_t vitesse = static_cast<uint8_t>(((static_cast<float>(pourcentage) / 100) * 55) + 200);
  ledcWrite(PWM_A1, 0);
  ledcWrite(PWM_A2, vitesse);
  ledcWrite(PWM_B1, 0);
  ledcWrite(PWM_B2, vitesse);
}

void loop(){

  avancer(0);
  delay(1000);

  droite(0);
  delay(500);
  
  avancer(100);
  delay(1000);
  
  gauche(50);
  delay(1000);
}
