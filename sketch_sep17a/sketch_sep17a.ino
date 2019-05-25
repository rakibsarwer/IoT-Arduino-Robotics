#include <RFID.h>
#include <SPI.h>
#include <String.h>

#define SDA_DIO 9
#define RESET_DIO 8
RFID RC522(SDA_DIO, RESET_DIO); 
int reader=0;
#include <Servo.h>

int RED=6;
int GREEN=3;
int buzzer = 11;
Servo myservo;
int pos = 0;
int i,n;

int key[4]={117,60};

int flag=0;
void setup() //Setup Subprocedure
{  
  Serial.begin(19200);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  //pinMode (sensor1, INPUT); //set Analog pin 0 as input
pinMode(RED,OUTPUT);
pinMode(GREEN,OUTPUT);
 myservo.attach(7); 
  pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); 
pinMode(buzzer,OUTPUT);
 
  
  delay(1000);
}
 
void loop() // Main loop
{

     byte i;
      
     delay(2);
    
    if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    int x = RC522.serNum[0];
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

   for(i=0;i<2;i++)
   {
    if(x==key[i])
    {
      flag=1;
     
      break;  
    } 
    else{
      flag=2;
       digitalWrite(buzzer,HIGH);
       delay(5000);   
       digitalWrite(buzzer,LOW);
       delay(500);  
      break; 
      }
   }
Serial.println(flag);
   if(flag==1)
      {
       Serial.println("Welcome    bus accesed ");
       digitalWrite(buzzer,LOW);
        digitalWrite(GREEN,HIGH);
  digitalWrite(RED,LOW);
   pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(2000);  
    pos = 90;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
      }
      else if(flag==2){
        Serial.println("accesed Deniyed");
        
        
          digitalWrite(GREEN,LOW);
  digitalWrite(RED,HIGH);
   pos = 0;
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);    
        
        }   
    delay(2000);
   }
  delay(1000);

   
 
  
}


