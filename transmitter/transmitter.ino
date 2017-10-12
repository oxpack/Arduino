// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "LowPower.h"

const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int sw = 3;
//const int transmit_en_pin = 3;

Adafruit_BME280 bme; // I2C

void setup()
{
  Serial.begin(9600);
  bool status, blink;
  pinMode(led_pin, OUTPUT);

  // default settings
  status = bme.begin();
  while (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    digitalWrite(led_pin, blink);
    blink++;
    delay(1000);
  }


  delay(100); // let sensor boot up

  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  //vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  pinMode(sw, INPUT_PULLUP);
}

void GetValues(char*);
//unsigned long time;

void loop()
{
  int i;
  char msg[] = "T-xxxxHyyyPzzzz";

  Temp(msg);
  Serial.print("Send: ");
  Serial.print(msg);
  SendMsg(msg);

  Hum(msg);
  Serial.print("Send: ");
  Serial.print(msg);
  SendMsg(msg);

  Pres(msg);
  Serial.print("Send: ");
  Serial.print(msg);
  SendMsg(msg);

  //time = millis();
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
//  while (millis() - time < 20000 && digitalRead(sw) == HIGH) {
  //  delay(1000);
  //}
}


void SendMsg(char * buffer) {
  int len, i;
  for (i = 0; i < 16 ; i++) {
    if (buffer[i] == '\n') {
      len = i;
      break;
    }
  }
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)buffer, len + 1);
  vw_wait_tx(); // Wait until the whole message is gone
  delay(100); //wait 100 milliseconds between sends
  digitalWrite(led_pin, LOW);

}


void Temp(char * buffer) {
  //T-1234
  float temp = bme.readTemperature();
  sprintf(buffer, "T%c%04d\n", temp > 0 ? '+' : '-', (int) abs(temp * 100.0) );
}

void Hum(char * buffer) {
  sprintf(buffer, "H%03d\n", int(bme.readHumidity() * 10.0 + .5));
}

void Pres(char * buffer) {
  sprintf(buffer, "P%04d\n", int(bme.readPressure() / 10.0 + .5));
}


