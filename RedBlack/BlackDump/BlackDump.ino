/*
Arduino nano ATmega328 on COM7
This program just reads the 4 analog inputs on the black side
to get readings on what the sensors see when on,off, and also in a room
*/

// the setup routine runs once when you press reset:
void setup()  {
  //setup com port to receive data
  Serial.begin(115200);
}

//main loop
void loop()  {
  int i;
  //cycle through first four analog inputs
  for (i = 0; i <= 3; i++) {
    Serial.print(analogRead(i));
    Serial.print(" ");
  }
  // print new line
  Serial.println();
  // 1/2 second delay
  delay( 500);
}


