#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
#include <RTClib.h>
#include <EEPROM.h>

#define DELAY 1000

RTC_DS1307 rtc;

int daysleft = 0;
int hoursleft = 0;
int minleft = 0;
int secleft = 0;

int year, month , day, hour, minute , second ;
unsigned long last, realtime, alarm;

Adafruit_7segment matrix1 = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  int i = 0;

  matrix1.begin(0x71);   //mm:ss
  //0x02 center colon
  //0x04 left lower dot
  //0x08 left upper dot
  //0x10 decimal point
  matrix1.print(8888, DEC);
  matrix1.writeDigitRaw(2, 0x02 | 0x04 | 0x08 | 0x10);
  matrix1.writeDisplay();

  matrix2.begin(0x70); //dd:hh
  matrix2.print(8888, DEC);
  matrix2.writeDigitRaw(2, 0x02 | 0x04 | 0x08 | 0x10);
  matrix2.writeDisplay();
  delay(2000); // This delay allows the MCU to read the current date and time.

  Serial.print("The current date and time is: ");
  print_time(rtc.now());
  Serial.println("Please change to newline ending the settings on the lower right of the Serial Monitor");
  Serial.println("Would you like to set the clock date and time now? Y/N");

  while (!Serial.available() && i < DELAY) {
    i++;
    delay(20);
  }
  if (i < DELAY) {


    if (Serial.read() == 'y' || Serial.read() == 'Y')

      // This set of functions allows the user to change the date and time
    {
      Serial.read();
      rtc.adjust(setTime());
      Serial.print("The current date and time is now: ");
      print_time(rtc.now());
    }
  }

  EEPROM.get(0x0, alarm);
  DateTime tmp(alarm);

  Serial.print("The current alarm date and time is: ");
  print_time(tmp);
  Serial.println("Would you like to set the alarm date and time now? Y/N");
  i = 0;
  while (!Serial.available() && i < DELAY) {
    i++;
    delay(20);
  }

  if (i < DELAY) {

    if (Serial.read() == 'y' || Serial.read() == 'Y')

      // This set of functions allows the user to change the date and time
    {
      Serial.read();
      tmp = (DateTime) setTime();
      Serial.print("The current alarm date and time is now: ");
      print_time(tmp);
      alarm = tmp.unixtime();
      EEPROM.put(0, alarm);
    }
  }

}

void loop() {

  DateTime now = rtc.now();
  realtime = now.unixtime();
  //check to see if time is past alarm
  if (alarm < realtime) {
    daysleft = (realtime - alarm) / 60 / 60 / 24;
    hoursleft = (realtime - alarm) / 60 / 60 - daysleft * 24 ;
    minleft =  (realtime - alarm) / 60 - hoursleft * 60 - daysleft * 24 * 60;
    secleft = (realtime - alarm) - ((daysleft * 24 + hoursleft) * 60 + minleft) * 60;
  } else {
    daysleft = (alarm  - realtime) / 60 / 60 / 24  ;
    hoursleft = (alarm - realtime) / 60 / 60 - daysleft * 24;
    minleft =  (alarm - realtime) / 60 - hoursleft * 60 - daysleft * 24 * 60 ;
    secleft = (alarm - realtime) - ((daysleft * 24 + hoursleft) * 60 + minleft) * 60;
  }
  print_time(now);
  displayTime();
  delay(511);
}


void displayTime() {

  matrix1.writeDigitNum(0, minleft / 10);
  matrix1.writeDigitNum(1, minleft % 10);
  matrix1.writeDigitRaw(2, 0x02 | 0x04 | 0x08);
  matrix1.writeDigitNum(3, secleft / 10);
  matrix1.writeDigitNum(4, secleft % 10);
  matrix1.writeDisplay();

  //matrix2.print(daysleft * 100 + hoursleft, DEC);

  matrix2.writeDigitNum(0, daysleft / 10);
  matrix2.writeDigitNum(1, daysleft % 10);
  matrix2.writeDigitRaw(2, 0x02);
  matrix2.writeDigitNum(3, hoursleft / 10);
  matrix2.writeDigitNum(4, hoursleft % 10);
  matrix2.writeDisplay();
}

void displayClock(DateTime a) {

  matrix1.writeDigitNum(0, a.minute() / 10);
  matrix1.writeDigitNum(1, a.minute() % 10);
  matrix1.writeDigitRaw(2, 0x02 | 0x04 | 0x08);
  matrix1.writeDigitNum(3, a.second() / 10);
  matrix1.writeDigitNum(4, a.second() % 10);
  matrix1.writeDisplay();

  //matrix2.print(daysleft * 100 + hoursleft, DEC);

  matrix2.writeDigitRaw(0, 0);
  matrix2.writeDigitRaw(1, 0);
  matrix2.writeDigitRaw(2, 0x02);
  matrix2.writeDigitNum(3, a.hour() / 10);
  matrix2.writeDigitNum(4, a.hour() % 10);
  matrix2.writeDisplay();
}


void print_time(DateTime a) {
  Serial.print(a.month(), DEC);
  Serial.print("/");
  Serial.print(a.day(), DEC);
  Serial.print("/");
  Serial.print(a.year(), DEC);
  Serial.print(" ");
  Serial.print(a.hour(), DEC);
  Serial.print(":");
  Serial.print(a.minute(), DEC);
  Serial.print(":");
  Serial.println(a.second(), DEC);

}

// This set of codes is allows input of data
DateTime setTime() {
  Serial.print("Please enter the year, 2000-2020. - ");
  year = readByte();
  Serial.println(year);
  Serial.print("Please enter the month, 1-12. - ");
  month = readByte();
  Serial.println(month);
  Serial.print("Please enter the day of the month, 1-31. - ");
  day = readByte();
  Serial.println(day);
  Serial.print("Please enter the hour, 0-23. - ");
  hour = readByte();
  Serial.println(hour);
  Serial.print("Please enter the minute, 0-59. - ");
  minute = readByte();
  Serial.println(minute);
  DateTime date(year, month, day, hour, minute, 0);
  return date;
}

int readByte() {
  while (!Serial.available()) delay(10);
  int reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}
