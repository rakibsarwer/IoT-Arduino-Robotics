
//#include <RFID.h>
#include <SPI.h>
#include "Adafruit_FONA.h"

#include <SoftwareSerial.h>

/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */


/* Create an instance of the RFID library */

int reader=0;
String x[3]={};

//For connecting with wemos uncomment the For Wemos lines, comment the For Arduino lines
//SoftwareSerial gsm(D7, D8, false, 256); // Rx, Tx //For Wemos

SoftwareSerial gsm(6, 7); //Rx, Tx //For Arduino
Adafruit_FONA SIM800(8); 

String sms, cellno = "+8801840077780"; // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
int net_status;

char RcvdMsg[200] = " ", MsgMob[15], MsgTxt[200]=" ";
int RcvdCheck = 0, RcvdConf = 0, aindex = 0, RcvdEnd = 0, MsgLength = 0;
boolean flag=false;
boolean gprs_on = false;
boolean tcp_on = false;


void setup()
{ 
  Serial.begin(9600);

  /* Enable the SPI interface */
  //SPI.begin(); 
  /* Initialise the RFID reader */
  //RC522.init();
  
  //Serial.begin(115200); //For Wemos
  //gsm.begin(115200); //For Wemos

  Serial.println("Bus  Data to ThingSpeak");
  Serial.println("Initializing SIM800....");
  
  gsm.begin(9600); //For Arduino
  
  if (! SIM800.begin(gsm)) {            
    Serial.println("Couldn't find SIM800 ");
    while (1);
  }
  
  Serial.println("SIM800 is OK"); 
  delay(1000);
 
  Serial.println("Waiting to be registered to network...");
  net_status = SIM800.getNetworkStatus();
  while(net_status != 1){
     net_status = SIM800.getNetworkStatus();
     delay(2000);
  }
  Serial.println("Registered to home network!");
  Serial.print("Turning on GPRS... ");
  delay(2000); 
  while(!gprs_on){
    if (!SIM800.enableGPRS(true)){  
        Serial.println("Failed to turn on GPRS");
        Serial.println("Trying again...");
        delay(2000);
        gprs_on = false;
    }else{
        Serial.println("GPRS now turned on");
        delay(2000);
        gprs_on = true;   
    } 
  }

    // EXtra line may not required in set up portion code...
  
  gsm.println("AT"); //ping the module to see if its up!
  ShowSerialData();
  gsm.println("AT+CSQ");  //Signal Quality Report
  ShowSerialData();
  gsm.println("AT+CREG?");  //Attach or Detach  from Gprs Service
  ShowSerialData();
// EXtra line may not required in set up portion code...
}

void loop()
{
    int x = 22;
    String y = String(x);
    String sms = String("Dear Admin, Bus No: "+ y + " Just leaved from IIUC Campus. Thanks for using real time bus monitoring System.");
   
    Serial.print(" iiuc bus ");
    Serial.print(x);
    Serial.print(",");
    Serial.print(reader++);
    Serial.println();
    SendMessage(sms);
    delay(2000); 
}


void ShowSerialData(){ //Show serial data
  delay(1000);
  while(gsm.available()!=0)
    Serial.write(gsm.read());
    //Serial.println();
}


void SendMessage(String sms){
  
  Serial.println(" debugg 1 : sms value check    ");
  Serial.println(sms);
  
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  
  gsm.print("AT+CMGS=\"");
  gsm.print(cellno);

  Serial.println(" debugg 2 : cell no check    ");
  Serial.println(cellno);
  
  gsm.println("\"\r");

  gsm.println(sms);// The SMS text you want to send
  delay(100);
  gsm.println((char)26);// ASCII code of CTRL+Z

  gsm.println("AT+CMGF=0");    //Sets the GSM Module in PDU Mode

  Serial.println("SMS sent");
}

