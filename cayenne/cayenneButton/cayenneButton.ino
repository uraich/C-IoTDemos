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
int pbPin=0;
#endif
#ifdef ESP32
#include <CayenneMQTTESP32.h>
int pbPin=17;
#endif

// WiFi network info.
char ssid[] = "WIFI SSID";
char wifiPassword[] = "WIFI PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE CLIENT_ID";

unsigned long lastMillis = 0;

void setup() {
	Serial.begin(115200);
  pinMode(pbPin,INPUT_PULLUP);
	Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
	Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  int pbChannel = 10;
	// Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
	//Cayenne.virtualWrite(0, millis());
	// Some examples of other functions you can use to send data.
  bool state;
  state = digitalRead(pbPin);
  if (state) 
    Serial.println("Switch is released");
  else
    Serial.println("Switch is pressed");
    
	Cayenne.digitalSensorWrite(pbChannel, !state);       // switch is active low
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
