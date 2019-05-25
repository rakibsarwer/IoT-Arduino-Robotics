#include <ESP8266WiFi.h>

const char* ssid     = "404 Network Unavailable";
const char* password = "*+3wrasm!";

const char* host = "rakibsarwar3.000webhostapp.com";

float sensor1 = 40;
float sensor2 = 50;
float sensor3 = 60;
int led1 = D1;
int led2 = D2;

void setup() {
  Serial.begin(9600);
  delay(10);
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
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

  sensor1 += 2;
  sensor2 += 2;
  sensor3 += 2;

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
  String url = "/ledtest/ledtest.php?";
  url += "sensor1=";
  url += sensor1;
  url += "&sensor2=";
  url += sensor2;
  url += "&sensor3=";
  url += sensor3;

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
      digitalWrite(led1,HIGH);
      }
      else if(line.indexOf("failed")!=-1)
     {
      Serial.println("failed to inserted");
      digitalWrite(led2,HIGH);
      digitalWrite(led1,LOW);
      }

  }

  Serial.println();
  Serial.println("closing connection");

  delay(10000);
  
}

