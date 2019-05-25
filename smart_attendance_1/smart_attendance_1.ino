/*
   ----------------------------------------------------------------------------
   This sketch uses the MFRC522 library ; see https://github.com/miguelbalboa/rfid
   for further details and other examples.

   NOTE: The library file MFRC522.h has a lot of useful info. Please read it.

   This sketch show a simple locking mechanism using the RC522 RFID module.
   ----------------------------------------------------------------------------
   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

*/
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "xxxx";
char wifiPassword[] = "xxxxx";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "xxxxx";
char password[] = "xxxxx";
char clientID[] = "xxxxxx";

#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

#define RST_PIN         D3        // Configurable, see typical pin layout above
#define SS_PIN          D8        // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String read_rfid;
String ok_rfid_1 = "452b85ab";
String ok_rfid_2 = "8525fab";
String ok_rfid_3 = "7e287b25";
String ok_rfid_4 = "559acd65";
//String ok_rfid_2="ffffffff"; //add as many as you need.

unsigned long lastMillis = 0;

int a;
int b;
int c;
int d;

int EEaddress0 = 1;
int EEaddress2 = 4;
int EEaddress4 = 8;
int EEaddress6 = 12;/*
   Initialize.
*/
void setup() {
  Serial.begin(9600);
  EEPROM.begin(32);
  Serial.begin(9600);         // Initialize serial communications with the PC
  while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522 card
  a = EEPROM.get(EEaddress0, a);
  Serial.println(a);
  b = EEPROM.get(EEaddress2, b);
  Serial.println(b);
  c = EEPROM.get(EEaddress4, c);
  Serial.println(c);
  d = EEPROM.get(EEaddress6, d);
  Serial.println(d);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  Serial.println("connected");
    pinMode(D4, OUTPUT);
}

/*
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  read_rfid = "";
  for (byte i = 0; i < bufferSize; i++) {
    read_rfid = read_rfid + String(buffer[i], HEX);
  }
}

void check1() {
  a++;
  Serial.println(a);
  EEPROM.put(EEaddress0, a);
  EEPROM.commit();
    digitalWrite(D4, LOW);
  delay(2000);
}
void check2() {
  b++;
  Serial.println(b);
  EEPROM.put(EEaddress2, b);
  EEPROM.commit();
    digitalWrite(D4, LOW);
  delay(2000);
}
void check3() {
  c++;
  Serial.println(c);
  EEPROM.put(EEaddress4, c);
  EEPROM.commit();
    digitalWrite(D4, LOW);
delay(2000);
}
void check4() {
  d++;
  Serial.println(d);
  EEPROM.put(EEaddress6, d);
  EEPROM.commit();
  digitalWrite(D4, LOW);
  delay(2000);
}

void loop() {
    digitalWrite(D4, HIGH);
Cayenne.loop();

  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    Cayenne.virtualWrite(0, a);
    Cayenne.virtualWrite(1, b);
    Cayenne.virtualWrite(2, c);
    Cayenne.virtualWrite(3, d);
    //Some examples of other functions you can use to send data.
    //Cayenne.celsiusWrite(1, 22.0);
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  }
  Serial.println("reading");
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

  if (read_rfid == ok_rfid_1) {
    check1();
  }
  if (read_rfid == ok_rfid_2) {
    check2();
  }
  if (read_rfid == ok_rfid_3) {
    check3();
  }
  if (read_rfid == ok_rfid_4) {
    check4();
  }

}

