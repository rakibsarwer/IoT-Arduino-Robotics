#define INTERVAL_MESSAGE1 5000

 
unsigned long time_1 = 0;


//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
// defines pins numbers
const int trigPin1 = 10;
const int echoPin1 = 9;
const int trigPin2 = 12;
const int echoPin2 = 11;
const int trigPin3 = 7;
const int echoPin3 = 6;
//const byte LCDcolumns = 16;
//const byte LCDrows = 2;
//LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);
int count;
// defines variables
long duration,valA1,valA2,valA3;
int distance;
long duration1,duration2;
int distance1,distance2;
    void setup(){
//      lcd.init();
//  lcd.backlight();
//  lcd.home();

pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

}
enum SIGNALSTATES
{
  ST_GREEN,
  ST_RED1,
  ST_RED2,
  ST_YELLOW,
};
SIGNALSTATES signalState=ST_GREEN;
void loop() {
// Clears the trigPin
digitalWrite(trigPin1, LOW);
digitalWrite(trigPin2, LOW);
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Clears the trigPin
duration = pulseIn(echoPin1, HIGH);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration1 = pulseIn(echoPin2, HIGH);
delayMicroseconds(2);

digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration2 = pulseIn(echoPin3, HIGH);
delayMicroseconds(2);
// Reads the echoPin, returns the sound wave travel time in microseconds
// Calculating the distance
////distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
// Calculating the distance
//distance1= duration1*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(duration);
//Serial.print("Distance2: ");
//Serial.println(duration1);
//delay(5000);
valA1=duration;
 valA2=duration1;
 valA3=duration2;
//Serial.println("Strat");
//Serial.println(valA1);
//
//Serial.println(valA2);
//
//Serial.println(valA3);
//
//Serial.println("end");
//
//Serial.println(".....................");
//Serial.println("Passenger : ");
 if(millis() > time_1 + INTERVAL_MESSAGE1){
        time_1 = millis();
        //print_time(time_1);
        
        Serial.print(count);
    }
//Serial.println(".....................");
//delay(200);
switch(signalState)
{
  case ST_GREEN:
  signalgreen(valA1, valA2, valA3);
  break;
  case ST_RED1:
  signalred1(valA1, valA2, valA3);
  break;
  case ST_RED2:
  signalred2(valA1, valA2, valA3);
  break;
  case ST_YELLOW:
  signalyellow(valA1, valA2, valA3);
  break;
} 
}

void signalgreen(int valA1, int valA2, int valA3){

  if (valA1<4000&& valA2>4000)
  {
    signalState=ST_RED1;
  }
  
  else if (valA2>4000 && valA3<4000)
  {
    signalState=ST_RED2;
  }
  
}

void signalred1(int valA1, int valA2, int valA3)
{
             // tell servo to go to position in variable 'pos'
   if (valA1>4000&& valA2<4000)
   {
    count++;
    //Serial.print(count);
    signalState=ST_YELLOW;
   } 
}

void signalred2(int valA1, int valA2, int valA3){
   if (valA2<4000 && valA3>4000){
     count--;
//Serial.print(count);
    signalState=ST_YELLOW;
  }
}

void signalyellow(int valA1, int valA2, int valA3)
{
           // tell servo to go to position in variable 'pos'
//  if (valA1>4000 || valA2>4000 || valA3>4000)
//  {
   
//      lcd.clear();
////      Serial.println(count);
//      lcd.print("Passenger:");
//      lcd.setCursor(2,1);
//      lcd.print(count);
//delay(500);
  signalState=ST_GREEN; 
//  } 
}
  








