

#include <NewPing.h>

int us1Pin = 2;
int us2Pin = 4;
int relayPin = 10;

#define MAX_DISTANCE 150



class USSensor {
public:
  USSensor(int trigPin, int echoPin, String aName) {
    trig = trigPin;
    echo = echoPin;
    sonar = new NewPing(trigPin, echoPin, MAX_DISTANCE);
    isActivated = false;
    name = aName;
    time = 0;
  }
  
  void update() {
    updateSensor();
    if (value < 100) {
      setActive(true);
    } else {
      if (millis() - time > 500) {
        setActive(false);
      } 
    }
  }
  
  void reset() {
    setActive(false);
    time = 0;
  }
  
  void setActive(boolean state) {
    if (!isActivated && state) {
      time = millis();
    }
    if (isActivated != state) {
      isActivated = state;
      Serial.print(name + ": ");
      Serial.println(state);
    }
  }
  
  boolean wasActive() {
    return (time != 0) && !isActivated;
  }
  
  int lastActive() {
    return millis() - time;
  }
  
private:
  int trig;
  int echo;
  int led;
  String name;
  boolean isActivated;
  unsigned long time;
  float value;
  NewPing *sonar;
  
  void updateSensor() {
    
    delay(25);
    unsigned int uS = sonar->ping();
    value = uS / US_ROUNDTRIP_CM;
    
    delay(5);
    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
    delayMicroseconds(50);
    digitalWrite(trig, HIGH);
    delayMicroseconds(200);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    int pulseLen = pulseIn(echo, HIGH);
    float currentValue = pulseLen / 29.387 /2; // [voloshyn] convert into cm
    if (value == 0.0f) value = currentValue;
    else value = (value + currentValue) / 2;
   value = pulseLen / 29.387 /2; // [voloshyn] convert into cm
  }
};

int peopleInRoom = 0;
USSensor *A;
USSensor *B;

void setup() {
  Serial.begin(9600);
  A = new USSensor(us1Pin, us1Pin, "A");
  B = new USSensor(us2Pin, us2Pin, "B");
  pinMode(relayPin, OUTPUT);
}

void loop() {
  
    A->update();
    B->update();
    
    if (A->wasActive() && B->wasActive()) {
      int a_time = A->lastActive();
      int b_time = B->lastActive();
      if (a_time < 5000 && b_time < 5000) {
        if (a_time > b_time) {
          peopleInRoom++;
        } else {
          peopleInRoom--;
        }
        Serial.print("People in room: ");
        Serial.println(peopleInRoom);
      }
      A->reset();
      B->reset();
    }

    if (peopleInRoom < 0) { // [voloshyn] in case when someone was already in the room when system was activated
      peopleInRoom = 0;
    }
    
    if (peopleInRoom > 0) {
      digitalWrite(relayPin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
    }
}


