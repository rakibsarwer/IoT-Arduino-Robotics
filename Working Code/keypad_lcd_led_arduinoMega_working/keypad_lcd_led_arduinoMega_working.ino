#include <Key.h>
#include <Keypad.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);


int key=0;
int led_pin=13;
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

Keypad eKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup(){

  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.home();
  
 
}

void loop(){

  char aKey = customKeypad.getKey();
  char bKey;
  
  if (aKey == 'B'){
    Serial.println(aKey);
    do {
    bKey = customKeypad.getKey();
    } while (bKey == NO_KEY);
      Serial.println("Key B is pressed");
      delay(500);
      if (bKey =='A'){
      Serial.println(" A is pressed");
    delay(1000);
    }
  }

}
