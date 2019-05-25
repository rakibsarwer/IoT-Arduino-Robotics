
// Written by Jan5412 
// DD 25-feb-18

#include <Wire.h>

#include <DS3231.h>     //  DS3231: Real-Time Clock.
DS3231 clock;
RTCDateTime dt;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address, replace 0x3F if necessary,
                                                                // Backlight is POSITIVE or NEGATIVE.

#define DAC_addr 0x62       // Set the DAC I2C address, replace 0x62 if necessary.

#define BUTTON_BackL   1    // Digital IO pen connected to the BackL button, only for testing.
#define BUTTON_Light   2    // Digital IO pen connected to the Light button, only for testing.


int BackL = 0;              // for testing backlight on and off.

int Light = 700;            // starting value of the brightness control.

int a = 5;                  // step.



void setup()  
{

  pinMode(BUTTON_BackL, INPUT_PULLUP);
  pinMode(BUTTON_Light, INPUT_PULLUP);


 
  lcd.begin(20,4); // Initialize LCD
  lcd.setCursor(1,0); // Set the cursor at the 2th column and 1st row
  lcd.print("Hello Jan5412 here");
  lcd.setCursor(2,1);  // Set the cursor at the 3th column and 2nd row
  lcd.print("Time to tinker ?");
  lcd.setCursor(4,2);  // Set the cursor at the 5st column and 3rd row
  lcd.print("Let's start");
  lcd.setCursor(7,3);  // Set the cursor at the 8th column and 4th row
  lcd.print("Yeah");

  delay (5000);

  Serial.begin(9600);

  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();

/*
  // Initialize DS3231
  // Twice once with time setting and then once without because otherwise
  // the time is continuously reset to the time of compilation

  Serial.println("Initialize DS3231");;
  clock.begin();

  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);
*/


  DAC_setting();

  delay(1000);

  lcd.clear();   // To clear the entire screen


  
}

void loop()
{


       print_LCD_Time();



//      backlight_on_off();   // For testing backlighting, switching on and off every 10 seconds.


{

   bool   newState1 = digitalRead(BUTTON_BackL);        // Get current button state BackL.
    
         if (newState1 == LOW) {
      
               lcd.setBacklight(LOW);


    }

    else {

             lcd.setBacklight(HIGH);
      
    }   

}



  
{

   bool   newState2 = digitalRead(BUTTON_Light);        // Get current button state Light.
    
         if (newState2 == LOW) {
      
            Light = Light - a;
            Serial.println(Light);  
            DAC_setting();
            delay(1000);

    }

    else {

            Light = Light + a;
            Serial.println(Light);  
            DAC_setting();
            delay(1000);
      
    }   

}


  
} //  End of void loop





void print_LCD_Time() {
  
   dt = clock.getDateTime();

//   lcd.clear();   // To clear the entire screen
  
   lcd.setCursor(0,0);          // Set the cursor
   lcd.print("        ");
   lcd.setCursor(0,0);          // Set the cursor
   lcd.print(dt.hour);
   lcd.print(":");
   lcd.print(dt.minute);
   lcd.print(":");

   lcd.print(dt.second); 

   lcd.setCursor(10,0);         // Set the cursor
   lcd.print(dt.day);
   lcd.print("-");
   lcd.print(dt.month);
   lcd.print("-");
   lcd.print(dt.year); 


   lcd.setCursor(0,3);          // Set the cursor
   lcd.print("Temp = ");
   lcd.print(clock.readTemperature());
   lcd.print(" .C");


} //  End of void print_LCD_Tim






void backlight_on_off() {  // For testing backlight, switch on and off  

    if  (BackL >= 1) {

        lcd.setBacklight(LOW);
        BackL = 0; 
        
        delay(10000);
 } 

   else {
 

       lcd.setBacklight(HIGH);
       BackL = 1;

       delay(10000);
}


} //  End of void backlight_on_off






void DAC_setting() {  // Set the output voltage 

  Wire.beginTransmission(DAC_addr);
  Wire.write (64);
  Wire.write(Light >> 4);   // MSB
  Wire.write((Light & 15) << 4); // LSB
  Wire.endTransmission();


} //  End of void DAC_setting






