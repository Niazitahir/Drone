#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7,8); // CE, CSN
int fail = 0;
const byte address[6] = "00001";

int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the blue LED
int greenpin =16;// select the pin for the green LED

Servo ESC;     // create servo object to control the ESC
Servo ESC2;
int potValue = 0;  // value from the analog pin


void setup() {
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  delay(100);
  if(!radio.begin()){
    analogWrite(redpin, 255);
    analogWrite(bluepin, 128);
    analogWrite(greenpin, 0);
    Serial.println("Radio Failed. Womp Womp");
    while(true){}
  }
  radio.openWritingPipe(address);
  radio.setPALevel(HIGH);
  radio.stopListening();
  radio.setAutoAck(0);
  radio.setDataRate(RF24_2MBPS); // Set the speed of the transmission to the quickest available
  radio.setChannel(124); // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setPALevel(RF24_PA_MAX); // Set radio Tx power to MAX
  delay(100);
  if(radio.isChipConnected()){
    Serial.println("Radio Transmitter Module Active");
  }
  else{
    Serial.println("Failed to connect");
    while(1){}
  }
  analogWrite(redpin, 0);
  analogWrite(bluepin, 0);
  analogWrite(greenpin, 1024);
  digitalWrite(LED_BUILTIN, HIGH);
}
void updateHardware(){
  potValue = analogRead(A7);
  potValue = map(potValue, 1, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
}
void loop() {
  char text[10] = "";
  updateHardware();
  sprintf(text, "%ld", potValue);
  if(!radio.write(&text, sizeof(text))){
    //Seria.println("Error transmitting");
    Serial.println("Failt");
  }
  else{
    //Serial.println("Hello World transmitted");
    Serial.println(text);
  }
  delay(100);
}