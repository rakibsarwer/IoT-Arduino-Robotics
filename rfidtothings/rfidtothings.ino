#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial
String apiKey = "KWNXQUPD13PLR72O";
//const int sensor = A0;
 
//Variables
ESP8266WiFiMulti WiFiMulti;

//RFID CODE start here
#include <RFID.h>
#include <SPI.h>
#include <String.h>
#include <SoftwareSerial.h>

#define SDA_DIO D8
#define RESET_DIO D3

RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;
String x[3]={};

//SoftwareSerial gsm(D7, D8, false, 256); // Rx, Tx //For Wemos

String api_key = "3VEPK689ANR7ZWAC"; //Thinkspeak data write API KEY 
String field = "1"; //Thinkspeak data writing field no


const int sensor = 0;
float sensordata = 0;

//RFID CODE end here

void setup() {
  //RFID CODE START

  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
   //pinmode (sensor, INPUT); //set Analog pin 0 as input
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the Serial baud rate
  delay(1000);

  //RFID CODE END

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
    WiFiMulti.addAP("Xtreem", "*+3wrasm!");

}

void loop() {
  
//RFID CODE START
  /* Temporary loop counter */
  byte i;

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    int x = RC522.serNum[0];
    String sms = String(x);
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
    Serial.print(x);
    Serial.print(",");
    Serial.print(reader++);
    Serial.println();

    //RFID END CODEE
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
    postStr += String(x);
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

