
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <string.h>

const char *ssid = "fahim";  
const char *password = "fsc12345"; 

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
char temperatureCString[6];
char temperatureFString[6];


//Prepare Mqtt connection data
const char *MQTTBroker = "m10.cloudmqtt.com";
const char *MQTTuser = "temp";
const char *MQTTpassword = "temp";
const char *Topic = "Home/Patient/Temperature";
const char *Topicid = "/value";
uint16_t port = 11511;
//uint16_t port = 1883;  //default port

//..........AES code start.......
#define AES_MAXROUNDS           14
#define AES_BLOCKSIZE           16
#define AES_IV_SIZE             16
#define AES_IV_LENGTH           16
#define AES_128_KEY_LENGTH      16

static const unsigned char Rcon[30]= {
  0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
  0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a,0x2f,
  0x5e,0xbc,0x63,0xc6,0x97,0x35,0x6a,0xd4,
  0xb3,0x7d,0xfa,0xef,0xc5,0x91,
};

static unsigned char AES_xtime(uint32_t x)
{
  return (x&0x80) ? (x<<1)^0x1b : x<<1;
}

static const uint8_t aes_sbox[256] =
{
  0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,
  0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76,
  0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,
  0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0,
  0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,
  0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15,
  0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,
  0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75,
  0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,
  0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84,
  0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,
  0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF,
  0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,
  0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8,
  0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,
  0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2,
  0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,
  0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73,
  0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,
  0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB,
  0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,
  0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79,
  0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,
  0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08,
  0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,
  0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A,
  0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,
  0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E,
  0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,
  0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF,
  0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,
  0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16,
};

inline static uint32_t crypto_ntohl(uint32_t x)
{
    return (
            ((x & 0xff)         << 24) |
            ((x & 0xff00)       << 8)  |
            ((x & 0xff0000UL)   >> 8)  |
            ((x & 0xff000000UL) >> 24)
           );
}

inline static uint32_t crypto_htonl(uint32_t x)
{
    return (
            ((x & 0xff)         << 24) |
            ((x & 0xff00)       << 8)  |
            ((x & 0xff0000UL)   >> 8)  |
            ((x & 0xff000000UL) >> 24)
           );
}


class AES {
public:
  AES(const uint8_t *key, const uint8_t *iv);
  void encryptCBC(const uint8_t *in, uint8_t *out, int length);
private:
  void encrypt(uint32_t *data);
  uint16_t _rounds;
  uint16_t _key_size;
  uint32_t _ks[(AES_MAXROUNDS+1)*8];
  uint8_t _iv[AES_IV_SIZE];
};

AES::AES(const uint8_t *key, const uint8_t *iv) {
    int i = 10, ii;
    uint32_t *W, tmp, tmp2;
    const unsigned char *ip;
    int words = 4;

    _rounds = i;
    _key_size = words;
    W = _ks;
    for (i = 0; i < words; i+=2) {
        W[i+0]= ((uint32_t)key[ 0]<<24)|
            ((uint32_t)key[ 1]<<16)|
            ((uint32_t)key[ 2]<< 8)|
            ((uint32_t)key[ 3]    );
        W[i+1]= ((uint32_t)key[ 4]<<24)|
            ((uint32_t)key[ 5]<<16)|
            ((uint32_t)key[ 6]<< 8)|
            ((uint32_t)key[ 7]    );
        key += 8;
    }

    ip = Rcon;
    ii = 4 * (_rounds+1);
    for (i = words; i<ii; i++)
    {
        tmp = W[i-1];

        if ((i % words) == 0)
        {
            tmp2 =(uint32_t)aes_sbox[(tmp    )&0xff]<< 8;
            tmp2|=(uint32_t)aes_sbox[(tmp>> 8)&0xff]<<16;
            tmp2|=(uint32_t)aes_sbox[(tmp>>16)&0xff]<<24;
            tmp2|=(uint32_t)aes_sbox[(tmp>>24)     ];
            tmp=tmp2^(((unsigned int)*ip)<<24);
            ip++;
        }

        if ((words == 8) && ((i % words) == 4))
        {
            tmp2 =(uint32_t)aes_sbox[(tmp    )&0xff]    ;
            tmp2|=(uint32_t)aes_sbox[(tmp>> 8)&0xff]<< 8;
            tmp2|=(uint32_t)aes_sbox[(tmp>>16)&0xff]<<16;
            tmp2|=(uint32_t)aes_sbox[(tmp>>24)     ]<<24;
            tmp=tmp2;
        }

        W[i]=W[i-words]^tmp;
    }

    /* copy the iv across */
    memcpy(_iv, iv, 16);
}

