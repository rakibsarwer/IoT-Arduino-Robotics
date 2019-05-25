#include <SoftwareSerial.h>
//For connecting with wemos uncomment the For Wemos lines, comment the For Arduino lines
//SoftwareSerial gsm(D7, D8, false, 256); // Rx, Tx //For Wemos
SoftwareSerial gsm(7, 8); //Rx, Tx //For Arduino

String sms, cellno = "+8800000000000"; // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS


char RcvdMsg[200] = " ", MsgMob[15], MsgTxt[200]=" ";
int RcvdCheck = 0, RcvdConf = 0, aindex = 0, RcvdEnd = 0, MsgLength = 0;
boolean flag=false;

void setup(){
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
}

void loop(){
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
