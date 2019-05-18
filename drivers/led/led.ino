/*
 * led.ino
 * This is the Hello World program for embedded systems: the blinking led
 * It works on the built-in LED on GPIO 2
 * Program written for the workshop on embedded system at the
 * African Internet Summit 2019, Kampala, Uganda
 * U. Raich 
 */
int builtinLed = 2;
bool ledState = true;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();
  Serial.println("Blinks the built-in LED on the WeMos D1 mini CPU board");

  pinMode(builtinLed,OUTPUT);
}

void loop() {
  digitalWrite(builtinLed,ledState);
  delay(500);
  ledState =!ledState;
}
