//arduino nano
//ATmega328 on COM7
//first part pulses leds in a wave using pins 3,5,6,9
//second part pulses discreetly 

#define PI = 3.1415;
//indicators
int led[4] = {3,5,6,9};
//optical outputs to BLACK
int led2[4] = {8,10,11,12};

int i=0,j;
byte incomingByte;

// the setup routine runs once when you press reset:
void setup()  { 
  int i=0;
  //set digital pins to outputs
  for (i=0;i<=3;i++){
  pinMode(led[i], OUTPUT);
  pinMode(led2[i],OUTPUT);
  }
    Serial.begin(9600);  
    
  //flash all leds 3x
  for(i=0;i<=2;i++)
  {
  set_lights(B1111); 
  delay(250);
  set_lights(B0000);
  delay(500);
  }
} 

// the loop routine runs over and over again forever:
unsigned long currentMillis=0;

void loop()  { 
  while(Serial.available()) 
{
  incomingByte = Serial.read();
  set_lights(incomingByte);  
  currentMillis = millis();
  delay(5);
}

//if its been more than ten seconds then turn off and pulse leds
if ((millis()-currentMillis) > 10000)
  {
  pulse();
  set_zero();
  }
  
//decay(incomingByte);
 
}

 void decay(byte status)
 {
   int i,mag;
   if(millis()-currentMillis<9000)
   {
     return;
   }
     else
     {mag = 255-((millis()-currentMillis)-9000)*255/1000;
       for(i=0;i<=3;i++){
         analogWrite(led[i], mag * (status & 1) );
         status = status >> 1;
       }
     }
   }
 
void pulse()
{
  float angle;
  int i,mag;
  angle = millis()/500.0;
  for (i=0;i<=3;i++){
    mag = 255*sin(angle+i*PI/2.0);
    if(mag<0) mag = 0;
  analogWrite(led[i], mag); 
  }
}  


void set_zero()
{
int i;
for(i=0;i<=3;i++){
    digitalWrite(led2[i],0);
    }
}

void set_lights(byte status)
{
int i;
for(i=0;i<=3;i++){
    digitalWrite(led[i],status & 1);
    digitalWrite(led2[i],status & 1);
    status = status >> 1;
    }
} 

