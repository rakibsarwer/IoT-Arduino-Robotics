#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);




//String api_key = "KWNXQUPD13PLR72O"; //Thinkspeak data write API KEY 


//String field = "1"; //Thinkspeak data writing field no


void setup() //Setup Subprocedure
{  
  Serial.begin(19200);
  /* Enable the SPI interface */

  mySerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);    // the Serial baud rate
  delay(1000);
}
 
void loop() // Main loop
{


int i;
//int x=5;
  //  for(i = 0; i <= x; i++)
    //{
     
      //x[i]=RC522.serNum[i]; 
      //Serial.print(RC522.serNum[i],HEX);
    //}*/
    int x = 66;
   
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
        
  
   Send2Pachube(sms);
    delay(2000);

  
}


void Send2Pachube(String sms)       //send data with gsm
{
 /* mySerial.println("AT"); //check gsm
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
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"127.0.0.1\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  String str="GET https://testProj/send.php?request="+ smsz;  
  
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
*/
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
  mySerial.print("AT+HTTPPARA=\"URL\",\"iiuctmdpro.000webhostapp.com//test.php?test=");
mySerial.print(sms);
mySerial.println("\"");
//String str="AT+HTTPsPARA=\"URL\",\"rakibsarwar3.000webhostapp.com/bus.php?bus=\""+sms;  
  
  //mySerial.println(str);//begin send data to remote server
   //mySerial.println("AT+HTTPPARA=\"URL\",\"rakibsarwar3.000webhostapp.com/bus.php?bus=\""+sms);// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());
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
