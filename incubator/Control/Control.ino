/*this program is to perform a checkout on the temperature and
  humidity sensors
  Can take up to 15 minutes to stablilize*/

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <PID_v1.h>
#define TPin 13
#define CPin 2

//BEGIN OF RELAY CLASS
class Relay
{
    // Class Member Variables
    // These are initialized at startup
    int OutPin;      // the number of the LED pin
    long OnTime;     // milliseconds of on-time
    long TotalTime;    // milliseconds of period

    // These maintain the current state
    int PinState;                 // ledState used to set the LED
    unsigned long previousMillis;   // will store last time LED was updated

    // Constructor - creates a Flasher
    // and initializes the member variables and state
  public:
    Relay(int pin, long P)
    {
      OutPin = pin;
      pinMode(OutPin, OUTPUT);

      OnTime = 0;
      TotalTime = P;
      PinState = LOW;
      previousMillis = 0;
    }

    void Update(long newOnTime)
    {
      // check to see if it's time to change the state of the LED
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis <= OnTime)
      {
        digitalWrite(OutPin, HIGH);  // Update the actual LED
      }
      else {
        digitalWrite(OutPin, LOW);
      }
      if (currentMillis - previousMillis >= TotalTime)
      {
        previousMillis = currentMillis;   // Remember the time
        OnTime = newOnTime;
      }
    }//end of update()
};

//END OF RELAY CLASS


struct CustomVar {
  double cal;
  double TSet;
  double CSet;
};

CustomVar constants;


//Define Variables we'll be connecting to
double TIn, TOut;
double CIn, COut;


PID TPID(&TIn, &TOut, &constants.TSet, 700, .5, 1, DIRECT);
PID CPID(&CIn, &COut, &constants.CSet, 5000, 1, .01, DIRECT);

//setup serial to talk to the CO2 sensor
SoftwareSerial mySerial0(8, 9);

int WindowSize = 5000; //five seconds

Relay RelayTemp(TPin, WindowSize);
Relay RelayCO2(CPin, WindowSize);

void setup() {
  byte flag = 0;
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  /* Serial.println("Data output is C ttt rh co2");
    Serial.println("C is 0 or 1 for the channel");
    Serial.println("ttt is the temperature in Celcius multiplied by 10  147 = 14.7");
    Serial.println("rh is the relative humidity 45 = 45%");
    Serial.println("co2 is the partial pressure of CO2 in psi 061 = 0.61 psi");
  */

  //tell the PID to range between 0 and the full window size
  TPID.SetOutputLimits(0, WindowSize);
  CPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  TPID.SetMode(AUTOMATIC);
  CPID.SetMode(AUTOMATIC);

  //NEED SOME WAY TO ENTER CALIBRATION DATA FOR EACH SENSOR
  mySerial0.begin(9600); //Start Serial connection with Sensor
  mySerial0.print("M 6\r\n");
  constants.CSet = 0.72;
  EEPROM.get(0, constants);
  Serial.print("##CO2 Calibration constant: ");
  Serial.println(constants.cal);

  if (constants.cal < .25 || constants.cal > 1. || isnan(constants.cal)) {
    Serial.println("##CO2 CAL WRONG DEFAULTING TO 0.5");
    constants.cal = .5;
    flag = 1;
  }

  Serial.print("##T Setpoint: ");
  Serial.println(constants.TSet);

  if (constants.TSet < 25.0 || constants.TSet > 45.0) {
    Serial.println("##TEMPERATURE SETPOINT WRONG, DEFAULTING TO 37.0");
    constants.TSet = 37.0;
    flag = 1;
  }

  Serial.print("##CO2 Setpoint: ");
  Serial.println(constants.CSet);

  if (constants.CSet < 0.0 || constants.CSet > 1.4 ) {
    Serial.println("##CO2 SETPOINT WRONG, DEFAULTING TO .71");
    constants.CSet = 0.71;
    flag = 1;
  }
  if (flag > 0) {
    Serial.println("##BURNING NEW CONSTANTS");
    EEPROM.put(0, constants);
  }
}//end of setup()

//ch   pin    sens
//0    A0      Temp
//0    A1      rh
//0    A4      co2

