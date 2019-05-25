#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial sende(0,1);

void setup() {
  Serial.begin(9600);
  //Serial S Begin at 9600 Baud
  sende.begin(9600);
}

void loop() {
  //Write '123' to Serial

sende.write(45);

  
}
