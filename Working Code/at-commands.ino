#include <SoftwareSerial.h>

//SIM800L - TX, RX, ARDUINO RX,TX
SoftwareSerial Sim800l(10,11);



void setup() {
 Serial.begin(9600);
 Sim800l.begin(9600);
}

void loop() {
 
 while(Sim800l.available()){
  Serial.write(Sim800l.read());
 }
  
 while(Serial.available()){
  char inc = Serial.read();
  if(inc == '$'){
    Sim800l.write(char(26));  
  }else{
    Sim800l.write(inc);
  }
 }

}

