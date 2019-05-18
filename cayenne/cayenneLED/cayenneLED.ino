// cayenneButton
// Reads out a simple push button and publishes the results on Cayenne
// The pushbutton return a value 0 when pressed (connection to gnd
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

int builtinLed = 2;
int ledChannel = 9;

// WiFi network info.
char ssid[] = "WIFI SSID";
char wifiPassword[] = "WIFI PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE_CLIENT_ID";

void setup() {
	Serial.begin(115200);
	pinMode(builtinLed,OUTPUT);
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
	//Cayenne.luxWrite(2, 700);
	//Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  int onOff;
  if (request.channel ==  ledChannel) {
    onOff = getValue.asInt();
    if (onOff)
      Serial.println("Switch LED on");
    else
      Serial.println("Switch LED off");
    digitalWrite(builtinLed,onOff);
  }
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
