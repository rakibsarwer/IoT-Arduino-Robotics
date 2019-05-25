/*--------------------------------------------------------------
  
  Description:  Arduino web server that serves up a web page
                allowing the user to control two different LEDs
  
  Hardware:     - Arduino Uno and official Arduino Ethernet
                  shield (I used Ethernet Shield 2). 
                - Two LEDs and two resistors in series connected between
                  Arduino pin 2 and GND, pin 3 and GND
                
  Software:     Developed using Arduino 1.8.1 software
                Should be compatible with Arduino 1.0 +
  
  References:   This project is a modified version of the 
                "Arduino Web Server LED Control" project found on
                startingelectronics.org

  Date:         08 August 2017
 

--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet2.h> //change if not using Shield 2

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0x90, 0xA2, 0xDA, 0x11, 0x06, 0xA9 };
IPAddress ip(192, 168, 0, 99); // IP address, this will change depending on your network and set up
EthernetServer server(80);  // create a server at port 80

String HTTP_req;          // stores the HTTP request
boolean LED_status = 0;   // state of LED2, off by default
boolean LED_status3 = 0;   // state of LED3, off by default

void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.begin(9600);       // for diagnostics
    pinMode(2, OUTPUT);       // LED on pin 2
    pinMode(3, OUTPUT);       // LED on pin 3
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                HTTP_req += c;  // save the HTTP request 1 char at a time
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println("Connection: close");
                    client.println();
                    // send web page
                    client.println("<!DOCTYPE html>");
                    client.println("<html>");
                    client.println("<head>");
                    client.println("<title>Arduino LED Control</title>");
                    //adds styles
                    client.println("<style type=\"text/css\">body {font-size:1.7rem; font-family: Georgia; text-align:center; color: #333; background-color: #cdcdcd;} div{width:75%; background-color:#fff; padding:15px; text-align:left; border-top:5px solid #bb0000; margin:25px auto;}</style>");
                    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                    client.println("</head>");
                    client.println("<body>");
                    client.println("<div>");
                    client.println("<h1>LED</h1>");
                    client.println("<p>Click to switch LED on and off.</p>");
                    client.println("<form method=\"get\">");
                    ProcessCheckbox(client);
                    client.println("</form>");
                    client.println("<form method=\"get\">");
                    ProcessCheckbox3(client);
                    client.println("</form>");
                    client.println("</div>");
                    client.println("</body>");
                    client.println("</html>");
                    Serial.print(HTTP_req);
                    HTTP_req = "";    // finished with request, empty string
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// switch LED2 and send back HTML for LED2 checkbox
void ProcessCheckbox(EthernetClient cl)
{
    if (HTTP_req.indexOf("LED2=2") > -1) {  // see if checkbox was clicked
        // the checkbox was clicked, toggle the LED
        if (LED_status) {
            LED_status = 0;
        }
        else {
            LED_status = 1;
        }
    }
    
    if (LED_status) {    // switch LED2 on
        digitalWrite(2, HIGH);
        // checkbox is checked
        cl.println("<input type=\"checkbox\" name=\"LED2\" value=\"2\" \
        onclick=\"submit();\" checked>LED2");
    }
    else {              // switch LED2 off
        digitalWrite(2, LOW);
        // checkbox is unchecked
        cl.println("<input type=\"checkbox\" name=\"LED2\" value=\"2\" \
        onclick=\"submit();\">LED2");
    }
}

// switch LED3 and send back HTML for LED3 checkbox
void ProcessCheckbox3(EthernetClient cl)
{
    if (HTTP_req.indexOf("LED3=2") > -1) {  // see if checkbox was clicked
        // the checkbox was clicked, toggle the LED3
        if (LED_status3) {
            LED_status3 = 0;
        }
        else {
            LED_status3 = 1;
        }
    }
    
    if (LED_status3) {    // switch LED3 on
        digitalWrite(3, HIGH);
        // checkbox is checked
        cl.println("<input type=\"checkbox\" name=\"LED3\" value=\"2\" \
        onclick=\"submit();\" checked>LED3");
    }
    else {              // switch LED3 off
        digitalWrite(3, LOW);
        // checkbox is unchecked
        cl.println("<input type=\"checkbox\" name=\"LED3\" value=\"2\" \
        onclick=\"submit();\">LED3");
    }
}
