#include <WEMOS_Matrix_LED.h>
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

  
}

void loop() {
  uint8_t i;
  for (i=0;i<65;i++) {
    setLevel(i);
    delay(200);
  }
}
