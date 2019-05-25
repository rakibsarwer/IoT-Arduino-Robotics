
#include <RFID.h>
#include <SPI.h>


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


/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 9
#define RESET_DIO 8

/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;
String x[3]={};

//For connecting with wemos uncomment the For Wemos lines, comment the For Arduino lines
//SoftwareSerial gsm(D7, D8, false, 256); // Rx, Tx //For Wemos
SoftwareSerial gsm(6, 7); //Rx, Tx //For Arduino

String sms, cellno = "+8801793030209"; // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS


char RcvdMsg[200] = " ", MsgMob[15], MsgTxt[200]=" ";
int RcvdCheck = 0, RcvdConf = 0, aindex = 0, RcvdEnd = 0, MsgLength = 0;
boolean flag=false;

void setup()
{ 
  Serial.begin(9600);

  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  
  //Serial.begin(115200); //For Wemos
  //gsm.begin(115200); //For Wemos
  gsm.begin(9600); //For Arduino
  delay(1000);
  gsm.println("AT"); //ping the module to see if its up!
  ShowSerialData();
  gsm.println("AT+CSQ");  //Signal Quality Report
  ShowSerialData();
  gsm.println("AT+CREG?");  //Attach or Detach  from Gprs Service
  ShowSerialData();
}

void loop()
{
  /* Temporary loop counter */
  byte i;

  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    int x = RC522.serNum[0];
    String y = String(x);
    String sms = String("Dear Admin, Bus No: "+ y + " Just leaved from IIUC Campus. Thanks for using real time bus monitoring System.");
    /* Output the serial number to the UART */

   /*
    int x[200];
    for(i = 0; i <= 2; i++)
    {
      Serial.println(RC522.serNum[i],DEC);
      x[i]=RC522.serNum[i]; 
      //Serial.print(RC522.serNum[i],HEX);
    }*/
        
    Serial.print(" iiuc bus ");
    Serial.print(x);
    Serial.print(",");
    Serial.print(reader++);
    Serial.println();
    SendMessage(sms);
    delay(2000);
   }
  delay(1000);
}

void SendMessage(String sms){
  
  Serial.println(" debugg 1 : sms value check    ");
  Serial.println(sms);
  
  gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  ShowSerialData();  
  gsm.print("AT+CMGS=\"");
  gsm.print(cellno);

  Serial.println(" debugg 2 : cell no check    ");
  Serial.println(cellno);
  
  gsm.println("\"\r");
  ShowSerialData();
  gsm.println(sms);// The SMS text you want to send
  delay(100);
  gsm.println((char)26);// ASCII code of CTRL+Z
  ShowSerialData();
  gsm.println("AT+CMGF=0");    //Sets the GSM Module in PDU Mode
  ShowSerialData();  
  Serial.println("SMS sent");
}

void ShowSerialData(){ //Show serial data
  delay(1000);
  while(gsm.available()!=0)
    Serial.write(gsm.read());
    //Serial.println();
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
