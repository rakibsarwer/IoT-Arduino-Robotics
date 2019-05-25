#include <Keypad.h>  
  
  
/** 
  Globals  
**/  
const byte ROWS = 4; // Four rows  
const byte COLS = 4; // Four columns  
  
  
// Define the Keymap  
char keys[ROWS][COLS] = {  
  {'1', '2', '3', '4'}, /*  S1   S2 S3   S4  */  
  {'5', '6', '7', '8'}, /*  S5   S6   S7   S8  */  
  {'A', 'C', 'E', 'G'}, /*  F1U   F2U   ON   NC  */  
  {'B', 'D', 'F', 'H'} /*  F1D   F2D   OFF   NC  */  
};  
  
  
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.  
byte rowPins[ROWS] = { 5, 4, 3, 2 };  
// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins.  
byte colPins[COLS] = { 9, 8, 7, 6 };   
  
  
// Create the Keypad  
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );  
  
  
byte ledPin = 13;  
boolean blink = false;  
boolean keyPressed = false;  
byte pressedKey = ' ';  
int keypadDelayCounter = 0;  
  
  
/** 
  Setup 
**/  
void setup() {  
  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output  
  digitalWrite(ledPin, HIGH);   // sets the LED on  
  
  /* Keypad event listener - Interrupt */  
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad  
}  
  
  
  
  
/** 
  Loop 
**/  
void loop() {  
  
  
  // Check for keypad  
  keypad.getKey();  
  
  
  
  
  // If key is pressed (HOLD state)  
  if ( keyPressed ) {  
  // Serial.println("KEYPRESSED");  
  // Serial.println(pressedKey);  
  // Serial.println(keypadDelayCounter);  
  switch (pressedKey) {  
  /* FAN 1 */  
  case 'A':  
  keypadDelayCounter++;  
  break;  
  
  
  case 'B':  
  keypadDelayCounter++;  
  break;  
  
  
  /* FAN 2 */  
  case 'C':  
  keypadDelayCounter++;  
  break;  
  
  
  case 'D':  
  keypadDelayCounter++;  
  break;  
  
  
  default:  
  // Key held pressed other than Dimmers  
  keypadDelayCounter = 0;  
  break;  
  }  
  
  
  // Main keypad hold delay adjustment  
  if ( keypadDelayCounter > 15000 ) {  
  Serial.println("INCREMENT/DECREMENT");  
  keypadDelayCounter = 0;  
  }  
  }  
  
  
  
  //digitalWrite(ledPin,!digitalRead(ledPin));  
  //delay(100);  
}  
  
  
  
  
//take care of some special events  
void keypadEvent( KeypadEvent key ){  
  switch ( keypad.getState() ) {  
  case PRESSED:  
  break;  
  
  
  case RELEASED:  
  // Reset keypad delay and set keypressed to false  
  keyPressed = false;  
  keypadDelayCounter = 0;  
  switch (key) {  
  // TOGGLES  
  case '1':  
  case '2':  
  case '3':  
  case '4':  
  case '5':  
  case '6':  
  case '7':  
  case '8':  
  Serial.print("SWITCH: ");  
  Serial.println(key);  
  //toggleSwitch(key);  
  break;  
  
  
  // FAN 1  
  case 'A':  
  Serial.println("FAN 1 UP");  
  break;  
  
  
  case 'B':  
  Serial.println("FAN 1 DOWN");  
  break;  
  
  
  
  
  // FAN 2  
  case 'C':  
  Serial.println("FAN 2 UP");  
  break;  
  
  
  case 'D':  
  Serial.println("FAN 2 DOWN");  
  break;  
  
  
  
  
  // MASTER CONTROLLS  
  case 'E':  
  Serial.println("ALL ON");  
  break;  
  
  
  case 'F':  
  Serial.println("ALL OFF");  
  break;  
  
  
  
  
  default:  
  Serial.print("UNMAPPED: ");  
  Serial.println(key);  
  break;  
  }  
  break;  
  
  
  case HOLD:  
  keyPressed = true;  
  pressedKey = key;  
  break;  
  
  
  case IDLE:  
  break;  
  }  
}  
  
  
  
  
void toggleSwitch( char num ) {  
  Serial.println(num);  
}  
