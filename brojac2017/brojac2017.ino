#include <Arduino.h>
#include <TM1637Display.h>


#define CLK 2
#define DIO 3


#define TEST_DELAY   2000


TM1637Display display(CLK, DIO);

void setup()
{
  pinMode(4,INPUT);
  display.setBrightness(6); 
}

int numb=0;
int pres=0;
void loop()
{
   display.setBrightness(0x0f);
   display.showNumberDec(numb,false);
   if(digitalRead(4)==1)
   {
    if(pres==0)
   {
    numb++;
    pres=1;
   }
    }
  else
  {
    pres=0;
    }
}
