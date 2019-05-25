#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);


String api_key = "ULOEIIVLMBV10ALB"; //Thinkspeak data write API KEY 


String field = "4"; //Thinkspeak data writing field no


const int sensor = 0;
float sensordata = 0;

void setup() //Setup Subprocedure
{  
  pinMode (sensor, INPUT); //set Analog pin 0 as input
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the Serial baud rate
  delay(1000);
}
 
void loop() // Main loop
{
     sensordata = analogRead(sensor);
     delay(2);
     Send2Pachube();
     Serial.println(sensordata);
   
  if (mySerial.available())
    Serial.write(mySerial.read());
}


void Send2Pachube()       //send data with gsm
{
  mySerial.println("AT"); //check gsm
  delay(1000);

  mySerial.println("AT+CPIN?"); //Check if sim locked with pin
  delay(1000);

  mySerial.println("AT+CREG?"); //Check if gets registered to sim network
  delay(1000);

  mySerial.println("AT+CGATT?"); //Check if gets attached to registered network
  delay(1000);

  mySerial.println("AT+CIPSHUT"); //Close any previous active PDP (Packet data protocol) context
  delay(1000);

  mySerial.println("AT+CIPSTATUS"); //Check current connection status (bearer, TCP/UDP, IP, Port etc.)
  delay(2000);

  mySerial.println("AT+CIPMUX=0"); //Deactive any multi IP connections
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"internet\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0"); //Set prompt if module is avail to send data
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=ULOEIIVLMBV10ALB&field4=0"; //thinkspeak data writing url
 // GET https://api.thingspeak.com/update?api_key=ULOEIIVLMBV10ALB&field4=7
  
  mySerial.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();

  mySerial.println((char)26);//sending
  delay(5000);//waiting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
}

void ShowSerialData() //Show serial data
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
    Serial.println();
}
