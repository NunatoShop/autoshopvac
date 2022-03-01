#include <Arduino.h>

#include <button.h>
#include <relay.h>

const uint8_t SENSOR_PIN = A4;

const int SAMPLE_TIME_MS = 1000;

int value = 0;
float voltage = 0;
float startingVoltage = 2.20; // You should play with this value during test for better performance in your system.

/**
 * @brief Get the max value from the sensor during a sample time.
 * 
 * @return int max value.
 */
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

int GetValue() {
  return value;
}

float GetVoltage() {
  return voltage;
}

float GetStartingVoltage() {
  return startingVoltage;
}

void CheckConnectedTool() {
    // Measuaring the tool
    value = getMaxValue();
    Serial.printf("sensor value is %d\n", value);
    voltage = (float) value / 4095 * 3.3;
    Serial.printf("Sensor voltage is %.2fv\n", voltage);

    // If voltage is above 3.2, the loop should be discarded because it could be a line noise.
    if (voltage <= 3.2) {
      if (voltage >= startingVoltage && !IsShopVacOn()) {
        TurnOnShopVac();
      } else if (voltage < startingVoltage && IsShopVacOn()) {
        TurnOffShopVac(5);
      }
    }
}