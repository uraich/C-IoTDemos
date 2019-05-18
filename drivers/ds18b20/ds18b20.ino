/*
 * ds18b20Driver
 * The program reads out a Maxim DS18B20 digital temperature sensor and prints the values acquired
 * Uli Raich 16.4.2019
 * The program is part of demonstration code developed for the African Internet Summit 2019 Kampala
 * It is released under GPL
 */
#include <OneWire.h>
#include <DallasTemperature.h>
#ifdef ESP8266
#define ONE_WIRE_BUS 4               // GPIO pin on which the DS18B20 is connected
#endif
#ifdef ESP32
#define ONE_WIRE_BUS 21              // GPIO pin on which the DS18B20 is connected
#endif

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
 
void setup() {
  Serial.begin(115200);
#ifdef ESP8266
  Serial.println("Maxim / Dallas DS18B20 readout program running on the ESP8266");
#endif
#ifdef ESP32
  Serial.println("Maxim / Dallas DS18B20 readout program runing on the ESP32");
#endif
}

void loop() {
  float temp;
  DS18B20.requestTemperatures(); 
  temp=DS18B20.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temp);
  delay(1000);
}
