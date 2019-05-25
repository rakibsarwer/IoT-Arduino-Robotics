#include <SoftwareSerial.h>
#include<ThingSpeak.h>

#define triggerPin 8
#define echoPin 12
#define LEDpin 6
SoftwareSerial gsm(6, 7); //Rx, Tx //For Arduino
// Network information
const char* ssid = "ssid";
const char* password = "xxxxxxxxxx";
//
// thingSpeak information
char* writeAPIKey = "XXXXXXXXXXXXXXXX";
char* readAPIKey = "YYYYYYYYYYYYYYYY"; 
const long channelID = 000000; 
const unsigned int firstReadFieldNumber = 2;
const unsigned int secondReadFieldNumber = 3; 
const unsigned int switchField = 4; // Field number (1-8) to use to change status of device.  Determines if data is read from ThingSpeak.

// Other constants
const unsigned long postingInterval = 60L * 1000L;   // Post data every 60 seconds

// Global variables
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0;
float distanceThreshold = 0;
bool getInfo = 1;  // Set this to zero if you don't want to read data from ThingSpeak anymore (i.e. calibration complete)
int points = 7; 
   

void setup() {
  /*gsm sart */
   //Serial.begin(115200); //For Wemos
  //gsm.begin(115200); //For Wemos
  Serial.begin(9600); //For Arduino
  gsm.begin(9600); //For Arduino
  delay(1000);
  Serial.println("Checking & Preparing GSM Module for AT Commands");
  gsm.println("AT");
  ShowSerialData();
  gsm.println("AT+CSQ");  //Signal Quality Report
  ShowSerialData();
  gsm.println("AT+CREG?");  //Attach or Detach  from Gprs Service
  ShowSerialData();
  Serial.println("******************* \nCommand Characters \ns for sending sms \nr for receiving sms \nc for calling \n*******************");
  /*gsm end */
  
  Serial.begin (9600); 
  pinMode(triggerPin, OUTPUT); 
  pinMode(LEDpin, OUTPUT);
  pinMode(echoPin, INPUT);
  connectWifi();
  Serial.println("Start");

  // Get the initial parameters from ThingSpeak.
  distanceThreshold = readTSData(channelID,firstReadFieldNumber,readAPIKey); 
  points = readTSData(channelID,secondReadFieldNumber,readAPIKey);   
}

void loop() {
  /*gsm srt*/
 Serial.println("Enter a command character:");
  while(!Serial.available()){
    //Do Nothing
  }
  if (Serial.available()){
    switch(Serial.read()){
      case 's':
        SendMessage();
        break;
      case 'r':
        ReceiveMessage();
        break;
      case 'c':
        GiveCall();
        break;
      default:
        Serial.println("Invalid Input");
    }
  }
    delay(1000);
    /*gsm end*/
  
  
  float  distance=0;

  // Make sure there is an internet connection.
  if(WiFi.status() != WL_CONNECTED){
    
    connectWifi();  
    }

     for (uint16_t loops = 0; loops < points; loops++){
      distance += getDistance(triggerPin,echoPin);  //make a measurement, store the sum of all measurements
      delay(5);  
     }
     
     distance = distance/points;
     
    if (distance < distanceThreshold){
      digitalWrite(LEDpin,HIGH);
      }
    
     else{
      
      digitalWrite(LEDpin,LOW); 
      }
      
     
     Serial.println("Ave: "+ String(distance)+ " cm");
      
    if (millis() - lastUpdateTime >=  postingInterval) {  
      
      lastUpdateTime = millis();
      
           if (!(getInfo==0)){
            
            distanceThreshold = readTSData(channelID,firstReadFieldNumber,readAPIKey);
            points = readTSData(channelID,secondReadFieldNumber,readAPIKey);
            getInfo = (bool)readTSData(channelID,switchField,readAPIKey);
            }
            
       if (distance < distanceThreshold){
        
      // Write data to ThingSpeak channel.
       writeTSData(channelID, 1, distance, writeAPIKey);
       }
       
      }
      
    delay(500);    // Provide some delay between measurements.
    
}

int writeTSData(long TSChannel,unsigned int TSField,float data,char* ReadAPIKey){
  int  writeSuccess = ThingSpeak.writeField(TSChannel, TSField, data, writeAPIKey); //write the data to the channel
  return writeSuccess;
}

// Use this function if you want multiple fields simultaneously.
/*
int writeTDData(long TSChannel,unsigned int TSField1,float data1,unsigned int TSField2,data2,char* ReadAPIKey){
  ThingSpeak.setField(TSField1,data1);
  ThingSpeak.setField(TSField1,data2);
   
  writeSuccess = ThingSpeak.writeFields(TSChannel, writeAPIKey);
  return writeSuccess;
}
*/

