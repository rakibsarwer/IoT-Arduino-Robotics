#include <SoftwareSerial.h>
// #include "ThingSpeak.h"

SoftwareSerial mySerial(9, 10); //RX TX

int ledPin = 13;
float j=0;
//int sensor = A0;
//unsigned long myChannelNumber = 167279;
String apiKey = "YTB2U7SVRPOO7XGF";
void setup()
{
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // enable hwardware serial port
mySerial.begin(115200); //enable software serial port 
connectWiFi();
 //ThingSpeak.begin(client);
}
void loop() {
//float val=analogRead(sensor); float vout = (val*5000.0)/1023;
//float tempc=vout/10; // Storing value in Degree Celsius
j++;
digitalWrite(ledPin, HIGH); 
delay(500);
digitalWrite(ledPin, LOW);
mySerial.println("AT+CIPMUX=0\r\n"); 
delay(2000);
// TCP connection
String cmd = "AT+CIPSTART=\"TCP\",\"";
cmd += "184.106.153.149";
// api.thingspeak.com 
cmd += "\",80\r\n\r\n";
mySerial.println(cmd);
Serial.println(cmd);
delay(2000);
if(mySerial.available() >0)
{
delay(500); 
while(mySerial.available())
Serial.write( char (mySerial.read()));
}
if(mySerial.find("Error"))
{
Serial.println("AT+CIPSTART error");
return;
}
// prepare GET string
String getStr = "GET http://api.thingspeak.com/update?api_key=";
getStr += apiKey;
getStr +="&field1=";
getStr += j;
getStr += "\r\n\r\n";
// send data length
Serial.println(getStr);
cmd = "AT+CIPSEND=";
cmd += String(getStr.length()); 
cmd+="\r\n";
mySerial.println(cmd);
Serial.println(cmd);
delay(2000);
if(mySerial.find(">"))
{
Serial.println("connected to Cloud");
mySerial.print(getStr);
}
else
{
mySerial.println("AT+CIPCLOSE\r\n");
// alert user
Serial.println("AT+CIPCLOSE");
}
// thingspeak needs 15 sec delay between updates 
delay(16000);
}
boolean connectWiFi()
{
mySerial.println("AT+CWMODE=3\r\n");
String cmd = "AT+CWJAP=\""; 
cmd += "Xtreem";
cmd += "\",\"";
cmd += "*+3wrasm!";
cmd += "\"\r\n";
Serial.println(cmd);
mySerial.println(cmd);
delay(10000);
mySerial.println("AT+CWJAP?\r\n");
delay(2000);
if(mySerial.available() >0)
{
delay(500); 
while(mySerial.available())
Serial.write( char (mySerial.read()));
}
}
