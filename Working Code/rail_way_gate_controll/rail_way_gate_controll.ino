#include <Servo.h>
int sensePin1=A0;
int sensePin2=A1;
int RED=6;
int YELLOW=5;
int GREEN=3;
int POWER=8;
int buzzer = 9;
Servo myservo;
int pos = 0;

void setup() {
Serial.begin(9600);
pinMode(RED,OUTPUT);
pinMode(YELLOW,OUTPUT);
pinMode(GREEN,OUTPUT);
pinMode(POWER,OUTPUT);
 myservo.attach(7); 
pinMode(buzzer,OUTPUT);
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

long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;

   
  delay(2000);
  
long valA1=duration1;
long valA2=duration2;
Serial.println(valA1);
Serial.println(valA2);
delay(200);

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
  digitalWrite(GREEN,LOW);
  digitalWrite(RED,HIGH);
  digitalWrite(YELLOW,HIGH);
  digitalWrite(POWER,HIGH);
  pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 

  if (valA1<10 && valA2>10){
    digitalWrite(buzzer,HIGH);
    digitalWrite(RED,LOW);
    delay(8000);
    digitalWrite(buzzer,LOW);
    signalState=ST_RED1;
  }
  else if (valA1>10 && valA2<10){
   digitalWrite(buzzer,HIGH);
   digitalWrite(RED,LOW);
    delay(8000);
    digitalWrite(buzzer,LOW);
    signalState=ST_RED2;
  }
}

void signalred1(int valA1, int valA2){
 
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(YELLOW,HIGH);
  digitalWrite(POWER,HIGH);
   pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 

  if (valA1>10 && valA2<10){
    signalState=ST_YELLOW;
  }
}

void signalred2(int valA1, int valA2){
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(YELLOW,HIGH);
  digitalWrite(POWER,HIGH);
   pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 

  if (valA1<10 && valA2>10){
    signalState=ST_YELLOW;
  }
 
}

void signalyellow(int valA1, int valA2){
  digitalWrite(GREEN,HIGH);
  digitalWrite(RED,HIGH);
  digitalWrite(YELLOW,LOW);
  digitalWrite(POWER,HIGH);
  delay(500);
   pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  

  if (valA1>10 && valA2>10){
    signalState=ST_GREEN;
  }
}
  


