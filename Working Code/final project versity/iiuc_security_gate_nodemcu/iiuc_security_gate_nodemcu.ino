#include <RFID.h>
#include <SPI.h>
#include <String.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#define SDA_DIO 15
#define RESET_DIO 5
int Green = D2;
int Red = D0;
int pos=90;
Servo myservo;

RFID RC522(SDA_DIO, RESET_DIO); 

const char* ssid     = "Ke Diyeche!";
const  char* password = "hasinahahaha";
const char* host = "iiuctmdpro.000webhostapp.com";

void setup() //Setup Subprocedure
{  
  Serial.begin(19200);
    myservo.attach(D4); 

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

     if(line.indexOf("inserted")!=-1)
     {
      Serial.println("Uhu inserted");
      digitalWrite(Red ,LOW);
      digitalWrite(Green,HIGH);
      
       pos = 180;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
   delay(200);
      }
      else if(line.indexOf("failed")!=-1)
     {
      Serial.println("failed to inserted");
      digitalWrite(Green,LOW);
      digitalWrite(Red,HIGH);
      pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
   
      
     
      }

  }

  Serial.println();
  Serial.println("closing connection");

  delay(10000);
  
}
}



