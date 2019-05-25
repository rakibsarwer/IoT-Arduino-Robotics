// defines pins numbers
const int trigPin1 = 10;
const int echoPin1 = 9;
const int trigPin2 = 12;
const int echoPin2 = 11;
// defines variables
long duration,valA1,valA2;
int distance;
long duration1;
int distance1;
int count=0;
int flag=0;

void setup() {
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
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



switch(signalState)
{
  case ST_GREEN:
  signalgreen(valA1, valA2);
  break;
  case ST_RED1:
  signalred1(valA1, valA2);
  break;
  case ST_RED2:
  signalred2(valA1, valA2);
  break;
  case ST_YELLOW:
  signalyellow(valA1, valA2);
  break;
} 
}

void signalgreen(int valA1, int valA2){


  if (valA1<500 && valA2>500){
  
    signalState=ST_RED1;
  }
  else if (valA1>500 && valA2<500){
    
    signalState=ST_RED2;
  }
  
}

void signalred1(int valA1, int valA2){
 
             // tell servo to go to position in variable 'pos'
   
     
  if (valA1>500 && valA2<500){
    count++;
  
    //Serial.print(count);

    signalState=ST_YELLOW;
  }
}

void signalred2(int valA1, int valA2){
 
 
  if (valA1<500 && valA2>500){
  count--;
 
//Serial.print(count);
    signalState=ST_YELLOW;
  }
 
}

void signalyellow(int valA1, int valA2){
           // tell servo to go to position in variable 'pos'

  if (valA1>500 && valA2>500){
    
     
Serial.println(count);
Serial.println(valA1);
Serial.println(valA2);
 
    signalState=ST_GREEN;
    
  } 
}
  








