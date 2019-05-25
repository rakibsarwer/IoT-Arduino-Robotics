#include <RFID.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;


String api_key = "KWNXQUPD13PLR72O"; //Thinkspeak data write API KEY 


String field = "1"; //Thinkspeak data writing field no


void setup() //Setup Subprocedure
{  
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  //pinMode (sensor1, INPUT); //set Analog pin 0 as input

 
  mySerial.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);    // the Serial baud rate
  delay(1000);
}
 
void loop() // Main loop
{

      byte i;
      
     delay(2);
    
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
   Send2Pachube(sms);
    delay(2000);
   }
  delay(1000);
}


void Send2Pachube(String sms)       //send data with gsm
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
 
  mySerial.println("AT+CSTT=\"INTERNET\"");//start task and setting the APN,
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
  String str="GET https://api.thingspeak.com/update?api_key=KWNXQUPD13PLR72O&field3="+ sms;  
  
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
