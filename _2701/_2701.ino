#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  matrix.begin(0x70);
  Serial.begin(9600);

}

int rpm=0;
int sequ[4];
int i;

void loop() {

//  matrix.writeDigitNum(0, (counter / 1000), drawDots);
  matrix.writeDigitNum(1, (rpm / 100) % 10, false);
    matrix.writeDigitNum(3, (rpm / 10) % 10, true);
    matrix.writeDigitNum(4, rpm % 10, false); 

for(int j=0;j<=4;j++)
  {matrix.writeDigitNum(j, random(9), false);
  }
  
if(millis()>3400) {
matrix.writeDigitNum(0, 2, false); 
}
if(millis()>6200) {
matrix.writeDigitNum(3, 0, false); 
}
if(millis()>9800) {
matrix.writeDigitNum(1, 7, false); 
}
if(millis()>10800) {
matrix.writeDigitNum(4, 1, false); 
}
if(millis()>13900) {
matrix.writeDigitNum(4, 2, false); 
}
//colon
matrix.drawColon(false); 
    
//  matrix.print(i);
  matrix.writeDisplay();
  Serial.println(rpm);
  rpm=rpm+1;
  delay(10);
  
  // print with print/println
//  for (uint16_t counter = 0; counter < 9999; counter++) {
  //  matrix.println(counter);
    //matrix.writeDisplay();
   // delay(10);
//  }

}
