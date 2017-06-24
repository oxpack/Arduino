/*
  Simple Receiver Code
  (TX out of Arduino is Digital Pin 1)
  (RX into Arduino is Digital Pin 0)
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

byte incomingByte;
void setup() {
  //4800 baud for the 434 model
  Serial.begin(4800);
}
int counter;

void loop() {
  // read in values, debug to computer
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    if (incomingByte == (byte)65) {
      counter++;
      Serial.println(counter);
    }
  }
}
