#include "TinyGPS++.h"
#include "SoftwareSerial.h"

SoftwareSerial serial_connection(10, 11); //RX=pin 11, TX=pin 10
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>



const byte LCDcolumns = 16;
const byte LCDrows = 2;

// 0x27 is the default address. Is your address 0x3F - if so, change  to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);



// this constant won't change:
const int  Up_buttonPin   = 2;    // the pin that the pushbutton is attached to
const int  Down_buttonPin = 3;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int up_buttonState = 0;         // current state of the up button
int up_lastButtonState = 0;     // previous state of the up button
int down_buttonState = 0;         // current state of the up button
int down_lastButtonState = 0;     // previous state of the up button
bool bPress = false;
int pass,la,lo;
void setup()
{
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
pinMode( Up_buttonPin , INPUT_PULLUP);
 pinMode( Down_buttonPin , INPUT_PULLUP);
  lcd.init();
   lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Passenger Number:");
  lcd.setCursor(2,1);
  lcd.print(buttonPushCounter);

}


void loop()
{
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
    Serial.println(gps.location.lat(), 2);
  
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 2);
   
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("Passenger");
    Serial.println(buttonPushCounter);
    Serial.println("");


  
  }

  checkUp();
     checkDown();

    if( bPress){
       bPress = false;
      lcd.setCursor(2,1);
      lcd.print("               ");
      lcd.setCursor(2,1);
      lcd.print(buttonPushCounter);
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
  //    lcd.clear();
//lcd.print("Pessenger:");
//delay(2000);
//lcd.setCursor(2,1);


      Serial.println("on");
      Serial.print("number of button pushes: ");
     lcd.print(buttonPushCounter);
    buttonPushCounter;
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

void checkDown()
{
  down_buttonState = digitalRead(Down_buttonPin);

  // compare the buttonState to its previous state
  if (down_buttonState != down_lastButtonState) {
    // if the state has changed, increment the counter
    if (down_buttonState == LOW) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter--;
     
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  down_lastButtonState = down_buttonState;
}


