# C++-IoTDemos
IoT demos written for the Arduino IDE in C++
## Purpose
The demo programs in this repository have been written for a workshop on IoT at the African Internet Summit (AIS) 2019 in Kampala Uganda. The programs have essentially the same functionality as the ones in the MicroPython_IoTDemos repository but here they are written in C++ for the Arduino IDE with the ESP8266 or the ESP32 processor.
## Running of ESP8266 and ESP32
The programs are written in such a way that they run on either the ESP8266 or the ESP32. The Wire library already works for both processor such that the programs for I2C devices work without change. For the other devices, where the GPIO pin must be defined, we check if ESP8266 or ESP32 is defined and we set up the GPIO pin numbers accordingly.
