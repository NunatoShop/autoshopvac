#include <Arduino.h>

const int RELAY_CLOSE_IN = LOW;

int initRelay(int relayPin) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, !RELAY_CLOSE_IN);

    return !RELAY_CLOSE_IN;
}

bool isRelayClosed(int relayPin) {
    int relayState = digitalRead(relayPin);
    
    return relayState == RELAY_CLOSE_IN;
}

void turnOnShopVac(int relayPin) {
  Serial.println("Turning on the shop vac");

  digitalWrite(relayPin, RELAY_CLOSE_IN);
}

void turnOffShopVac(int relayPin, int d) {
  Serial.println("Turning off the shop vac");
      
  for (int i = d; i > 0; i--) {
    Serial.printf("%d\n", i);
    delay(1000);
  }

  digitalWrite(relayPin, !RELAY_CLOSE_IN);
}