#include <RFID.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;
#include <Servo.h>

int RED=6;
int GREEN=3;
int buzzer = 11;
Servo myservo;
int pos = 0;
int p, i,n;
int key[4]={214,22,56,60};

void setup() //Setup Subprocedure
{  
  Serial.begin(19200);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  //pinMode (sensor1, INPUT); //set Analog pin 0 as input
pinMode(RED,OUTPUT);
pinMode(GREEN,OUTPUT);
 myservo.attach(7); 
 pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'

pinMode(buzzer,OUTPUT);
 
    mySerial.begin(19200);
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

 delay(1000);

int position=0;

 
   for(i=0;i<4;i++)
   {
    position++;
    if(key[i]==x)
    {
      Serial.println("Welcome    bus accesed ");
       digitalWrite(buzzer,LOW);
        digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
   pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(2000);  
    pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
 Send2Pachube(sms);
 position--;
 
     break;
    
    }
    else
    {
      
      digitalWrite(buzzer,HIGH);
       delay(5000);   
       digitalWrite(buzzer,LOW);
       delay(500); 
       if(position==4) 
       {Serial.println("accesed Deniyed");}
        
        
          digitalWrite(GREEN,LOW);
  digitalWrite(RED,HIGH);
   pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
       
        
      } 
   }
   position=0;

   
   
      }
   }


    
void Send2Pachube(String sms)       //send data with gsm
{
 mySerial.println("AT+CSQ"); // Signal quality check
  delay(100);
  ShowSerialData();



  mySerial.println("AT+CGATT?"); //Check if gets attached to registered network
  delay(1000);
  ShowSerialData();

  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();

  mySerial.println("AT+SAPBR=3,1,\"APN\",\"INTERNET\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
  mySerial.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
  mySerial.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();
  mySerial.print("AT+HTTPPARA=\"URL\",\"flood-monitoring-sy.000webhostapp.com/iobus.php?bus=");
mySerial.print(sms);
mySerial.println("\"");
  delay(1000);
 
  ShowSerialData();
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
 
 ShowSerialData();
mySerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
 // changeLed();
  ShowSerialData();
 
  mySerial.println("");
  delay(100);

}




void ShowSerialData() //Show serial data
{
  while(mySerial.available()!=0)
    Serial.write(mySerial.read());
    Serial.println();
}
