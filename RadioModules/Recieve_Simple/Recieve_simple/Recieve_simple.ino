#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  if(!radio.begin()){
    Serial.println("Radio Failed. Womp Womp");
    while(true){}
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  Serial.println("Polling, please hold");
  if (radio.available()) {
    Serial.println("Transmitting...");
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  delay(1000);
}