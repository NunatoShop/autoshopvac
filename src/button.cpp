#include <Arduino.h>

#include <relay.h>

const uint8_t BUTTON_PIN = 13;

const int BUTTON_CLOSE_IN = HIGH;
int lastState = !BUTTON_CLOSE_IN;
int buttonState = !BUTTON_CLOSE_IN;

void initButton() {
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  buttonState = digitalRead(BUTTON_PIN);
}

bool isButtonActive() {
  buttonState = digitalRead(BUTTON_PIN);
  return buttonState == BUTTON_CLOSE_IN;
}

void doButtonAction() {
  buttonState = digitalRead(BUTTON_PIN);
  // Button has changed
  if (lastState != buttonState) {
    if (buttonState == BUTTON_CLOSE_IN) {
      turnOnShopVac();
    } else {
      turnOffShopVac(1);
    }

    lastState = buttonState;
  }
}
