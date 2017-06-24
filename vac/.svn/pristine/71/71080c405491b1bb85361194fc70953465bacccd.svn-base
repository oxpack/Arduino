#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"


/*code for testing 7 segment backpack
first digit is 0
second digit is 1
colon is 2
third digit is 3
fourth digit is 4

top segment = 2^0 
upper right seg = 2^1
lower right seg = 2^2
bottom segment = 2^3
lower left segment = 2^4
upper left segment = 2^5
middle segment = 2 ^6
decimal point = 2^7
*/

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
  // put your setup code here, to run once:
  pinMode(2, INPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  //E
  matrix.writeDigitRaw(0, 121);
  //S
  matrix.writeDigitRaw(1, 109);
  //T
  matrix.writeDigitRaw(3, 49);
  //P   
  matrix.writeDigitRaw(4, 115);
  //Serial.println(digitalRead(2));

  matrix.writeDisplay();

  delay(250);
}
