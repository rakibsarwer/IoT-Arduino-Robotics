  #define INTERVAL_MESSAGE1 5000
  
   
  unsigned long time_1 = 0;
  
  
  
  const int trigPin1 = 10;
  const int echoPin1 = 9;
  const int trigPin2 = 12;
  const int echoPin2 = 11;
  const int trigPin3 = 7;
  const int echoPin3 = 6;
   const int trigPin4 = 5;
  const int echoPin4 = 4;
  
  int count;
  // defines variables
  long duration,valA1,valA2,valA3,valA4;
  int distance;
  long duration1,duration2,duration3;
  int distance1,distance2,distance3;
  
void setup(){
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin4, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin4, INPUT); // Sets the echoPin as an Input
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
  digitalWrite(trigPin4, LOW);
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

   digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration3 = pulseIn(echoPin4, HIGH);
  delayMicroseconds(2);
  
  distance1= duration1*0.034/2;
  distance= duration*0.034/2;
  distance2= duration2*0.034/2;
    distance3= duration3*0.034/2;
  
  valA1=distance;
   valA2=distance1;
   valA3=distance2;
     valA4=distance3;
//   
//  Serial.println("Strat");
//  Serial.println(valA1);
//  
//  Serial.println(valA2);
//  
//  Serial.println(valA3);
//  
//  Serial.println(valA4);
//  
//  Serial.println("end");

   if(millis() > time_1 + INTERVAL_MESSAGE1){
          time_1 = millis();
          //print_time(time_1);
          
          Serial.print(count);
      }
  switch(signalState)
  {
    case ST_GREEN:
    signalgreen(valA1, valA2, valA3, valA4);
    break;
    case ST_RED1:
    signalred1(valA1, valA2, valA3, valA4);
    break;
    case ST_RED2:
    signalred2(valA1, valA2, valA3, valA4);
    break;
    case ST_YELLOW:
    signalyellow(valA1, valA2, valA3, valA4, count);
    break;
  } 
  }
  
  void signalgreen(int valA1, int valA2, int valA3, int valA4){
  
    if ((valA1<50 || valA2<50) && (valA3>50 || valA4>50))
    {
      signalState=ST_RED1;
    }
    
    else if ((valA1>50 || valA2>50) && (valA3<50 || valA4<50))
    {
      signalState=ST_RED2;
    }
    
  }
  
  void signalred1(int valA1, int valA2, int valA3, int valA4)
  {
               // tell servo to go to position in variable 'pos'
     if ((valA1>50 || valA2>50) && (valA3<50 || valA4<50))
     {
      count++;
   
      signalState=ST_YELLOW;
     } 
  }
  
  void signalred2(int valA1, int valA2, int valA3, int valA4){
     if ((valA1<50 || valA2<50) && (valA3>50 || valA4>50)){
       count--;
  
      signalState=ST_YELLOW;
    }
  }
  
  void signalyellow(int valA1, int valA2, int valA3, int valA4, int count)
  {
    
    signalState=ST_GREEN; 
  
  }
    
  
  
  
  
  
  
  

