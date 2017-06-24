//arduino nano
//ATmega328 on COM7
//first part pulses leds in a wave using pins 3,5,6,9
//second part pulses discreetly 

#define PI = 3.1415;
//indicators
int led[4] = {3,5,6,9};
//optical inputs to BLACK
int inputs[4] = {0,1,2,3};

int i=0,j;
byte outByte;

// the setup routine runs once when you press reset:
void setup()  { 
  int i=0;
  //set digital pins to outputs
  for (i=0;i<=3;i++){
  pinMode(led[i], OUTPUT);
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
  //reset to 0
  outByte = 0;
  //read signals from RED
  for (i=0;i<=3;i++){
    //threshold needs to be determined by voltage divider
    outByte = outByte + (analogRead(i)>500)*2^i;
  }
  
  //set the indicator lights
  set_lights(outByte);  
  
  //send out on serial the byte read once every ten second
   if((millis()-currentMillis) > 10000)
   {
      Serial.write(outByte);
      j = j + (outByte = 0);
      //reset j to 0 if outByte >0;
      j = j * (outByte !=0);
      currentMillis = millis();
   }

if ( j>5)
  {
    pulse();
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

void set_lights(byte status)
{
int i;
for(i=0;i<=3;i++){
    digitalWrite(led[i],status & 1);
    status = status >> 1;
    }
} 

