#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <ESPDash.h>

#include <wifi_credentials.h>
#include <acs712.h>
#include <relay.h>

// WIFI
const char* hostname = "Shopvac";

AsyncWebServer server(80);

/* Attach ESP-DASH to AsyncWebServer */
ESPDash dashboard(&server); 

Card cardButton(&dashboard, BUTTON_CARD, "Shopvac");
bool cardButtonValue = false;
Card cardVoltage(&dashboard, GENERIC_CARD, "Voltage", "V");

// PIN DEFINITION
const int CURRENT_SENSOR_PIN = A4;
const int MANUAL_BUTTON_PIN = 13;

// RELAY
const int RELAY_PIN = 26;

// CURRENT SENSOR
const int SAMPLE_TIME_MS = 1000;
const float VOLTAGE_TO_START = 2.20;
int currentSensorValue = 0;
float voltage = 0;

// BUTTON
const int BUTTON_CLOSE_IN = HIGH;
int currentButtonState = !BUTTON_CLOSE_IN;
int nextButtonState = !BUTTON_CLOSE_IN;

// Inits the wifi connection.
void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname);
  const char* ssid = getWifiSsid();
  const char* password = getWifiPassword();
  Serial.printf("Connecting to %s with password %s", ssid, password);
  WiFi.begin(ssid, password);

   // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

/**
 * Inits the server.
 * 
 */
void initServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am the Shopvac.");
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

/**
 * Inits the sensors, button & relay.
 * 
 */
void initSensors() {
  pinMode(MANUAL_BUTTON_PIN, INPUT_PULLDOWN);
  
  initRelay(RELAY_PIN);

  currentButtonState = digitalRead(MANUAL_BUTTON_PIN);
  

  cardButton.attachCallback([&](bool value){
    cardButtonValue = value;
    cardButton.update(value);
    dashboard.sendUpdates();

    if (value) {
      turnOnShopVac(RELAY_PIN);
    } else {
      turnOffShopVac(RELAY_PIN, 1);
    }
  });
}

/**
 * Setup function.
 */
void setup() {
  Serial.begin(115200);

  initWifi();
  initServer();
  initSensors();
}

/**
 * Loop function.
 * 
 */
void loop() {
  if (!cardButtonValue) {
    nextButtonState = digitalRead(MANUAL_BUTTON_PIN);
    // Button has changed
    if (currentButtonState != nextButtonState) {
      if (nextButtonState == BUTTON_CLOSE_IN) {
        turnOnShopVac(RELAY_PIN);
      } else {
        turnOffShopVac(RELAY_PIN, 1);
      }
      currentButtonState = nextButtonState;
    } else if (currentButtonState != BUTTON_CLOSE_IN) {
      // Measuaring the tool
      currentSensorValue = getMaxValue(CURRENT_SENSOR_PIN, SAMPLE_TIME_MS);
      Serial.printf("sensor value %d\n", currentSensorValue);
      voltage = (float) currentSensorValue / 4095 * 3.3;
      Serial.printf("Voltage %.2fv\n", voltage);
      cardVoltage.update(voltage);
      dashboard.sendUpdates();

      // If voltage is above 3.2, the loop should be discarded.
      if (voltage <= 3.2) {
        if (voltage >= VOLTAGE_TO_START && !isRelayClosed(RELAY_PIN)) {
          turnOnShopVac(RELAY_PIN);
        } else if (voltage < VOLTAGE_TO_START && isRelayClosed(RELAY_PIN)) {
          turnOffShopVac(RELAY_PIN, 5);
        }
      }

      delay(500);
    }
  }
}