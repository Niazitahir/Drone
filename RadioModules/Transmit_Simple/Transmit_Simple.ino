#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//radio
RF24 radio(7,8); // CE, CSN
int fail = 0;
const byte address[6] = "00001";
char text[10] = "";
//analog inputs
int thrust = A1;
int pan = A2;
int xAxis = A4;
int yAxis = A3;
uint8_t potValue[4];
//Discrete output
int redpin = 5; //select the pin for the red LED D2
int bluepin =6; // select the pin for the blue LED D3
int greenpin =7;// select the pin for the green LED D4


void setup(){
  Serial.begin(9600);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(thrust, INPUT);
  //pinMode(pan, INPUT);
  pinMode(xAxis, INPUT);
  //pinMode(yAxis, INPUT);
  if(!radio.begin()){
    analogWrite(redpin, 255);
    analogWrite(bluepin, 128);
    analogWrite(greenpin, 0);
    Serial.println("Radio Failed. Womp Womp");
    //while(true){}
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
    //while(1){}
  }
  analogWrite(redpin, 0);
  analogWrite(bluepin, 0);
  analogWrite(greenpin, 1024);
}
void updateHardware(){
  int thr = analogRead(thrust);
  thr = (uint8_t) map(thr, 1, 1023, 0, 127);
  //Serial.println(thr);
  //set all values of potValue arr to thrust at first
  //memset(potValue, thr, sizeof(potValue));
  potValue[0] = thr;potValue[1] = thr;potValue[2] = thr;potValue[3] = thr;
  
  int xA = analogRead(xAxis);
  
  xA-=510;
  xA =  (int8_t) map(xA, 0, 510, 0, (thr/2));
  Serial.println(xA);
  if (xA <= 0){
    potValue[0] += xA;
    potValue[1] += xA;
  }
  if (xA >= 0){
    potValue[2] -= xA;
    potValue[3] -= xA;
  }
  //Serial.print(potValue[0]); Serial.print(":");Serial.print(pot Value[1]); Serial.print(":");Serial.print(potValue[2]); Serial.print(":");Serial.println(potValue[3]);

  //xA = map(xA, 511, 1023, 0, thr);
  


  // potValue = analogRead(thrust);
  // potValue = map(potValue, 1, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  
}

void loop(){
  
  updateHardware();
  //sprintf(text, "%ld", potValue[0]);
  if(!radio.write(&potValue, sizeof(potValue))){
    //Seria.println("Error transmitting");
    Serial.println("Failt");
  }
  else{
    //Serial.println("Hello World transmitted");
    Serial.println(potValue[1]);
  }
  delay(100);
}
