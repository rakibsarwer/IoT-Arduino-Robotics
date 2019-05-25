#include <Key.h>
#include <Keypad.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

char male,female,des,type,student,teacher,staff,kumira,chawkbazar,bbt;

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



byte rowPins [ROWS] = {26,28,30,32}; //pins of the keypad
byte colPins [COLS] = {34,36,38,40};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//Keypad cKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



void setup(){

  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.home();
  
 
}

void loop(){



char customKey = customKeypad.getKey();
  if (customKey){
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print(customKey);
    
    digitalWrite(led_pin,HIGH);
    Serial.println(customKey);
    delay(100);

    if (customKey =='A'){
     
     String des="kumira";
     Serial.println(des);
    }
       if (customKey =='B'){
     
     String des="bbt";
     Serial.println(des);
    }
       if (customKey =='C'){
     
     String des="chawkbazar";
     Serial.println(des);
    }
       if (customKey =='D'){
     
     String des="agrabad";
     Serial.println(des);
    }
  }
  else{ digitalWrite(led_pin,LOW);}
  }


 

