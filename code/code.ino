int relay1=2;
int relay2=3;
int relay3=4;
int relay4=5;
int echo_front=6;
int trig_front=7;
int echo_left=8;
int trig_left=9;
int echo_right=10;
int trig_right=11;

long time_front,distance_front,minimum_front,distance_left,minimum_left,time_left,distance_right,minimum_right,time_right;
  
void setup()
{
  Serial.begin(9600);
  pinMode(trig_front,OUTPUT);
  pinMode(echo_front,INPUT);
  pinMode(trig_left,OUTPUT);
  pinMode(echo_left,INPUT);
  pinMode(trig_right,OUTPUT);
  pinMode(echo_right,INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
}

void loop() 
{
      
    sensor_front();
    sensor_left();
    sensor_right();
    forward_robot();
    Serial.println("Robot Forward");
    
    
    if(distance_front<=minimum_front)
    {
      tern_left();
      
    }
    if(distance_front<=minimum_front && distance_left<=minimum_left)
    {
       tern_right();
    
    }
    if(distance_front<=minimum_front && distance_right<=minimum_right)
    {
      tern_left();
    }
    if(distance_front<=minimum_front && distance_left<=minimum_left && distance_right<=minimum_right)
    {
      stop_robot();
    }
    delay(50);
}

void sensor_front()
{
digitalWrite(trig_front, LOW); 
delayMicroseconds(2);
digitalWrite(trig_front, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_front, LOW);
 
time_front=pulseIn(echo_front,HIGH);
distance_front=time_front/58.2;
minimum_front=20;  
}

void sensor_left()
{
digitalWrite(trig_left, LOW); 
delayMicroseconds(2);
digitalWrite(trig_left, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_left, LOW);
 
time_left=pulseIn(echo_left,HIGH);
distance_left=time_left/58.2;
minimum_left=20;    
}

void sensor_right()
{
digitalWrite(trig_right, LOW); 
delayMicroseconds(2);
digitalWrite(trig_right, HIGH); 
delayMicroseconds(20);
digitalWrite(trig_right, LOW);
 
time_right=pulseIn(echo_right,HIGH);
distance_right=time_right/58.2;
minimum_right=20; 
}

void forward_robot()
{
 digitalWrite(relay1,HIGH); 
 digitalWrite(relay2,LOW);
 digitalWrite(relay3,LOW);
 digitalWrite(relay4,HIGH);

}

void stop_robot()
{
 digitalWrite(relay1,LOW); 
 digitalWrite(relay2,LOW);
 digitalWrite(relay3,LOW);
 digitalWrite(relay4,LOW);
 
}

void tern_left()
{
 digitalWrite(relay1,LOW); 
 digitalWrite(relay2,HIGH);
 digitalWrite(relay3,LOW);
 digitalWrite(relay4,HIGH);
 
}

void tern_right()
{
 digitalWrite(relay1,HIGH); 
 digitalWrite(relay2,LOW);
 digitalWrite(relay3,HIGH);
 digitalWrite(relay4,LOW);
 
}

