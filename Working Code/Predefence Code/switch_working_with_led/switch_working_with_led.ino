/* sketch 1 
turn on a LED when the button is pressed
turn it off when the button is not pressed (or released)
*/
int pinButton = 3; //the pin where we connect the button
int LED = 2; //the pin we connect the LED
int stat;
void setup() {
  Serial.begin(9600);
  pinMode(pinButton, INPUT); //set the button pin as INPUT
  pinMode(LED, OUTPUT); //set the LED pin as OUTPUT
}

void loop() {
  int stateButton = digitalRead(pinButton); //read the state of the button
  if(stateButton == 1) { //if is pressed
     digitalWrite(LED, HIGH);
     Serial.println(stateButton);
     //write 1 or HIGH to led pin
  } else { //if not pressed
     digitalWrite(LED, LOW); 
          Serial.println(stateButton);
    
    //write 0 or low to led pin
  }
  
}
