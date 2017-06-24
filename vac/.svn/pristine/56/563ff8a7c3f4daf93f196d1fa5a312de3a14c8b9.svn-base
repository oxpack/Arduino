#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#define PROX 5
#define DIR 7
#define MICROSTEP 32
#define ESTOP 2

Adafruit_7segment matrix = Adafruit_7segment();

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
      pinMode(pin, INPUT);
      bounce = bounce_time;
      repeat = repeat_interval;
      state = false;
    }

    int Update()
    {
      pin_status = digitalRead(pin);

      if (pin_status == true && state == false)
      {
        previousMillis = millis();
        state = true;
        repeat = 0;
        return 1;
      }

      if (pin_status == true && state == true && millis() - previousMillis >
          bounce)
      {
        previousMillis = millis();
        repeat += 1;
        if(repeat>10) {repeat=10;}
        //Serial.print(repeat);
        //Serial.print("   ");
        return repeat;
      }

      if (pin_status == false && millis() - previousMillis > bounce)
      { repeat = 0;
        state = false;
      }

      return 0;

    }
};//end class Button Definition



Button up(3, 500, 1000);
Button down(4, 500, 1000);
Button prox(PROX, 500, 5000);

float spd = 0.0, old_spd = 0.0;
int period = 0;
unsigned long last_prox = 0;

void setup() {
  //setup the display
  matrix.begin(0x70);

  //setup serial output
  Serial.begin(9600);
  
  //pinMode(ESTOP, INPUT);
  
  //setup the direction pin as output
  pinMode(DIR, OUTPUT);

  //show the microstep setting briefly at startup
  matrix.print(MICROSTEP);
  matrix.writeDisplay();
  delay(1000);

  //reset display to 0.0
  matrix.print(0);
  matrix.writeDisplay();
}

void loop() {
  //check the up button and check the down button
  spd = spd + up.Update() / 10.0 - down.Update() / 10.0;;

  //make sure speed isn't less than -1.0
  if (spd < -1) {
    spd = -1.0;
  }

  //make sure speed isn't greater than 15.0
  if (spd > 15.0) {
    spd = 15.0;
  }

  //check if speed positive change direction if negative
  if (spd > 0)
  {
    digitalWrite(DIR, 1);
  } else
  {
    digitalWrite(DIR, 0);
  }

  //if speed not equal the old speed then change frequency
  if (spd != old_spd)
  {
    //F = x rpm * 10 (gear) *200 (steps/rev)*(microsteps/step) * (min/60 sec)
    if (abs(spd) >.05)
    {
      tone(8, abs(spd) * 10 * 200 * MICROSTEP / 60);
    }
    else
    {
      noTone(8);
    } 
    matrix.print(spd);
    old_spd = spd;
  }

  /*safety
  if (digitalRead(2) == 0)
  {
    spd = 0;
    //E
    matrix.writeDigitRaw(0, 121);
    //S
    matrix.writeDigitRaw(1, 109);
    //T
    matrix.writeDigitRaw(3, 49);
    //P
    matrix.writeDigitRaw(4, 115);
  }
  */

  //calculate period
  if (spd > .05) {
    period = 60.0 * 1000.0 / spd;
   
    
  //prox switch
  if (digitalRead(PROX) == 0 && (millis() - last_prox) > (period / 2) )
  {
    //00.0 format
    //prepend the leading zero
    if (spd < 10.0) {
      Serial.print("0");
    }
    Serial.println(spd, 1);
    last_prox = millis();
  }
  }

  //update display last thing
  matrix.writeDisplay();
}



