#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



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


lcd.print("Alarm ON(F,G)");
//delay(2000);
lcd.setCursor(2,1);
lcd.print("Earthquake ON");
delay(2000);
lcd.clear();
}