void loop() {
  char buf[15];

  //look from input U or G from terminal
  if (Serial.available() > 0)
  {
    zero();
  }

  // read the input on analog pin a0 for temp
  int sensorValue = analogRead(0);
  TIn = ((double) sensorValue / 1023.0 * 130.0 - 30.0);
  if (TIn < 20.0) {
    TIn = 20.0;
  }


  // read the input on analog pin a1 for rh
  sensorValue = analogRead(1);
  int rh = (float) sensorValue / 1023.0 * 100.0;
  if (rh < 0) {
    rh = 0;
  }

  //read the input from analog pin a4 for analog co2
  sensorValue = analogRead(4);
  CIn = (double) sensorValue * constants.cal / 100.0;
  if (CIn < 0) {
    CIn = 0;
  }


  //dump to serial output
  if (millis() % 950 == 0) {
    sprintf(buf, "%1d %03d %02d %03d\n", 0, (int) (TIn * 10.0), rh, (int) (100.0 * CIn));
    Serial.print(buf);
    Serial.print("##TOut");
    Serial.println(TOut);
    Serial.print("##COut");
    Serial.println(COut);
  }

  TPID.Compute();
  CPID.Compute();

  RelayTemp.Update((long) TOut);
  RelayCO2.Update((long) COut);

}//end of loop


void zero() {
  byte byteread;
  int i;
  float cal, setpoint;

  while (Serial.available() > 0)
  {
    byteread = Serial.read();
    if (byteread == 'U')
    {
      TPID.SetMode(MANUAL);
      CPID.SetMode(MANUAL);

      Serial.println("##Put gauge in a 100% nitrogen environment for five minutes to zero them");
      delay(5000);
      for (i = 300; i > 0; i--)
      {
              
          Serial.print("##Equilibrating in nitrogen ");
          Serial.println(i);
          delay(1000);
      }
      //send signal to zero firmware on the CO2 sensor
      mySerial0.write("U\r\n");
      
      Serial.println("##Put gauge in a 5% co2 environment for five minutes");
      delay(5000);
      for ( i = 300; i > 0; i--)
      {
          Serial.print("##Equilibrating in 5% CO2 at Boulder altitude ");
          Serial.println(i);
          delay(1000);
      }

      cal = 0.0;
      //get an average
      for (i = 0; i < 10; i++)
      {
        cal = cal + (float) analogRead(4);
        delay(50);
      }

      cal = 10.0 * 61.0 / cal;
      constants.cal = cal;
      EEPROM.put(0, constants);
      Serial.print("## Calibration constant: ");
      Serial.println(cal);

      //turn pid back on
      TPID.SetMode(AUTOMATIC);
      CPID.SetMode(AUTOMATIC);
    }

    if (byteread == 'T')
    {
      setpoint = Serial.parseFloat();
      if (setpoint < 25.0 || setpoint > 45.0)
      { Serial.print("##Invalid setpoint 25<Tset<45: ");
        return;
      }
      else
      { constants.TSet = setpoint;
      }
      Serial.print("##Setting temperature to :");
      Serial.print(constants.TSet);
      Serial.println(" Celcius");
      EEPROM.put(0, constants);
    }


    if (byteread == 'C')
    {
      setpoint = Serial.parseFloat();
      if (setpoint < 0.0 || setpoint > 1.41)
      { Serial.print("##Invalid setpoint 0.0<Tset<1.41: ");
        return;
      }
      else
      { constants.CSet = setpoint;
      }
      Serial.print("##Setting CO2 partial pressure to:");
      Serial.print(constants.CSet);
      Serial.println(" psia");
      EEPROM.put(0, constants);
    }

    if (byteread == 'R')
      //reset pid loops to zeros
    {
      TPID.SetMode(MANUAL);
      CPID.SetMode(MANUAL);
      Serial.println("##Resetting PID loops");
      TPID.SetMode(AUTOMATIC);
      CPID.SetMode(AUTOMATIC);
    }
    if (byteread == 'P')
      //print constants
    {
      Serial.println(constants.cal);
      Serial.println(constants.TSet);
      Serial.println(constants.CSet);
    }

  }
}//end of zero()





