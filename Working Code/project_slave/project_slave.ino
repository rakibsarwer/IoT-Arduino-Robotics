#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int x;
const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);


void setup(){
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.home();
  }



void loop(){
   delay(100); 
   lcd.print("Alarm ON(F,G)");
//delay(2000);
lcd.setCursor(2,1);
lcd.print(x);
delay(2000);
lcd.clear();
}

void receiveEvent(int howMany)
{
    while(1<Wire.available())
    {
      char c = Wire.read();
      Serial.print(c);
    }
     x = Wire.read();
    Serial.println(x);
}

