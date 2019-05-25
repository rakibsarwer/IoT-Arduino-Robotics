#include <ThingSpeak.h>

#include<ESP8266WiFi.h>

 

const char*ssid= “Your internet id”;

const char* password=”Your internet password”;

const char* server= “api.thingspeak.com”;

float temp= 0;

int analog=0;

 

WiFiClient client;

unsigned long myChannelNumber = your channel number from Thingspeak;

const char * myWriteAPIKey = “Your api key”;

 

void setup() {

  // put your setup code here, to run once:

Serial.begin(9600);

delay(10);

WiFi.begin(ssid, password);

Serial.println();

Serial.println();

Serial.print(“Connecting to”);

Serial.println(ssid);

WiFi.begin(ssid, password);

while( WiFi.status()!=WL_CONNECTED){

  delay(500);

  Serial.print(“.”);

}

Serial.println(“”);

Serial.println(“WiFi connected”);

ThingSpeak.begin(client);

}

 

void loop() {

  // put your main code here, to run repeatedly:

analog=analogRead(17);

float temp= 0.322*analog;

 

  Serial.print(“Temeperature:”);

  Serial.print(temp);

//  Serial.print(“%send to Thingspeak”);

//Serial.println(“Waiting…”);

ThingSpeak.writeField(myChannelNumber, 1, temp, myWriteAPIKey);

delay(20000);

}
