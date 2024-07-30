#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_LSM303_U.h>
#include "globalVars.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

int loop_count = 0;
int wdt_counter = 0;

void watchdogStart(void)
{
  cli();  // disable all interrupts 
  wdt_reset(); // reset the WDT timer
/*
//WDTCSR configuration:
WDIE = 1: //Interrupt Enable 
WDE = 1 : //Reset Enable
WDP3 = 0 :
For 2000ms Time-out WDP2 = 1 :
For 2000ms Time-out WDP1 = 1 :
For 2000ms Time-out WDP0 = 1 :
    For 2000ms Time-out
    */
  // Enter Watchdog Configuration mode: 
  WDTCSR |= (1<<WDCE) | (1<<WDE); // Set Watchdog settings:
  WDTCSR = (1<<WDIE) | (0<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0); 
  sei();
}

void watchdogArm(void)
{
  cli();  // disable all interrupts 
  wdt_reset(); // reset the WDT timer
/*
//WDTCSR configuration:
WDIE = 1: //Interrupt Enable 
WDE = 1 : //Reset Enable
WDP3 = 0 :
For 2000ms Time-out WDP2 = 1 :
For 2000ms Time-out WDP1 = 1 :
For 2000ms Time-out WDP0 = 1 :
    For 2000ms Time-out
    */
  // Enter Watchdog Configuration mode: 
  WDTCSR |= (1<<WDCE) | (1<<WDE); // Set Watchdog settings:
  WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0); 
  sei();
}


void setup() {
  Serial.begin(9600);
  delay(100);

  watchdogStart(); 
  
  gyroSetup();
  accelSetup();
  magSetup();



}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(curX);
  delay(1500);
  wdt_reset();
  watchdogStart();
  wdt_counter = 0;
}
ISR(WDT_vect)
{
  updateAverageAccel();
  if(wdt_counter==0)
  {
  wdt_counter++;
  watchdogArm();
  }

}
