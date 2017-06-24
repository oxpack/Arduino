  /*
Original software was from CO2 sensor manufacturer
 Cozir Sample code
 Written by: Jason Berger ( for Co2meter.com)
 
 This sketch connects will connect to a Cozir gss or SprintIR sensor
 and report readings back to the host computer over usb. The value is
 stored in a global variable 'co2' and can be used for any number of applications.
 
 pin connections:
 
 Arduino________Cozir Sensor
 GND ------------------ 1 (gnd)
 3.3v------------------- 3 (Vcc)
 10 -------------------- 5 (Rx)
 11 -------------------- 7 (Tx)
 
 Paul Koenig added some commanding and checkout for two simultaneous serial ports
 */
#include <SoftwareSerial.h>
SoftwareSerial mySerial0(8,9);
SoftwareSerial mySerial1(10, 11); // RX, TX

String val= ""; //holds the string of the value
double co2 =0; // holds the actual value
double multiplier = 10; //each range of sensor has a different value.
unsigned long time;

// up to 2% =1
// up to 65% = 10
//up to 100% = 100;
uint8_t buffer[25];
uint8_t ind =0; 

void setup()
{
  Serial.begin(9600); //Start Serial connection with host
  Serial.println("Co2Meter.com Cozir Sample"); 

  mySerial0.begin(9600); //Start Serial connection with Sensor
  mySerial0.print("M 6\r\n");

  mySerial1.begin(9600); //Start Serial connection with Sensor
  mySerial1.print("M 6\r\n");
} 

void loop()
{
  if(Serial.available()>0) 
  {
    zero();
  }
  /*Cozir sensors ship from the factory in streaming mode
   So we read incoming bytes into a buffer until we get '0x0A'
   which is the ASCII value for new-line
   */
  Serial.println("Reading ch0");
  time= millis();
  ind=0;
  mySerial0.listen();
  while(buffer[ind-1] != 0x0A && millis()-time<5000 && ind<24)
  {
    if(mySerial0.available())
    {
      buffer[ind] = mySerial0.read();

      Serial.print(char(buffer[ind]));
      ind++;
    }
  }  
 

  delay(1000);
  Serial.println("Reading ch1");
  time = millis();
  ind=0;
  mySerial1.listen();
  
  while(buffer[ind-1] != 0x0A && (millis()-time)<5000 && ind<24)
  {
    if(mySerial1.available())
    {
      buffer[ind] = mySerial1.read();
      Serial.print(char(buffer[ind]));
      ind++;
    }
  }  
  
  delay(1000);

} 

void zero(){
  byte byteread;
  while(Serial.available()>0)
  {
    byteread = Serial.read();
    if(byteread=='U')
    { Serial.println();
      Serial.println("Gauges must be in nitrogen already for 5 minutes");
      mySerial1.write("U\r\n");
      mySerial0.write("U\r\n");
    }
    if(byteread=='G')
    { Serial.println();
      Serial.println("Gauges must be in fresh air");
      mySerial1.write("G\r\n");
      mySerial0.write("G\r\n");
    }
  }
}
