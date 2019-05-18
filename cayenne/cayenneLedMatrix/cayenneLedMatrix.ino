// cayennLedMatrix
// subscribes to a slider on Cayenne defining the number of LEDs to light
// The slider must provide values 0..64
// The ledMatrix switches the number of Leds on which are given by the slider
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
#include <WEMOS_Matrix_LED.h>

// WiFi network info.
char ssid[] = "WIFI SSID";
char wifiPassword[] = "WIFI PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE_CLIENT_ID";

#ifdef ESP8266
MLED mled(3,13,14); //set intensity=5 dataPin = 13, clkPin = 14)
#endif
#ifdef ESP32
MLED mled(1,23,18); //set intensity=1
#endif

void setLevel(uint8_t level) {
  uint8_t i,j,x,y;
  Serial.print("level: ");
  Serial.println(level);
  
  y = level / 8;
  x = level % 8;
  
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.println(y);
  mled.clear();
  for (i=0;i<y;i++)
    for (j=0; j<8; j++)
      mled.dot(j,i);
  for (i=0;i<x;i++)
    mled.dot(i,y);
  mled.display();  
}

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
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
  int ledMatrixChannel = 11;
  int level;
  if (request.channel ==  ledMatrixChannel) {
    level = getValue.asInt();
    setLevel(level);
  }
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
