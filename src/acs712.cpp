#include <Arduino.h>

/**
 * Samples for SAMPLE_TIME_MS and get the maximum value from the CURRENT_SENSOR_PIN.
 */
int getMaxValue(int acs712SensorPin, int sampleTime) {
    int sensorMax = 0;
    uint32_t start_time = millis();
    
    while((millis()-start_time) < sampleTime) {
        int sensorValue = analogRead(acs712SensorPin);
        if (sensorValue > sensorMax) {
            sensorMax = sensorValue;
        }
    }

    return sensorMax;
}