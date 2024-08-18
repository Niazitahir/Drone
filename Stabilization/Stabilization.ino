#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_LSM303_U.h>
#include "globalVars.h"
#include <avr/io.h>
#include <avr/interrupt.h>
//https://arduino.stackexchange.com/questions/9765/which-timer-can-i-use-to-control-a-servo-with-arduino-uno
//https://microcontrollerslab.com/arduino-timer-interrupts-tutorial/
//interrupts
//update current accel value
//counter the accel values
//reload = timer interrupt time. EX:
/*
System clock is 16Mhz and prescalar is 1024 for generating clock of 10ms
Speed of Timer2 = 16MHz/1024 = 15.625 KHz
Pulse Time = 1/15.625 KHz = 64 us
OCR= 10ms/64us = 156.25 ->156 (whole number)
*/
int volatile count = 0;
byte reload = 0xff; 
ISR(TIMER2_COMPA_vect)
{
  count = count + 1;
  //updateAverageAccel();
  OCR2A = reload;
}

void watchdogStart(void)
{
  cli();
  TCCR0B = 0; 
  OCR2A = reload;
  TCCR2A = 1<<WGM21;
  TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
  TIMSK2 = (1<<OCIE2A);
  sei();
  Serial.print("OCR2A: "); 
  Serial.println(OCR2A, HEX);
  Serial.print("TCCR2A: "); 
  Serial.println(TCCR2A, HEX);
  Serial.print("TCCR2B: ");
  Serial.println(TCCR2B, HEX);
  Serial.print("TIMSK2: "); 
  Serial.println(TIMSK2, HEX);
  Serial.println("TIMER2 Setup Finished.");
}

void setup() {
  Serial.begin(9600);
  delay(100);
  gyroSetup();
  accelSetup();
  magSetup();
  watchdogStart();  
  Serial.println("Hello");
}

void loop() {
  if (count == 20){
    cli();
    TIMSK2 = 0;
    sei();
    updateCurAccel();
    updateAll();
    Serial.println(curX);
    count = 0;
    cli();
    TIMSK2 = (1<<OCIE2A);
    sei();
  }
}
