#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial mySerial(7, 6);
 double la,lg,sped;
     int count=23;
    int stat;
     String des;
void setup() //Setup Subprocedure
{  
  Serial.begin(19200);


 
  mySerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);    // the Serial baud rate
  delay(1000);
}
 
void loop() // Main loop
{

   
  
   
     la=22.244555;
     lg=91.7777;
     sped=3.90;
     count=23;;
     stat=1;
     des="kumira";
  int y = 111111;
   
    String latL=String(la);
    String lngL=String(lg);
    String speedL=String(sped);
    String pas=String(count);
    String st=String(stat);
String no = "iiuc-123";

    Serial.print(" iiuc bus ");
    Serial.print(no);
    Serial.print(",");
//    Serial.print(reader++);
    Serial.println();
  // Send2Pachube(sms);
    Send2Pachube(latL, lngL, speedL, pas, des, st, no);
    delay(2000);
   
  
}

void Send2Pachube(String latL, String lngL, String speedL, String pas, String des, String st, String no) 
//void Send2Pachube(String sms)       //send data with gsm
{
 mySerial.println("AT+CSQ"); // Signal quality check
  delay(1000);
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
//  mySerial.print("AT+HTTPPARA=\"URL\",\"iiuctmdpro.000webhostapp.com/test.php?test=");
//mySerial.print(sms);
mySerial.print("AT+HTTPPARA=\"URL\",\"iiuctmdpro.000webhostapp.com/bustest/bustest.php?lat="+latL+"&lng="+lngL+"&speed="+speedL+"&pass="+pas+"&des="+des+"&stat="+st+"&no="+no);
//  Send2Pachube(stat,des,lt,lg,sped,count);Longitude=" + szLon ",Latitude=" + szLat;

//mySerial.println(latL" ,lng=" + lngL ",speed=" + speedL ",pass=" + pas ", des=" + des ",stat=" + st ",no=" + no);
//mySerial.println("&lng=");
//mySerial.println(lngL);
//mySerial.println("&speed=");
//mySerial.println(speedL);
//mySerial.println("&pass=");
//mySerial.println(pas);
//mySerial.println("&des=");
//mySerial.println(des);
//mySerial.println("&stat=");
//mySerial.println(st);
//mySerial.println("&no=");
//mySerial.println(no);
mySerial.println("\"");

// setting the httppara, the second parameter is the website you want to access
  delay(1000);
 
  ShowSerialData();
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.

 ShowSerialData();
mySerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);

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
