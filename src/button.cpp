#include <Arduino.h>

#include <relay.h>

const uint8_t BUTTON_PIN = 13;

const int BUTTON_ON = HIGH;
int buttonState = !BUTTON_ON;
int lastState = !BUTTON_ON;

void InitButton() {
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
}

bool IsButtonActive() {
  return digitalRead(BUTTON_PIN) == BUTTON_ON ||
    lastState == BUTTON_ON;
}

void DoButtonAction() {
  buttonState = digitalRead(BUTTON_PIN);
  // Button has changed
  if (lastState != buttonState) {
    if (buttonState == BUTTON_ON) {
      TurnOnShopVac();
    } else {
      TurnOffShopVac(1);
    }

    lastState = buttonState;
  }
}
