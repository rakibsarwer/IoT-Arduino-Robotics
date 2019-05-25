  #include "TinyGPS++.h"
  #include "SoftwareSerial.h"
  
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  
  #include <Key.h>
  #include <Keypad.h>
  
  #include <SoftwareSerial.h>
  #include <String.h>
  #define INTERVAL_MESSAGE1 1000
//
//   
  unsigned long time_1 = 0;
//  
  
  double lt,lg,sped;
  SoftwareSerial serial_connection(50, 49); //( TX=pin 10,RX=pin 11)
  TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
  SoftwareSerial mySerial(7, 6);

//passenger start 
  int count;
//passenger end 

//lcd start
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
  int pinButton = 13; //the pin where we connect the button
 //the pin we connect the LED
  int stat;
//Rocker Switch End

//bus info start
  String no="11-0157";
//bus info end

void setup()
  {
//gps start
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
//gps end

//lcd start
  lcd.init();
  lcd.backlight();
  lcd.home();
//lcd end

//gprs start
   mySerial.begin(9600);
//gprs end 

//rocker switch start
    pinMode(pinButton, INPUT); //set the button pin as INPUT
//rocker switch end
}

void locate()
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
    Serial.println(gps.location.lat(), 6);
    lt=gps.location.lat();
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    lg=gps.location.lng();
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    sped=gps.speed.mph();
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
   }
//gps end
 void pass()
 {
  //passenger serial start
 if(Serial.available()>0)
 {
  count =Serial.parseInt();
  Serial.println(count);
 }
  //passenger Serial end
 }
  
void loop()
  {

  
     
        
   
  pass();
  locate();
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
  locate();
//Rocker Switch start
  int stateButton = digitalRead(pinButton); //read the state of the button
  if(stateButton == 1) { //if is pressed
     digitalWrite(led_pin, HIGH);
       stat=1;
      Serial.println(stat);
     //write 1 or HIGH to led pin
  } else { //if not pressed
     digitalWrite(led_pin, LOW); 
      stat=0;
     Serial.println(stat);
    //write 0 or low to led pin
  }
//Rocker Switch end here
  locate();



//gprs start
  String latL=String(lt,6);
  String lngL=String(lg,6);
  String speedL=String(sped,3);
  String pas=String(count);
  String st=String(stat);
  locate();
  Serial.print("Passenger :");
  Serial.println(pas);
  Serial.print("lat: ");
  Serial.println(latL);
  Serial.print("lng: ");
  Serial.println(lngL);
  Serial.print("spd: ");
  Serial.println(speedL);
  Serial.print("stat: ");
  Serial.println(st);
  Serial.print("Bus no:");
  Serial.println(no);
  Serial.print("Dest:");
  Serial.println(des);
  locate();


  //lcd start
lcd.setCursor(0,0);
lcd.print("pas");
lcd.setCursor(0,1);
lcd.print(pas);

lcd.setCursor(4,0);
lcd.print("st");
lcd.setCursor(4,1);
lcd.print(st);

lcd.setCursor(7,0);
lcd.print("des");
lcd.setCursor(7,1);
lcd.print(des);

lcd.setCursor(13,0);
lcd.print("GPS");
lcd.setCursor(13,1);
lcd.print("OKK");


//lcd end
locate();
// if(millis() > time_1 + INTERVAL_MESSAGE1){
//       time_1 = millis();

  Send2Pachube(latL,lngL,speedL,pas,des,st,no);
// }
}
//gprs start 
  
void Send2Pachube(String latL, String lngL, String speedL, String pas, String des, String st, String no) 
{
 mySerial.println("AT+CSQ"); // Signal quality check
  ShowSerialData();
 
  mySerial.println("AT+CGATT?"); //Check if gets attached to registered network
  ShowSerialData();
  mySerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  ShowSerialData();
  mySerial.println("AT+SAPBR=3,1,\"APN\",\"INTERNET\"");//setting the APN, Access point name string
  ShowSerialData();
  mySerial.println("AT+SAPBR=1,1");//setting the SAPBR
  ShowSerialData();
  mySerial.println("AT+HTTPINIT"); //init the HTTP request

  ShowSerialData();
  mySerial.print("AT+HTTPPARA=\"URL\",\"iiuctmdtest.000webhostapp.com/bustest/bustest.php?lat="+latL+"&lng="+lngL+"&speed="+speedL+"&pass="+pas+"&des="+des+"&stat="+st+"&no="+no);

  mySerial.println("\"");

// setting the httppara, the second parameter is the website you want to access
  delay(10);
  ShowSerialData();
  mySerial.println("AT+HTTPACTION=0");//submit the request 
  delay(100);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
 
  ShowSerialData();
  mySerial.println("AT+HTTPREAD");// read the data from the website you access
  delay(30);

  ShowSerialData();
  mySerial.println("");
  delay(10);

}

void ShowSerialData() //Show serial data
{
    while(mySerial.available()!=0)
    Serial.write(mySerial.read());
    Serial.println();
}
