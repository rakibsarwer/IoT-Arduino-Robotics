
int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

int r = 13;
int g = 12;
int b = 11;



void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  
   float mv = ( sensorValue/1024.0)*5000;
   float temp = mv/10;


Serial.print("TEMPRATURE = ");
Serial.print(temp);
Serial.print("*C");
Serial.println();

  delay(500);
  
  if(temp>0 && temp<50)
  {
    digitalWrite(r,0);
    digitalWrite(g,1);
    digitalWrite(b,0);
  }
  
    if(temp>50 && temp<80)
  {
    digitalWrite(r,0);
    digitalWrite(g,0);
    digitalWrite(b,1);
  }
  
      if(temp>80 )
  {
    digitalWrite(r,1);
    digitalWrite(g,0);
    digitalWrite(b,0);
  }
 
 
  
}

