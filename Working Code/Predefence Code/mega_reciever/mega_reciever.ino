#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

int c[10]; //Initialized variable to store recieved data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.home();
}

void loop() {
  int x = Serial.read(); //Read the serial data and store in var
  Serial.println(x); //Print data on Serial Monitor
  
  lcd.print("passenger:");
//delay(2000);
lcd.setCursor(2,1);
lcd.print(x);
delay(2000);
lcd.clear();
  delay(1000);
}
