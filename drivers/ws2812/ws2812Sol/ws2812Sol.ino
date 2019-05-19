// A basic NeoPixel test program, controls a single ws2812b rgb LED
// U. Raich, 19.5.2019
// This program was written as a demo for the AIS conference 2019, Kampala, Uganda

#include <Adafruit_NeoPixel.h>
// pin on which the ws2812 is connected
#ifdef ESP8266
#define LED_PIN    4
#endif
#ifdef ESP32      
#define LED_PIN   21 
#endif

#define LED_COUNT 1

// Declare our NeoPixel strip object:
Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("Testing the WS2812B rgb LED");
  Serial.println("Program written for the workshop on IoT at the");
  Serial.println("African Internet Summit 2019");
  Serial.println("Copyright: U.Raich");
  Serial.println("Released under the Gnu Public License");
  
  led.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  led.show();            // Turn OFF all pixels ASAP
  led.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop() {

  int i,j,k;
  for (i=0;i<10; i++) {
    Serial.println("Switch red LED on");
    led.setPixelColor(0,led.Color(0,64,0));
    led.show();
    delay(1000);
    
    Serial.println("Switch green LED on");    
    led.setPixelColor(0,led.Color(64,0,0));
    led.show();
    delay(1000);
    
    Serial.println("Switch blue LED on");     
    led.setPixelColor(0,led.Color(0,0,64));
    led.show();
    delay(1000);
  }
// switch LED off
  led.setPixelColor(0,led.Color(0,0,0));
  led.show();
  while (true) ;       // stop
}
