void setup() {
  Serial.begin(115200);
  Serial.print("Find CPU type");
#ifdef ESP8266
  Serial.print("ESP8266 found");
#endif
#ifdef ESP32
  Serial.print("ESP32 found");
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
