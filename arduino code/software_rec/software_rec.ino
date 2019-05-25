
//#include<SoftwareSerial.h>
//SoftwareSerial mySerial(0,1);
void setup() {
Serial.begin(9600);
 
}

void loop() {
 int c="";
 if(Serial.available()>0)
 {
  c =Serial.parseInt();
  Serial.println(c);
 }
 //delay(5000);
}
