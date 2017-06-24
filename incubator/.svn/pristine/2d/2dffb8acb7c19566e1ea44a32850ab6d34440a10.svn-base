//routine to generate data for python to read in
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}


void loop() {
  /*Data format is below
    C TTT RH xxxxx
    where C is channel either 0 or 1
    TTT is temperature times 10 in celcius
    RH is 00 to 99 for percent rh
    xxxxx is ppm of CO2
  */
  char buf[15];
  for (int i = 0; i < 2; i++) {
    int t = 340 + random(0, 50);
    int rh = 40 + random(0, 5);
    int ppm = 1000 + random(0,100);
    sprintf(buf, "%1d %03d %02d %05d\n",i,t,rh,ppm);
    Serial.print(buf);
  }
  delay(2000);        // delay in between reads for stability
}
