
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <AES.h>


const char *ssid = "fahim";  
const char *password = "fsc12345"; 

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
char temperatureCString[6];
char temperatureFString[6];


//Prepare Mqtt connection data
const char *MQTTBroker = "m11.cloudmqtt.com";
const char *MQTTuser = "temp";
const char *MQTTpassword = "temp";
const char *Topic = "Home/Patient/Temperature";
const char *Topicid = "/value";
uint16_t port = 16078;
//uint16_t port = 1883;  //default port

int count = 0;

PubSubClient mqtt(MQTTBroker,port);

void callback(const MQTT::Publish& pub){
  // handle message arrived
  Serial.println(pub.payload_string());
}
void setup()
{

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  DS18B20.begin();
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

  mqtt.set_callback(callback);  //Set Callback function

  

  if (mqtt.connect(MQTT::Connect("esp8266").set_auth(MQTTuser,MQTTpassword))){
    mqtt.publish(Topic, "Hello");  //publish
    mqtt.subscribe(Topicid);    //subscribe
  }

}
 
  void loop()
  {

  float tempC;
  float tempF;
  
  do {
    DS18B20.requestTemperatures(); 
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, temperatureCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, temperatureFString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0));

  count = tempF;
  String con = String(count);
  delay(1000);

  mqtt.publish(Topic, con);  //publish
  if(mqtt.subscribe(Topicid)!=0)    //subscribe
  {
  
    
  Serial.println(Topicid);
  }
  
  
  mqtt.loop();
}
  