float readTSData(long TSChannel,unsigned int TSField,char* ReadAPIKey){
  
  float data = 0;
  
  data = ThingSpeak.readFloatField(TSChannel,TSField,ReadAPIKey);
  Serial.println(" Data read from ThingSpeak "+String(data));
  return data;
}

float getDistance(int tPin,int ePin){
  
  long duration, distance;
    
  digitalWrite(tPin, LOW);  // Reset the trigger pin.
  delayMicroseconds(2); 
  digitalWrite(tPin, HIGH);  // Start a measurement.
  delayMicroseconds(10); // 
  digitalWrite(tPin, LOW);   // Complete the pulse.
  duration = pulseIn(ePin, HIGH);  // Wait for a reflection pulse.
  distance = (duration/2) / 29.1;     // Calculate the appropriate distance using the estimated speed of sound.

  // This section is useful when debugging the sensor.
/*
  if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
   Serial.print(distance);
   Serial.println(" cm");
  }
  */
  return distance;
}

int connectWifi(){
     
    while (WiFi.status() != WL_CONNECTED) {
       WiFi.begin(ssid, password);
       delay(2500);
       Serial.println("Connecting to WiFi");
    }
    
    Serial.println("Connected");
    ThingSpeak.begin(client);
  }
  void SendMessage(){
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  ShowSerialData();  
  gsm.print("AT+CMGS=\"");
  gsm.print(cellno);
  gsm.println("\"\r");
  ShowSerialData();
  Serial.println("Enter the text to be sent:");
  while(!Serial.available()){
    //Do Nothing
  }
  if (Serial.available()){
  sms = Serial.readString();
  }
  gsm.println(sms);// The SMS text you want to send
  delay(100);
  gsm.println((char)26);// ASCII code of CTRL+Z
  ShowSerialData();
  gsm.println("AT+CMGF=0");    //Sets the GSM Module in PDU Mode
  ShowSerialData();  
  Serial.println("SMS sent");
}

void ReceiveMessage(){
  Serial.println("Preparing to receive an SMS....");
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  ShowSerialData(); 
  gsm.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  ShowSerialData();
  Serial.println("Waiting to receive an SMS....");
  while(!gsm.available()){
    //Do Nothing
  }
  if(gsm.available()){
    //ReceSMS();
   ShowSerialData();
   Serial.println();
   Serial.println("Message Received Successfully");
  }
  gsm.println("AT+CMGF=0\"n\"r");    //Sets the GSM Module in PDU Mode
  //gsm.println("AT+CMGL=\"ALL\"");
  ShowSerialData();
}

void GiveCall() {
  Serial.println("Preparing to Call...");
  gsm.print("ATD");
  gsm.print(cellno);
  gsm.println(";");
  ShowSerialData();
  Serial.print("Calling ");
  Serial.println(cellno);
  delay(20000); //Hang up after 20 seconds
  // AT command to hang up
  gsm.println("ATH"); // hang up
  ShowSerialData();
  Serial.println("Hunged UP!!!");
  
}

void ReceSMS(){
  //boolean flag=false;
  if(gsm.available()){
    char data = gsm.read();
    if(data == '+'){
      RcvdCheck = 1;
    }
    if((data == 'C') && (RcvdCheck == 1)){
      RcvdCheck = 2;
    }
    if((data == 'M') && (RcvdCheck == 2)){
      RcvdCheck = 3;
    }
    if((data == 'T') && (RcvdCheck == 3)){
      RcvdCheck = 4;
    }
    if(RcvdCheck == 4){
      aindex = 0; 
      RcvdConf = 1; 
      RcvdCheck = 0;
      flag=true;
    }
    if(RcvdConf == 1){
      if(data == '\n'){
        RcvdEnd++;
      }
      if(RcvdEnd == 3){
      RcvdEnd = 0;
      }
      RcvdMsg[aindex] = data;
      aindex++;
      if(RcvdEnd == 2){
        RcvdConf = 0;
        MsgLength = aindex-2;
      }
      if(RcvdConf == 0){
        Serial.print("Mobile Number is: ");
        for(int x = 4;x <17;x++){
          MsgMob[x-4] = RcvdMsg[x];
          Serial.print(MsgMob[x-4]);
        }
        Serial.println();
        Serial.print("Message Text: ");
        for(int x = 46;x <MsgLength;x++){
          MsgTxt[x-46] = RcvdMsg[x];
        }
        for (int i=0;i<200;i++){
          Serial.print(MsgTxt[i]);
        }
        Serial.println();
      }
    }
  }
  //return flag;
}

void ShowSerialData(){ //Show serial data
  delay(1000);
  while(gsm.available()!=0)
    Serial.write(gsm.read());
    //Serial.println();
}
