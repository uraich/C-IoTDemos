// cayenneBMP180
// Reads out the BMP180 temperature and barometric pressure sensor and publishes the
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

#include <Wire.h>
#include <Adafruit_BMP085.h>

// WiFi network info.
char ssid[] = "WIFI_SSID";
char wifiPassword[] = "WIFI password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE_CLIENT_ID";

unsigned long lastMillis = 0;
Adafruit_BMP085 bmp;

void setup() {
	Serial.begin(115200);
        if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP180 sensor, check wiring!");
	  while (1) {}
	}
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
	// Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
	//Cayenne.virtualWrite(0, millis());
	// Some examples of other functions you can use to send data.
  float temp,pressure;
  int bmp180TempChannel = 12;
  int bmp180PressChannel = 13;
  temp=bmp.readTemperature();
  pressure = bmp.readSealevelPressure()/100.0;
  
  Cayenne.celsiusWrite(bmp180TempChannel, temp);
  Cayenne.hectoPascalWrite(bmp180PressChannel,pressure)
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
	CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
	//Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
