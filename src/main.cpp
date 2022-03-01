#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include <wifi_credentials.h>
#include <acs712.h>
#include <button.h>
#include <relay.h>

// WIFI
const char* hostname = "Shopvac";

// SERVER
AsyncWebServer server(80);

// Inits the wifi connection.
void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname);

  const char* ssid = GetWifiSsid();
  const char* password = GetWifiPassword();
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
 * @brief Inits the server.
 * 
 */
void initServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am the Shopvac.");
  });

  server.on("/ping", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send( 200, "text/plain", "pong");
  });

   server.on("/sensor", HTTP_GET, [](AsyncWebServerRequest *request) {
     int value = GetValue();
     float voltage = GetVoltage();
    char json[40];
    sprintf(json, "{\"value\":%d,\"voltage\":%.2f}", value, voltage);
    request->send( 200, "application/json", json);
  });

  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

/**
 * @brief Inits the sensors.
 * 
 */
void initSensors() {
  InitButton();
  InitRelay();
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
  if (IsButtonActive()) {
    DoButtonAction();
  } else {
    CheckConnectedTool();
  }
}