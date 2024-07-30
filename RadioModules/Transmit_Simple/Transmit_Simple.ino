#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  delay(100);
  if(!radio.begin()){
    Serial.println("Radio Failed. Womp Womp");
    while(true){}
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  
  const char text[] = "Hello World";
  if(!radio.write(&text, sizeof(text))){
    Serial.println("Error transmitting");
  }
  else{
    Serial.println("Hello World transmitted");
  }
  delay(1500);
}