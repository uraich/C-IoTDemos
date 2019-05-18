// cayenneDHT11
// Reads out the DHT11 temperature and humidity sensor and publishes the
// results on Cayenne
// Copyright Uli Raich
// This program is part of the workshop on IoT at the African Internet Summit
// AIS 2019 Kampala, Uganda
// It is released under GPL

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#ifdef ESP8266
#include <CayenneMQTTESP8266.h>
#endif
#ifdef ESP32
#include <CayenneMQTTESP32.h>
#endif

#include "DHT.h"
#ifdef ESP8266
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#endif

#ifdef ESP32
#define DHTPIN 16     // Digital pin connected to the DHT sensor
#endif
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial

// WiFi network info.
char ssid[] = "WIFI_SSID";
char wifiPassword[] = "WIFI PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE CLIENT_ID";

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  int dht11TempChannel = 7;
  int dht11HumChannel = 8;
  float temp,hum;
  // Write data to Cayenne here. 
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  Cayenne.celsiusWrite(dht11TempChannel, temp);
  Cayenne.virtualWrite(dht11HumChannel, hum, TYPE_RELATIVE_HUMIDITY, UNIT_PERCENT);
  
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
