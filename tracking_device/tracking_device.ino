//gps start
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Key.h>
#include <Keypad.h>

#include <SoftwareSerial.h>
#include <String.h>


SoftwareSerial serial_connection(52, 51); //( TX=pin 10,RX=pin 11)
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
SoftwareSerial mySerial(7, 6);
//gps end

//passenger start 

// defines pins numbers
const int trigPin1 = 10;
const int echoPin1 = 9;
const int trigPin2 = 12;
const int echoPin2 = 11;
const int trigPin3 = 13;
const int echoPin3 = 8;

// defines variables
long duration,valA1,valA2,valA3;
int distance;
long duration1,duration2;
int distance1,distance2;
int count;

//passenger end 

//lcd start


double lg,lt,sped;


const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

//lcd end

//keypad start

String des;




int key=0;
int led_pin=2;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};



byte rowPins [ROWS] = {40,38,36,34}; //pins of the keypad
byte colPins [COLS] = {32,30,28,26};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//keypad end

//gprs start









//String api_key = "KWNXQUPD13PLR72O"; //Thinkspeak data write API KEY 


//String field = "1"; //Thinkspeak data writing field no

//gprs end

//Rocker switch Start

int pinButton = 3; //the pin where we connect the button
 //the pin we connect the LED
int stat;
//Rocker Switch End


void setup()
{
  //gps start
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
  //gps end

  //passenger start

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

  //passenger end

  //lcd start

   lcd.init();
  lcd.backlight();
  lcd.home();

  //lcd end

  //keypad start

   pinMode(led_pin,OUTPUT);

   //keypad end

   //gprs start

   mySerial.begin(9600);

   //gprs end 

   //rocker switch start

    pinMode(pinButton, INPUT); //set the button pin as INPUT
  

//rocker switch end


}

//passenger start

enum SIGNALSTATES
{
  ST_GREEN,
  ST_RED1,
  ST_RED2,
  ST_YELLOW,
};
SIGNALSTATES signalState=ST_GREEN;

//passenger end


void loop()
{
  //gps start
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
   // Serial.println(gps.location.lat(), 6);
     lt = gps.location.lat();
    Serial.println(lt);
    Serial.println("Longitude:");
    //Serial.println(gps.location.lng(), 6);
     lg = gps.location.lng();
    Serial.println(lt);
    Serial.println("Speed MPH:");
    //Serial.println(gps.speed.mph());
     sped = gps.speed.mph();
    Serial.println(sped);
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }

  //gps end

  //passenger start

  // Clears the trigPin
digitalWrite(trigPin1, LOW);
digitalWrite(trigPin2, LOW);
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Clears the trigPin
duration = pulseIn(echoPin1, HIGH);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration1 = pulseIn(echoPin2, HIGH);
delayMicroseconds(2);

digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration2 = pulseIn(echoPin3, HIGH);
delayMicroseconds(2);
// Reads the echoPin, returns the sound wave travel time in microseconds

// Calculating the distance
////distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
// Calculating the distance
//distance1= duration1*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(duration);
//Serial.print("Distance2: ");
//Serial.println(duration1);

valA1=duration;
 valA2=duration1;
 valA3=duration2;
 


switch(signalState)
{
  case ST_GREEN:
  signalgreen(valA1, valA2, valA3);
  break;
  case ST_RED1:
  signalred1(valA1, valA2, valA3);
  break;
  case ST_RED2:
  signalred2(valA1, valA2, valA3);
  break;
  case ST_YELLOW:
  signalyellow(valA1, valA2, valA3);
  break;
} 

//passenger end



//keypad start

char customKey = customKeypad.getKey();
 
    
   
    Serial.println(customKey);
 

    if (customKey =='A'){
     
     des="kumira";
     Serial.println(des);
    }
       if (customKey =='B'){
     
     des="bbt";
     Serial.println(des);
    }
       if (customKey =='C'){
     
      des="chawkbazar";
     Serial.println(des);
    }
       if (customKey =='D'){
     
      des="agrabad";
     Serial.println(des);
    }


  //keypad end



  //Rocker Switch start

  int stateButton = digitalRead(pinButton); //read the state of the button
  if(stateButton == 1) { //if is pressed
     digitalWrite(led_pin, HIGH);
       stat="1";
      Serial.println(stat);
     //write 1 or HIGH to led pin
  } else { //if not pressed
     digitalWrite(led_pin, LOW); 
      stat="0";
     Serial.println(stat);
    //write 0 or low to led pin
  }

 //Rocker Switch End

   //gprs start
//  String sms="45";
Send2Pachube(stat,des,lt,lg,sped,count);
  //lcd start



delay(100);
lcd.setCursor(0,0);
lcd.print("Stat");
lcd.setCursor(0,1);
lcd.print(stat);

lcd.setCursor(5,0);
lcd.print("Destination");
lcd.setCursor(5,1);
lcd.print(des);
delay(100);
lcd.clear();

//lcd end
  //gprs end

  
}


//passenger start

void signalgreen(int valA1, int valA2, int valA3){


  if (valA1<=2000&& valA2>=2000){
  
    signalState=ST_RED1;
  }
  else if (valA2>2000 && valA3<2000){
    
    signalState=ST_RED2;
  }
  
}

void signalred1(int valA1, int valA2, int valA3){
 
             // tell servo to go to position in variable 'pos'
   
     
 
    count++;
  
    //Serial.print(count);

    signalState=ST_YELLOW;
  
}

void signalred2(int valA1, int valA2, int valA3){
 
 

  count--;
 
//Serial.print(count);
    signalState=ST_YELLOW;
  
 
}

void signalyellow(int valA1, int valA2, int valA3){
           // tell servo to go to position in variable 'pos'

  if (valA1>2000&& valA2>2000 && valA3>2000){
    
//     lcd.clear();
Serial.print("Passenger :");
Serial.println(count);
//      lcd.print("Passenger:");
////delay(2000);
//lcd.setCursor(2,1);
//lcd.print(count);
;

 
    signalState=ST_GREEN;
    
  } 
}

//passenger end

//gprs start 

void Send2Pachube(int stat,String des,double lt,double lg,double sped,int count)       //send data with gsm
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
  mySerial.print("AT+HTTPPARA=\"URL\",\"iiuctmdpro.000webhostapp.com/bustest/bustest.php?busno=");
  Send2Pachube(stat,des,lt,lg,sped,count);
mySerial.println(stat);
mySerial.print("&pep=");
mySerial.println(des);
mySerial.print("lat=");
mySerial.print(lt);
mySerial.print("&lon=");
mySerial.println(lg);
mySerial.print("&sped=");
mySerial.println(sped);
mySerial.print("&count=");
mySerial.println(count);
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

//gprs end

