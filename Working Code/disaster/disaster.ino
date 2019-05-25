

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


#include <SoftwareSerial.h>
#include <String.h>


#include <dht.h>

#define dht_apin A0 // Analog Pin sensor is connected to
SoftwareSerial mySerial(7, 6);
int trigPin1=9;
int echoPin1=10;


const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);


 
dht DHT;

int sensorPin = A1; // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the sensor

int led = 5; // Output pin for LED

int buzzer = 4; // Output pin for Buzzer


String api_key = "KN4WH0QQK48KBCEL"; //Thinkspeak data write API KEY 

String field1 ="1";
String field2 ="2";
String field3 ="3";
String field4 ="4";








void setup() {
   Serial.begin (9600);
    lcd.init();
  lcd.backlight();
  lcd.home();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  mySerial.begin(9600);               // the GPRS baud rate   
 
  delay(1000);
  pinMode(led, OUTPUT);

pinMode(buzzer,OUTPUT);
 
  
   Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 

}

void loop() {
  

  

Serial.println("Welcome to TechPonder Flame Sensor Tutorial");

sensorValue = analogRead(sensorPin);

Serial.println(sensorValue);

if (sensorValue < 100)

{

Serial.println("Fire Detected");
delay(5000);
lcd.clear();
lcd.print("Fire Attacks!");

Serial.println("LED on");

digitalWrite(led,HIGH);

digitalWrite(buzzer,HIGH);

delay(1000);

}

digitalWrite(led,LOW);

digitalWrite(buzzer,LOW);

delay(sensorValue);




 

    
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(5000);


 
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

   if (distance1 >=0 || distance1 <= 10){
    Serial.println("Flood Incomming!");
    lcd.clear();
lcd.print("Flood Incomming!");
digitalWrite(led,HIGH);

digitalWrite(buzzer,HIGH);

delay(1000);
  }
  else {
    digitalWrite(led,LOW);

digitalWrite(buzzer,LOW);
    Serial.print ( "Sensor1  ");
    Serial.print ( distance1);
    Serial.println("cm");
    
  }
  delay(2000);



    int uls1 = distance1;
    String us1 = String(uls1);

     int fire1 = sensorValue;
    String fire = String(fire1);

     int hum1 = DHT.humidity;
    String hum = String(hum1);

     int temp1 = DHT.temperature;
    String temp = String(temp1);

    

    
   

   
    

    Serial.println();
   Send2Pachube(us1,fire,hum,temp);
    delay(2000);
   
}



void Send2Pachube(String us1,String fire,String hum,String temp)       //send data with gsm
{
  mySerial.println("AT"); //check gsm
  delay(1000);

  mySerial.println("AT+CPIN?"); //Check if sim locked with pin
  delay(1000);

  mySerial.println("AT+CREG?"); //Check if gets registered to sim network
  delay(1000);

  mySerial.println("AT+CGATT?"); //Check if gets attached to registered network
  delay(1000);

  mySerial.println("AT+CIPSHUT"); //Close any previous active PDP (Packet data protocol) context
  delay(1000);

  mySerial.println("AT+CIPSTATUS"); //Check current connection status (bearer, TCP/UDP, IP, Port etc.)
  delay(2000);

  mySerial.println("AT+CIPMUX=0"); //Deactive any multi IP connections
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"INTERNET\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0"); //Set prompt if module is avail to send data
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=KN4WH0QQK48KBCEL&field1="+ us1+"&field2=" + fire + "&field3=" + hum+"&field4=" + temp ;  
  
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waiting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}

void ShowSerialData() //Show serial data
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
    Serial.println();
}
