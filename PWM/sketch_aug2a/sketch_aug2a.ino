#include "global.h"
/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/
#include <Servo.h>

const unsigned int MAX_MESSAGE_LENGTH = 12;
int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the blue LED
int greenpin =16;// select the pin for the green LED

Servo ESC;     // create servo object to control the ESC
Servo ESC2;

int potValue = 0;  // value from the analog pin
String incomingByte;
int incomingInstr;

void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  Serial.begin(115200);
  delay(100);
  // Attach the ESC on pin 9
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(6,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  analogWrite(greenpin, 255);
  analogWrite(bluepin, 0);
  analogWrite(redpin, 0);
  Serial.println("Start");
}

void updateComputer(){
  if (Serial.available()){
    incomingByte = Serial.readString();
    incomingInstr = incomingByte.toInt();
    delay(20);
    Serial.println(incomingInstr);
    potValue = incomingInstr;
    potValue = map(potValue, 1, 9, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
    ESC.write(potValue);    // Send the signal to the ESC
    ESC2.write(potValue);    // Send the signal to the ESC
  }
}


void updateHardware(){
  potValue = analogRead(A7);
  potValue = map(potValue, 1, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  ESC.write(potValue);    // Send the signal to the ESC
  ESC2.write(potValue);    // Send the signal to the ESC
}
void loop() {
  updateHardware();
  delay(25);
  //potValue = analogRead(A7);   // reads the value of the potentiometer (value between 0 and 1023)
}