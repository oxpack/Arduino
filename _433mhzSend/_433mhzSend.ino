/*
* Simple Transmitter Code
* This code simply counts up to 255
* over and over
* (TX out of Arduino is Digital Pin 1)
*/
byte counter;
void setup(){
//4800 baud for the 434 model
Serial.begin(4800);
}
void loop(){
//send out to transmitter
for(byte i=0;i<255;i++)
  {
    Serial.write(i);
  }
}
