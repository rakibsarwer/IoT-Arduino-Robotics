#include <ESP8266WiFi.h>
#include <WiFiClient.h>

 #define LED 2

const char* ssid     = "RED_TUTOELECTRO";
const char* password = "tutoelectro123";

WiFiServer servidorTCP(8266);
WiFiClient clienteTCP;



void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  delay(100);
  
  Serial.print("Conectandose a: ");
  Serial.println(ssid);


  WiFi.begin(ssid, password);  //Intentamos conectarnos a la red Wifi
  
  while (WiFi.status() != WL_CONNECTED) {  //Esperamos hasta que se conecte.
    delay(200);
  }

  Serial.print ("Conectado, IP: ");
  Serial.println (WiFi.localIP());

  servidorTCP.begin();

}

void loop() {

  if (!clienteTCP.connected()) {
        // try to connect to a new client
        clienteTCP = servidorTCP.available();
    } else {
        // read data from the connected client
        if (clienteTCP.available() > 0) {
            char dato = clienteTCP.read();
            

            if (dato == '1'){
              digitalWrite(LED_BUILTIN, HIGH);
              Serial.write(dato);
            }
            else if (dato == '0'){

              digitalWrite(LED_BUILTIN, LOW);
              Serial.write(dato);
              
            }
              

           
              
        }
    }
     
     
     
      

}
