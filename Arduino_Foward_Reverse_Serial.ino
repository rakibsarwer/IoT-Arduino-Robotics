/* Nudge Me's Youtube Channel:
 *  
 * Forward/reverse control of DC motor using 2 relays and serial communication.
 * This code will make to motor turn CW when we send 'A', turn CCW when we send 'B' and stop when we send 'X'.
 * You can send those 'A', 'B' and 'X' via 2 ways:
 *    a) Through Serial Monitor window
 *    b) Through Bluetooth connection
 *       - Connect Bluetooth module's (e.g. HC-06) TX pin to Arduino's RX pin, and RX pin of Bluetooth module to TX pin of Arduino. Connect the Bluetooth module's VCC pin to 3.3V and GND pin to GND.
 * Connect first relay's Enable pin to Arduino's pin 11 and the second relay's Enable pin to Arduino's pin 12.
 * Follow the connection in this diagram: https://goo.gl/Fnsf4B (this diagram has no Bluetooth module connection. Refer (b) above for connecting the BT module to your Arduino).
 * More info refer this video: https://youtu.be/QmLQMQ-eAZY
 * 
 * This code was updated on 11 Nov 2017 (3.00pm).
 */

char c;

void setup() 
{     
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  Serial.println("Started...");
} 

void loop() { 
  
   while (Serial.available()) 
   {
         
      if (Serial.available() > 0) 
      {
        c = Serial.read();
      }
     
      if ((c == 'a') || (c == 'A')) 
      {
        Serial.println("RECEIVE 'A' - FORWARD");      
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);  
      }    
         
      else if ((c == 'b') || (c == 'B')) 
      { 
        Serial.println("RECEIVE 'B' - BACKWARD");         
        digitalWrite(12, LOW);
        digitalWrite(11, HIGH);             
      }  
      
      else if ((c == 'x') || (c == 'X')  ) 
      { 
        Serial.println("RECEIVE 'X' OR 'x' - STOP"); 
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);        
      }
  
      Serial.flush();  
   }
   
}
