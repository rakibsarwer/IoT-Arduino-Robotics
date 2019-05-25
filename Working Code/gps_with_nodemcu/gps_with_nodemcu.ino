#include <ESP8266WiFi.h>
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
const char* ssid     = "404 Network Unavailable";
const char* password = "*+3wrasm!";

const char* host = "rakibsarwar3.000webhostapp.com";

String str="student";
String des="chokbazar";
SoftwareSerial serial_connection(D8, D7); //tX=pin 11, rX=pin 10
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);



// this constant won't change:
const int  Up_buttonPin   = D3;    // the pin that the pushbutton is attached to
const int  Down_buttonPin = D4 ;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int up_buttonState = 0;         // current state of the up button
int up_lastButtonState = 0;     // previous state of the up button
int down_buttonState = 0;         // current state of the up button
int down_lastButtonState = 0;     // previous state of the up button
bool bPress = false;

void setup() {
  
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
pinMode( Up_buttonPin , INPUT_PULLUP);
 pinMode( Down_buttonPin , INPUT_PULLUP);
  lcd.init();
   lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Passenger Number:");
  lcd.setCursor(2,1);
  lcd.print(buttonPushCounter);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
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


void loop() {

  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");


  checkUp();
     checkDown();

    if( bPress){
       bPress = false;
      
    }
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
  String url = "/bustest/bustest.php?";
  url += "lat=";
  url += gps.location.lat();
  url += "&lng=";
  url += gps.location.lng();
  url += "&speed=";
  url += gps.speed.mph();
 url += "&pass=";
  url += 55;
  url += "&no=";
  url += 0017;
   url += "&type=";
  url +="'student'";
  url += "&des=";
  url +="'kumira'";
    url += "&stat=";
  url += 1;

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

     

  }

  Serial.println();
  Serial.println("closing connection");

  delay(10000);
  
  }

  lcd.clear();
      
      lcd.print("Passenger: ");
      lcd.setCursor(2,1);
      lcd.print(buttonPushCounter);

}

void checkUp()
{
  up_buttonState = digitalRead(Up_buttonPin);

  // compare the buttonState to its previous state
  if (up_buttonState != up_lastButtonState) {
    // if the state has changed, increment the counter
    if (up_buttonState == LOW||up_buttonState == HIGH  ) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
  //    lcd.clear();
//lcd.print("Pessenger:");
//delay(2000);
//lcd.setCursor(2,1);


      Serial.println("on");
      Serial.print("number of button pushes: ");
     lcd.print(buttonPushCounter);
    buttonPushCounter;
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  up_lastButtonState = up_buttonState;
}

void checkDown()
{
  down_buttonState = digitalRead(Down_buttonPin);

  // compare the buttonState to its previous state
  if (down_buttonState != down_lastButtonState) {
    // if the state has changed, increment the counter
    if (down_buttonState == LOW) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter--;
     
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  down_lastButtonState = down_buttonState;
}



