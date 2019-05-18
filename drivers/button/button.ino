/* button.ino
 *  Reads out the state of a push button and prints the result 
 *  This program was developed for the workshop on IoT during the
 *  African Interner Summit 2019, Kampala, Uganda
 *  Copyright U. Raich
 *  This program is released under GPL
 */

#ifdef ESP8266
int pbPin = 0;
#endif
#ifdef ESP32
int pbPin = 17;
#endif

void setup() {
  Serial.begin(115200);
#ifdef ESP8266  
  Serial.println("Push button test program running on the ESP8266");
#endif 
#ifdef ESP32  
  Serial.println("Push button test program running on the ESP32");
#endif
  pinMode(pbPin,INPUT_PULLUP);
}

void loop() {
  int state;
  state = digitalRead(pbPin);
  if (state)
    Serial.println("Switch is released");
  else
    Serial.println("Switch is pressed");
  delay(1000);

}
