

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);



// this constant won't change:
const int  Up_buttonPin   = 2;    // the pin that the pushbutton is attached to


// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int up_buttonState = 0;         // current state of the up button
int up_lastButtonState = 0;     // previous state of the up button
bool bPress = false;
void setup()
{
  Serial.begin(9600);
  pinMode( Up_buttonPin , INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.home();

}


void loop()
{
   checkUp();
  

   if( bPress){
       bPress = false;
    
   }
  
}

void checkUp()
{
  up_buttonState = digitalRead(Up_buttonPin);

  // compare the buttonState to its previous state
  if (up_buttonState != up_lastButtonState) {
    // if the state has changed, increment the counter
    if (up_buttonState == LOW||up_buttonState == HIGH  ) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      lcd.clear();
lcd.print("Pessenger:");
//delay(2000);
lcd.setCursor(2,1);


      Serial.println("on");
      Serial.print("number of button pushes: ");
      lcd.print(buttonPushCounter);

      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  up_lastButtonState = up_buttonState;
}



