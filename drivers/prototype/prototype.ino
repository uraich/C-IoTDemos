/*
 * proto.ino
 * A control and readout program for the prototype board
 * The prototype board consists of a photo resistor whose voltage changes with changing
 * illumination. The voltage is read through the 10 bit ADC on the ESP8266
 * An LED is switched on periodically to change the illumination on the photo resistor 
 * The board and the program were developed for the workshop on IoT during 
 * the African Internet Summit 2019 in Kampala, Uganda
 * Copyright U. Raich
 * The program is released under the GPL public licence
 */
int illuminationLed = 16;
int photoResistor = A0;
int count = 0;
bool ledState = false;  
void setup() {
  Serial.begin(115200);
  Serial.println("Test program for the prototype board");
  pinMode(illuminationLed,OUTPUT);
}

void loop() {

  int lightIntensity;
  delay(1000);  
  count ++;
  lightIntensity = analogRead(photoResistor);
  
//  Serial.print("Count: ");
//  Serial.println(count);
  Serial.print("Light intensity: ");
  Serial.println(lightIntensity);
  if (count > 4) {
    count = 0;
    ledState = !ledState;
    digitalWrite(illuminationLed,ledState);

  } 
  
}
  
