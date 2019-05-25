#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Debug.h>
#include <MFRC522Extended.h>
#include <MFRC522Hack.h>
#include <require_cpp11.h>
#include <RFID.h>

/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */
#include <SPI.h>


#include <SoftwareSerial.h>


#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
//#include <DHT.h>

#define USE_SERIAL Serial
String apiKey = "ULBKA6Y8EHZ9T206";
//#define DHTPIN 2     // what pin we're connected to
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

const int sensor = A0;
 
//Variables
int chk;
float hum;  //Stores humidity value
String s;
ESP8266WiFiMulti WiFiMulti;
#define SDA_DIO 9
#define RESET_DIO 8

/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;
String RFID[3]={};

void setup() {
  Serial.begin(9600);

  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Shakil10vr", "game0n123");

}

void loop() {
byte i;

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    int RFID = RC522.serNum[0];
    String y = String(RFID);
    String sms = String("Dear Admin, Bus No: "+ y + " Just leaved from IIUC Campus. Thanks for using real time bus monitoring System.");
    /* Output the serial number to the UART */
  
    /*
    int x[200];
    for(i = 0; i <= 2; i++)
    {
      Serial.println(RC522.serNum[i],DEC);
      x[i]=RC522.serNum[i]; 
      //Serial.print(RC522.serNum[i],HEX);
    }*/
        
    Serial.print(" iiuc bus ");
    Serial.print(RFID);
    Serial.print(",");
    Serial.print(reader++);
    Serial.println();
    //SendMessage(sms);
    delay(2000);
   }
  delay(1000);
  
  delay(2000);
    //Read data and store it to variables hum and temp
    //hum = dht.readHumidity();
    //int rawvoltage= analogRead(sensor);
    //float millivolts= (rawvoltage/1024.0) * 5000;
    //float sensordata= millivolts/10;
    //Print temp and humidity values to serial monitor
     //Delay 2 sec.
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(RFID);
    //postStr +="&field2=";
    //postStr += String(sensordata);
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        http.begin("http://api.thingspeak.com/update?api_key="+postStr); //HTTP

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(10000);
}

