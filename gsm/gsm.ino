#include <SoftwareSerial.h>
#define SIM_800_TX 6
#define SIM_800_RX 7

int midZ=2000;//time delays
int minZ=500;
int maxZ=5000;

SoftwareSerial MySerial(SIM_800_RX, SIM_800_TX); // RX, TX

void setup() {

Serial.begin(9600);
while (!Serial);
MySerial.begin(9600);

delay(midZ);

MySerial.println("at+csq");
delay(minZ);
feedback();
MySerial.println("at+cipshut");
delay(minZ);
feedback();

MySerial.println("at+cstt=\"giffgaff.com\",\"giffgaff\",\"\"");
feedback();
MySerial.println("at+ciicr");//start wireless connection cellular network
feedback();
MySerial.println("at+cifsr");//enquire regarding the IP address allocated
feedback();
MySerial.println("at+cipstart=\"TCP\",\"184.106.153.149\",\"80\"");//connect to the ThingSpeak update URL (https://api.thingspeak.com)
feedback();
MySerial.println("at+cipsend=71");//declare the number of bytes (characters) I want to send
feedback();
MySerial.print("GET https://api.thingspeak.com/update?");//this is a constant beginning for the GET command and is as provided by ThingSpeak
feedback();
MySerial.print("api_key=IVEJWZMAPDSP2AXB");//the channel API key provided by ThingSpeak

feedback();
MySerial.print("&field1=");

feedback();
MySerial.println("5");//the value that I want to post to field 1
feedback();
MySerial.println("at+cipack");//ask for acknowledge details

feedback();
MySerial.println("at+cipclose");//close the IP connection
feedback();
}

void loop() {

if (MySerial.available()) {

Serial.write(MySerial.read());
}
if (Serial.available()) {

MySerial.write(Serial.read());
}
}

void feedback() {
delay(midZ);
while (MySerial.available()) {
Serial.write(MySerial.read());
}
}
