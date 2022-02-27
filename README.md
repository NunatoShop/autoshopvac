AUTO SHOPVAC
============

This project has the purpose to create a shop vacuum controller that measure if a tool is on and it automatically start the shop vacuum.

## Hardware
* ESP32.
* 1 channel relay 5V 10A.
* Acs712 ± 30a Efecto Hall.
* Button (Switch).
* Logic level 5v - 3.3V.
* 2 male electrical plugs.
* 1 female electrical plug.
* 1 electrical box.
* Wires.

## Instalation
### WiFi credentials

There is a file that isn't included in the project that is `wifi_credentials.cpp` that has to contains

```c++
char* getWifiSsid() {
    return "Your WiFi Name";
}

char* getWifiPassword() {
    return "Your WiFi Password";
}
```
