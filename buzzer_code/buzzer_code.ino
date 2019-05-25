// Buzzer
// buzzer make sounds
//Email:support@sunfounder.com
//Website:www.sunfounder.com
/***********************************/
int buzzer = 12;//the pin of the active buzzer
void setup()
{
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
}
void loop()
{
  unsigned char i; //define a variable
  while(1)
  {
    //output an frequency
    for(i=0;i<80;i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(10000000);//wait for 1ms
      digitalWrite(buzzer,LOW);
      delay(12);//wait for 1ms
    }
    //output another frequency
    for(i=0;i<100;i++)
    {
      digitalWrite(buzzer,HIGH);
      delay(20000000);//wait for 2ms
      digitalWrite(buzzer,LOW);
      delay(2);//wait for 2ms
    }
  }
} 
/****************************************/
