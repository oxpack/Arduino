/*this program is to perform a checkout on the temperature and
  humidity sensors
  Can take up to 15 minutes to stablilize*/

#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial mySerial0(8, 9);
SoftwareSerial mySerial1(10, 11); // RX, TX

char buf[15];
unsigned long co2 = 0; // holds the actual value
float cal[2]; //calibration constants

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  /* Serial.println("Data output is C ttt rh co2");
    Serial.println("C is 0 or 1 for the channel");
    Serial.println("ttt is the temperature in Celcius multiplied by 10  147 = 14.7");
    Serial.println("rh is the relative humidity 45 = 45%");
    Serial.println("co2 is the partial pressure of CO2 in psi 061 = 0.61 psi");
  */


  //NEED SOME WAY TO ENTER CALIBRATION DATA FOR EACH SENSOR
  mySerial0.begin(9600); //Start Serial connection with Sensor
  mySerial0.print("M 6\r\n");

  mySerial1.begin(9600); //Start Serial connection with Sensor
  mySerial1.print("M 6\r\n");
  
  for (int i = 0; i < 2; i++)
  {
    EEPROM.get(i * sizeof(float), cal[i]);
    Serial.print("Calibration constant ");
    Serial.print(i);
    Serial.print(":");
    Serial.println(cal[i]);

    if (cal[i] < .25 || cal[i] > 1.) {
      Serial.print("CAL WRONG FOR CHANNEL ");
      Serial.print(i);
      Serial.println(" DEFAULTING TO 0.5");
      cal[i]=.5;
    }


  }

}

//ch   pin    sens
//0    A0      Temp
//0    A1      rh
//1    A2      Temp
//1    A3      rh
//0    A4      co2
//1    A5      co2


void loop() {

  //look from input U or G from terminal
  if (Serial.available() > 0)
  {
    zero();
  }


  for (int i = 0; i < 2; i++)
  {

    //co2_read(i);
    // read the input on analog pin a0 or a2 for temp
    int sensorValue = analogRead(2 * i);
    int t = ((float)sensorValue / 1023.0 * 130.0 - 30.0) * 10.0;
    if (t < 0) {
      t = 0.0;
    }

    // read the input on analog pin a1 or a3 for rh
    sensorValue = analogRead(2 * i + 1);
    int rh = (float) sensorValue / 1023.0 * 100.0;
    if (rh < 0) {
      rh = 0;
    }

    //read the input from analog pin a4 and a5 for analog co2
    sensorValue = analogRead(4 + i);
    co2 = (float) sensorValue * cal[i];
    if (co2 < 0) {
      co2 = 0;
    }

    sprintf(buf, "%1d %03d %02d %03d\n", i, t, rh, co2);
    Serial.print(buf);
    delay(1000);
  }
}


void zero() {
  byte byteread;
  int i;

  while (Serial.available() > 0)
  {
    byteread = Serial.read();
    if (byteread == 'U')
    {
      Serial.println("Beginning calibration process for both gauges");
      Serial.println("Put both gauges in a 100% nitrogen environment for five minutes to zero them");
      for (i = 300; i > 0; i--)
      {
        Serial.print(i);
        if (i % 15 == 14) {
          Serial.println();
        }
        delay(1000);
      }
     // mySerial1.write("U\r\n");
      //mySerial0.write("U\r\n");
      Serial.println("Put both gauges in a 5% co2 environment for five minutes");
      for ( i = 300; i > 0; i--)
      {
        Serial.print(i);
        Serial.print(" ");
        Serial.print(analogRead(4));

        Serial.print(" ");
        Serial.println(analogRead(5));
        delay(1000);
      }

      cal[0] = 0.0;
      cal[1] = 0.0;
      //get an average
      for (i = 0; i<10; i++)
      {
        cal[0] = cal[0] + (float) analogRead(4);
        cal[1] = cal[1] + (float) analogRead(5);
        delay(50);
      }

      cal[0] = 10.0 * 61.0 / cal[0];
      EEPROM.put(0, cal[0]);
      Serial.println(cal[0]);

      cal[1] = 10.0 * 61.0 / cal[1];
      EEPROM.put(sizeof(float), cal[1]);
      Serial.println(cal[1]);

    }

  }
}


//This code was abandoned in place


void co2_read(int i)
{
  String val = ""; //holds the string of the value
  unsigned long time;
  uint8_t buffer[25];
  int    ind = 0; //Reset the buffer index to overwrite the previous packet

  double multiplier = 10; //each range of sensor has a different value.
  time = millis();

  if (i == 0)
  {
    mySerial0.listen();
    while (buffer[ind - 1] != 0x0A && millis() - time < 3000 && ind < 24)
    {
      if (mySerial0.available())
      {
        buffer[ind] = mySerial0.read();

        //        Serial.print(char(buffer[ind]));
        ind++;
      }
    }
  }
  ind = 0;
  if (i == 1)
  {
    mySerial1.listen();

    while (buffer[ind - 1] != 0x0A && (millis() - time) < 3000 && ind < 24)
    {
      if (mySerial1.available())
      {
        buffer[ind] = mySerial1.read();
        //      Serial.print(char(buffer[ind]));
        ind++;
      }
    }
  }

  //Cycle through the buffer and send out each byte including the final linefeed
  //each packet in the stream looks like "Z 00400 z 00360"
  //'Z' lets us know its a co2 reading. the first number is the filtered value
  // and the number after the 'z' is the raw value.
  // We are really only interested in the filtered value

  for (int i = 0; i < ind + 1; i++)
  {
    if (buffer[i] == 'z') //once we hit the 'z' we can stop
      break;

    if ((buffer[i] != 0x5A) && (buffer[i] != 0x20)) //ignore 'Z' and white space
    {
      val += buffer[i] - 48; //because we break at 'z' the only bytes getting added are the numbers
      // we subtract 48 to get to the actual numerical value
      // example the character '9' has an ASCII value of 57. [57-48=9]
    }
  }

  co2 = (multiplier * val.toInt()); //now we multiply the value by a factor specific ot the sensor. see the Cozir software guide
  // Serial.println(co2);
}



