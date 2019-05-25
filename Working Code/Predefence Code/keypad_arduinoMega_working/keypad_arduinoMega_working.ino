 #include <Keypad.h>

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

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
void setup(){
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);
}
  
void loop(){
 char aKey = customKeypad.getKey();
  int bKey;
  if (aKey == 'D'){
   do {
    bKey = customKeypad.getKey();
    } while (bKey == NO_KEY);
      Serial.println("Key A is pressed");
      delay(500);
      if (bKey == 1){
      Serial.println(" 1 is pressed");
    delay(10000);
    }
  }
}
