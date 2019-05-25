#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);


//Receiver Code
String incomingByte;
String incomingByte2;
String incomingByte3;

void setup() {
  Serial.begin(9600);
 
lcd.init();
  lcd.backlight();
  lcd.home();

}

void loop()
{
if (Serial.available() > 0 ) //then chars are in the serial buffer
{
incomingByte = (char)Serial.read();
//Serial.print("You entered1: ");
//Serial.println(incomingByte);
}
if (Serial.available() > 0 )
{

incomingByte2 = (char)Serial.read();
//Serial.print("You entered2: ");
//Serial.println(incomingByte2);
// Serial.end();
}
if (Serial.available() > 0 ) //then chars are in the serial buffer
{
incomingByte3 = (char)Serial.read();
//Serial.print("You entered1: ");
//Serial.println(incomingByte);
}
delay (2000);
String bytee=" ";
bytee = (incomingByte+incomingByte2+incomingByte3);
Serial.println(bytee);


lcd.print("Passenger: ");
//delay(2000);
lcd.setCursor(2,1);
lcd.print(bytee);
delay(2000);
lcd.clear();
}

