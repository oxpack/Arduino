//routine to generate data for python to read in
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}


void loop() {
  /*Data format is below
  C TTT RH xxxx
  where C is channel either 1 or 2
  TTT is temperature times 10 in celcius
  RH is 00 to 99 for percent rh
  xxxx is ppm of CO2
  */
  for(int i=1;i<3;i++){
    //print channel
    Serial.print(i);
    Serial.print(" ");
    //print temperature
    Serial.print(340+random(0,50));
    Serial.print(" ");
    //print rh
    Serial.print(40+random(0,5));
    Serial.print(" ");
    //print CO2
    Serial.println(400+random(0,66));
  }
  delay(1000);        // delay in between reads for stability
}
