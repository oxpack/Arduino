// receiver.pde
//
// Simple example of how to use VirtualWire to receive messages
// Implements a simplex (one-way) receiver with an Rx-B1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: receiver.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <SoftwareSerial.h>
#include <Wire.h>
//#include "RTClib.h"

SoftwareSerial mySerial(9, 10); // RX, TX
//RTC_DS1307 rtc;

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
const int sensorPin = 0;
unsigned long previousMillis = 0;  

//const int transmit_en_pin = 3;

void setup()
{
  delay(1000);
  
  
  //serial to debug
  Serial.begin(9600);	// Debugging only

  //for receiving 433 mhz
  mySerial.begin(2400);

  Serial.println("##Starting and waiting for msg");

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  //vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  pinMode(led_pin, OUTPUT);
}
float temp;
char temp_c[10];


void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  

  if (vw_get_message(buf, &buflen) ) // Non-blocking
  {
    int i;
    digitalWrite(led_pin, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.

    for (i = 0; i < buflen - 1; i++)
    {
      Serial.print(char(buf[i]));
    }
    Serial.println();
    digitalWrite(led_pin, LOW);
  }
  
  if(millis()-previousMillis>20000)
  {
    temp = float(analogRead(sensorPin)) / 1024.0 * 500.0;
    temp = (temp - 32.0) * 5.0 / 9.0;
    sprintf(temp_c, "t%c%04d\n", temp>0?'+':'-',(int) abs(temp * 100.0) );
    
    Serial.print(temp_c);
  
    previousMillis = millis();
  }
}



