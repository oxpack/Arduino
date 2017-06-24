//frequency check as part of 160304-01

#define MICROSTEP 32

float spd = 14.0;

void setup() {
  //setup serial output
  Serial.begin(9600);
}

void loop() {

 for(spd = 13;spd=spd+.1;spd<15)
 {  
    tone(8, abs(spd) * 10 * 200 * MICROSTEP / 60);  
    Serial.print(spd);
    Serial.print("  ");
    Serial.println(abs(spd) * 10 * 200 * MICROSTEP / 60); 
delay(10000);
 }
}



