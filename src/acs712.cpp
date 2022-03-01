#include <Arduino.h>

#include <button.h>
#include <relay.h>

const uint8_t SENSOR_PIN = A4;

const int SAMPLE_TIME_MS = 1000;
const float VOLTAGE_TO_START = 2.20; // You should play with this value during test for better performance in your system.

int currentValue = 0;
float voltage = 0;

int getMaxValue() {
    int sensorMax = 0;
    uint32_t start_time = millis();
    
    while((millis()-start_time) < SAMPLE_TIME_MS) {
        int sensorValue = analogRead(SENSOR_PIN);

        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }
    }

    return sensorMax;
}

void checkConnectedTool() {
if (!isButtonActive()) {
    // Measuaring the tool
    currentValue = getMaxValue();
    Serial.printf("sensor value is %d\n", currentValue);
    voltage = (float) currentValue / 4095 * 3.3;
    Serial.printf("Sensor Voltage is %.2fv\n", voltage);

    // If voltage is above 3.2, the loop should be discarded because it could be a line noise.
    if (voltage <= 3.2) {
      if (voltage >= VOLTAGE_TO_START && !isRelayClosed()) {
        turnOnShopVac();
      } else if (voltage < VOLTAGE_TO_START && isRelayClosed()) {
        turnOffShopVac(5);
      }
    }
  }
}