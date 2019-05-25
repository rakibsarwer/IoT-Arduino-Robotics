#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <SoftwareSerial.h>

//SoftwareSerial mySerial()
//int val;
const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);



void setup(){

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();
  
 
}

void loop(){

if (Serial.available()> 0);
{
 int val = Serial.parseInt(); //read int or parseFloat for ..float...
lcd.clear();
if (val!=0){
Serial.println(val);
lcd.print("Passenger :");
//delay(2000);
lcd.setCursor(2,1);
lcd.print(val);
delay(2000);}
}
}
