#include <Arduino.h>

int getMaxValue(int sensorPin, int sampleTime) {
    int sensorMax = 0;
    uint32_t start_time = millis();
    
    while((millis()-start_time) < sampleTime) {
        int sensorValue = analogRead(sensorPin);
        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }
    }

    return sensorMax;
}