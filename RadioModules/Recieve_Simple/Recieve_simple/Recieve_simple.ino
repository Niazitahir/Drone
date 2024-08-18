#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
Servo ESC;     // create servo object to control the ESC
Servo ESC2;
int redpin = 14; //select the pin for the red LED
int bluepin =15; // select the pin for the blue LED
int greenpin =16;// select the pin for the green LED

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

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
    analogWrite(greenpin, 128);
    analogWrite(bluepin, 0);
    Serial.println("Radio Failed. Womp Womp");
    while(true){}
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(HIGH);
  radio.startListening();
  radio.setAutoAck(0);
  radio.setDataRate(RF24_2MBPS); // Set the speed of the transmission to the quickest available
  radio.setChannel(124); // Use a channel unlikely to be used by Wifi, Microwave ovens etc
  radio.setPALevel(RF24_PA_MAX); // Set radio Tx power to MAX
  if(radio.isChipConnected()){
    Serial.println("Radio Reciever Module Active");
  }
  else{
    Serial.println("Failed to connect");
    while(1){}
  }
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(6,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 

  analogWrite(greenpin, 255);
  analogWrite(bluepin, 0);
  analogWrite(redpin, 0);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (radio.available()) {
    Serial.println("Recieving...");
    char text[10] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    int finalThrust;
    sscanf(text, "%d", &finalThrust);
    ESC.write(finalThrust);    // Send the signal to the ESC
    ESC2.write(finalThrust);    // Send the signal to the ESC
  }

  delay(50);
  Serial.print("=");
}