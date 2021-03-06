/* ESP8266+Arduino IDE Test code
Object :
- TCP Socket(port 4444) Server.
- ESP8266 AP mode test.
Requirement :
- ESP8266WiFi.h Library (https://github.com/esp8266/Arduino)
- PubSubClient.h Library (https://github.com/Imroy/pubsubclient)
- DW.miniESP board  (https://github.com/deaware/dwminiesp_firmware_support)
- Arduino IDE 1.6.4

Write by : Myconfix (http://www.myconfix.com/)
Fanpage : https://www.facebook.com/myconfix
github : https://github.com/myconfix/ESP8266ArduinoExample
*/


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Prepare AP id&password.
const char *ssid = "SocGrounD Rmutt";  //your access point ssid // cannot be longer than 32 characters!
const char *password = "computer54"; //your access point password


//Prepare Mqtt connection data
const char *MQTTBroker = "m11.cloudmqtt.com";
const char *MQTTuser = "big";
const char *MQTTpassword = "big";
const char *Topic = "/big";
const char *Topicid = "/big";
uint16_t port = 15659;
//uint16_t port = 1883;  //defalut port

int sw = 5;



PubSubClient mqtt(MQTTBroker,port);

void callback(const MQTT::Publish& pub){
	// handle message arrived
	Serial.println(pub.payload_string());
}
void setup()
{

  pinMode(sw,INPUT);

	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	WiFi.printDiag(Serial);

	mqtt.set_callback(callback);  //Set Callback function

	if (mqtt.connect(MQTT::Connect("esp8266").set_auth(MQTTuser,MQTTpassword))){
		mqtt.publish(Topic, "Hello");  //publish
		mqtt.subscribe(Topicid);		//subscribe
	}

}


void loop()
{
	mqtt.loop();
  
  if()
  mqtt.publish(Topic, "Hello");  //publish
  delay(1000);
}
