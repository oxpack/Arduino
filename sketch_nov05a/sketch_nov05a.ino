class Button
{
  unsigned long previousMillis;
  boolean state;
  boolean pin_status;
  int pin;
  int bounce;     // milliseconds of on-time
  int repeat; 
  
public:
Button(int sw_pin, int bounce_time, int repeat_interval)
{
  pin = sw_pin;
  pinMode(pin,INPUT_PULLUP);
  bounce = bounce_time;
  repeat = repeat_interval;
  state = false;
}
  
int Update()
{
  pin_status = 1 - digitalRead(pin);
  
  if(pin_status == true && state == false)
 {
  previousMillis = millis();
  state = true;
  repeat = 0;
  return 1;
  }
  
 if(pin_status == true && state == true && millis()-previousMillis > bounce)
 {
   previousMillis = millis();
   repeat += 1;
   Serial.print(repeat);
   Serial.print("   ");
   return 1 + repeat/10;
 }
 
if(pin_status == false && millis()-previousMillis > bounce)
 {repeat = 0;
  state = false;
}
 
 return 0;
 
 }
};//end class Button Definition
  


Button up(2,500,1000);
float spd;
float old_spd;

void setup() {
Serial.begin(9600);  
}

void loop() {
   spd = spd + up.Update()/10.0;
   if (spd != old_spd)  { Serial.println(spd);}
   old_spd = spd;
}