void AES::encrypt(uint32_t *data) {
    /* To make this code smaller, generate the sbox entries on the fly.
     * This will have a really heavy effect upon performance.
     */
    uint32_t tmp[4];
    uint32_t tmp1, old_a0, a0, a1, a2, a3, row;
    int curr_rnd;
    int rounds = _rounds;
    const uint32_t *k = _ks;

    /* Pre-round key addition */
    for (row = 0; row < 4; row++)
        data[row] ^= *(k++);

    /* Encrypt one block. */
    for (curr_rnd = 0; curr_rnd < rounds; curr_rnd++) {
        /* Perform ByteSub and ShiftRow operations together */
        for (row = 0; row < 4; row++) {
            a0 = (uint32_t)aes_sbox[(data[row%4]>>24)&0xFF];
            a1 = (uint32_t)aes_sbox[(data[(row+1)%4]>>16)&0xFF];
            a2 = (uint32_t)aes_sbox[(data[(row+2)%4]>>8)&0xFF];
            a3 = (uint32_t)aes_sbox[(data[(row+3)%4])&0xFF];

            /* Perform MixColumn iff not last round */
            if (curr_rnd < (rounds - 1)) {
                tmp1 = a0 ^ a1 ^ a2 ^ a3;
                old_a0 = a0;
                a0 ^= tmp1 ^ AES_xtime(a0 ^ a1);
                a1 ^= tmp1 ^ AES_xtime(a1 ^ a2);
                a2 ^= tmp1 ^ AES_xtime(a2 ^ a3);
                a3 ^= tmp1 ^ AES_xtime(a3 ^ old_a0);
            }

            tmp[row] = ((a0 << 24) | (a1 << 16) | (a2 << 8) | a3);
        }

        /* KeyAddition - note that it is vital that this loop is separate from
           the MixColumn operation, which must be atomic...*/
        for (row = 0; row < 4; row++)
            data[row] = tmp[row] ^ *(k++);
    }
}


void AES::encryptCBC(const uint8_t *in, uint8_t *out, int length) {
    int i;
    uint32_t tin[4], tout[4], iv[4];

    memcpy(iv, _iv, AES_IV_SIZE);
    for (i = 0; i < 4; i++)
        tout[i] = crypto_ntohl(iv[i]);

    for (length -= AES_BLOCKSIZE; length >= 0; length -= AES_BLOCKSIZE)
    {
        uint32_t msg_32[4];
        uint32_t out_32[4];
        memcpy(msg_32, in, AES_BLOCKSIZE);
        in += AES_BLOCKSIZE;

        for (i = 0; i < 4; i++)
            tin[i] = crypto_ntohl(msg_32[i])^tout[i];

        AES::encrypt(tin);

        for (i = 0; i < 4; i++)
        {
            tout[i] = tin[i];
            out_32[i] = crypto_htonl(tout[i]);
        }

        memcpy(out, out_32, AES_BLOCKSIZE);
        out += AES_BLOCKSIZE;
    }

    for (i = 0; i < 4; i++)
        iv[i] = crypto_htonl(tout[i]);
    memcpy(_iv, iv, AES_IV_SIZE);
}
//..........AES code end.........

int count = 0;

PubSubClient mqtt(MQTTBroker,port);

void callback(const MQTT::Publish& pub){
  // handle message arrived
  Serial.println(pub.payload_string());
}
void setup()
{

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  DS18B20.begin();
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

  mqtt.set_callback(callback);  //Set Callback function

  

  if (mqtt.connect(MQTT::Connect("esp8266").set_auth(MQTTuser,MQTTpassword))){
    mqtt.publish(Topic, "Hello");  //publish
    mqtt.subscribe(Topicid);    //subscribe
  }

}
 
  void loop()
  {
    
  float tempC;
  float tempF;
  
  do {
    DS18B20.requestTemperatures(); 
    tempC = DS18B20.getTempCByIndex(0);
    dtostrf(tempC, 2, 2, temperatureCString);
    tempF = DS18B20.getTempFByIndex(0);
    dtostrf(tempF, 3, 2, temperatureFString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0));

  count = tempF;
  Serial.println("temperature: ");
   Serial.println(count);
  String tmp = String(count);
  while (tmp.length() < 16) {
    tmp = '0' + tmp;
  }
  char _key[] = "0123456789123456";
  char _iv[] = "0101010101010101";
  uint8_t in[16], out[16], key[16], iv[16];
  for (int i = 0; i < 16; i++) {
    in[i] = tmp[i];
    key[i] = _key[i];
    iv[i] = _iv[i];
  }
  AES aes = AES(key, iv);
  aes.encryptCBC(in, out, 16);
  String encryptData = "";
  for (int i = 0; i < 16;  i++) {
    encryptData += String(out[i]) + ",";
  }
  mqtt.publish(Topic, encryptData);
  Serial.println("haaaaiii");
  if(mqtt.subscribe(Topicid)!=0)    //subscribe
  {
  
    
  Serial.println(Topicid);
  }
  
  
  mqtt.loop();
}

