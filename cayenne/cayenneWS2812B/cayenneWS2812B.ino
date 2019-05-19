// cayennwWS2812
// subscribes to a 3 slider on Cayenne defining each color component of
// the rgb LED
// The sliders must provide values 0..255
// Copyright Uli Raich
// This program is part of the workshop on IoT at the African Internet Summit
// AIS 2019 Kampala, Uganda
// It is released under GPL

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial

#include <Adafruit_NeoPixel.h>
// pin on which the ws2812 is connected
#ifdef ESP8266
#include <CayenneMQTTESP8266.h>
#define LED_PIN    4
#endif
#ifdef ESP32
#include <CayenneMQTTESP32.h>   
#define LED_PIN   21 
#endif

#define LED_COUNT 1

// Declare our NeoPixel strip object:
Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// WiFi network info.
char ssid[] = "WIFI SSID";
char wifiPassword[] = "WIFI PASSWORD";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "CAYENNE USERNAME";
char password[] = "CAYENNE PASSWORD";
char clientID[] = "CAYENNE CLIENT_ID";

typedef struct LedColor{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} ;

LedColor ledColor={0,0,0};

void setColor(LedColor color) {
  Serial.print("In setColor: r,g,b: ");
  Serial.print(color.red);
  Serial.print(" ");
  Serial.print(color.green);
  Serial.print(" ");
  Serial.println(color.blue);
  led.show();
  led.setPixelColor(0,led.Color(color.green,color.red,color.blue));
  led.show();
}

void setup() {
  Serial.begin(115200);
  led.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  led.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  // switch LED off
  setColor(ledColor);
  
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
  int redChannel = 3, greenChannel = 2, blueChannel = 4;
  
  int level;
  if (request.channel ==  redChannel) {
     ledColor.red = getValue.asInt();
     Serial.print("Setting red component to ");
     Serial.println(ledColor.red);
  }
  else if (request.channel ==  greenChannel) {
     ledColor.green = getValue.asInt();
     Serial.print("Setting green component to ");
     Serial.println(ledColor.green); 
  }
  else if (request.channel ==  blueChannel) {
     ledColor.blue = getValue.asInt();
     Serial.print("Setting blue component to ");
     Serial.println(ledColor.blue);      
  }
  setColor(ledColor);
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
