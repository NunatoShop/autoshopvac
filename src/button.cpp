#include <Arduino.h>

#include <relay.h>

const uint8_t BUTTON_PIN = 13;

const int BUTTON_CLOSE_IN = HIGH;
int lastState = !BUTTON_CLOSE_IN;
int buttonState = !BUTTON_CLOSE_IN;

void InitButton() {
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  buttonState = digitalRead(BUTTON_PIN);
}

bool IsButtonActive() {
  buttonState = digitalRead(BUTTON_PIN);
  return buttonState == BUTTON_CLOSE_IN;
}

void DoButtonAction() {
  buttonState = digitalRead(BUTTON_PIN);
  // Button has changed
  if (lastState != buttonState) {
    if (buttonState == BUTTON_CLOSE_IN) {
      TurnOnShopVac();
    } else {
      TurnOffShopVac(1);
    }

    lastState = buttonState;
  }
}
