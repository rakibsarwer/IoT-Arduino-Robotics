#include <SoftwareSerial.h>

SoftwareSerial SIM900(7, 8); // configure software serial port
int REDLed= 2;
int GREENLed= 3;
int BLUELed= 4;

void setup() {     
  
  pinMode(REDLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  pinMode(GREENLed, OUTPUT);
  SIM900.begin(19200);
  Serial.begin(19200); 
  Serial.print("power up" );
  delay(30000); 

}


 
void loop()
{

  Serial.println("SubmitHttpRequest - started" );
  SubmitHttpRequest();
  Serial.println("SubmitHttpRequest - finished" );
  delay(10000);

}

void SubmitHttpRequest()
{
 
  SIM900.println("AT+CSQ"); // Signal quality check

  delay(100);
 
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  
  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
  delay(100);
 
  ShowSerialData();
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, Access point name string
  delay(4000);
 
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
  delay(2000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPINIT"); //init the HTTP request
 
  delay(2000); 
  ShowSerialData();
 
  SIM900.println("AT+HTTPPARA=\"URL\",\"sim900test.net46.net/getstate.php?color=All\"");// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!SIM900.available());
 
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  changeLed();
  ShowSerialData();
 
  SIM900.println("");
  delay(100);
}
 
void changeLed()
{
 String content = "";
// String RedState = content.substring();
 while(SIM900.available()!=0)
 {  
    //Serial.write(SIM900.read());
    content = content + String(char (SIM900.read()));
 }
    Serial.println(content);
 if(content.substring(30,31)== "1")
 {
   digitalWrite(REDLed, HIGH);
 }
 else if (content.substring(30,31)== "0")
 {
   digitalWrite(REDLed, LOW);
 }
 
 if(content.substring(31,32)== "1")
 {
   digitalWrite(GREENLed, HIGH);
 }
 else if (content.substring(31,32)== "0")
 {
   digitalWrite(GREENLed, LOW);
 }
 
 if(content.substring(32,33)== "1")
 {
   digitalWrite(BLUELed, HIGH);
 }
 else if (content.substring(32,33)== "0")
 {
   digitalWrite(BLUELed, LOW);
 }
 content = "";
}

 
void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char (SIM900.read()));
}
