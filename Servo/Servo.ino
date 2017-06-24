#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;
#include <Servo.h>

Servo myservox,myservoy;  // create servo object to control a servo
// a maximum of eight servo objects can be created

void setup () {

  myservox.attach(9);
    myservoy.attach(8);
  Serial.begin(57600);
  Wire.begin();
  RTC.begin();

  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    //RTC.adjust(DateTime(__DATE__, __TIME__));
  }
/*  myservo.write(0);
  delay(5000);
  myservo.write(90);
  delay(5000);
  myservo.write(180);
  delay(5000);
  */
}
  int sec = -1;
  float anglex,angley;
  
void loop () {
  int sec = -1;
  float anglex,angley;
  DateTime now = RTC.now();
  sec = now.second();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(sec, DEC);
  anglex = 90.0 - 40.0 * sin( (float) sec * 3.14 / 180.0 * 6 );
  angley = 40.0 - 40.0 * cos( (float) sec * 3.14 / 180.0 * 6 );
  myservox.write(anglex);
  myservoy.write(angley);

  Serial.println("  ");


  delay(100);
}
