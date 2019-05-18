#include <WEMOS_Matrix_LED.h>
#ifdef ESP8266
MLED mled(3,13,14); //set intensity=5 dataPin = 13, clkPin = 14)
#endif
#ifdef ESP32
MLED mled(3,23,18); //set intensity=5
#endif

void setup() {
  // put your setup code here, to run once:

  
}

void loop() {

  for(int y=0;y<8;y++)
  {
    for(int x=0;x<8;x++)
    {
        mled.dot(x,y); // draw dot
        mled.display();
        delay(200);
        mled.dot(x,y,0);//clear dot
        mled.display();
        delay(200);        
    }  
  }

}
