#include <Arduino.h>

const uint8_t RELAY_PIN = 26;
const int RELAY_ON = LOW;

void InitRelay() {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, !RELAY_ON);
}

bool IsShopVacOn() {
    return digitalRead(RELAY_PIN) == RELAY_ON;
}

void TurnOnShopVac() {
  Serial.println("Turning on the shop vac");

  digitalWrite(RELAY_PIN, RELAY_ON);
}

void TurnOffShopVac(int d) {
  Serial.println("Turning off the shop vac");
      
  for (int i = d; i > 0; i--) {
    Serial.printf("%d\n", i);
    delay(1000);
  }

  digitalWrite(RELAY_PIN, !RELAY_ON);
}