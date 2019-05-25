#include <RFID.h>
#include <SPI.h>z
#include <String.h   >
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#define SDA_DIO 15
#define RESET_DIO 0
int Green =16;
int Red =2;
int pos;
Servo myservo;

RFID RC522(SDA_DIO, RESET_DIO); 

const char* ssid     = "pi";
const  char* password = "opencv123";
const char* host = "iiuctmdpro.000webhostapp.com";


const byte LCDcolumns = 16;
const byte LCDrows = 2;


// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

void setup() //Setup Subprocedure
{  
  Serial.begin(19200);
   lcd.init();
  lcd.backlight();
  lcd.home();
    myservo.attach(D4); 
 pos = 90;
  myservo.write(pos);

  pinMode(Green,OUTPUT);
  pinMode(Red,OUTPUT);
  SPI.begin(); 
  RC522.init();
  delay(1000);
 
   Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() // Main loop
{

     byte i;
      
     delay(2);
  
    
    if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    int x = RC522.serNum[0];
   
    String sms = String(x);
    String stat = "kumira";
 
    Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/veh/iobus.php?";
  url += "bus=";
  url += sms;
  url += "&stat=";
  url += stat;


  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    //Serial.print(line);
      Serial.println();

     if(line.indexOf("have")!=-1)
     {
      Serial.println("Uhu inserted");
      
      
      digitalWrite(Green,HIGH);
      digitalWrite(Red,LOW);
      lcd.clear();
      lcd.print("Access Authorized");
//delay(2000);
lcd.setCursor(2,1);
lcd.print("Inserted");
delay(2000);
digitalWrite(Green ,LOW);
   digitalWrite(Red,LOW);
      
       pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
   
      }
      else if(line.indexOf("not")!=-1)
     {
      Serial.println("failed to inserted");
      digitalWrite(Green,LOW);
      digitalWrite(Red,HIGH);
       lcd.clear();
      lcd.print("Access Unorized");
//delay(2000);
lcd.setCursor(2,1);
lcd.print("Failed to Insert");
delay(2000);
      
      pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
   
      
     
      }

  }

  Serial.println();
  Serial.println("closing connection");

  delay(10000);
  
}
}



