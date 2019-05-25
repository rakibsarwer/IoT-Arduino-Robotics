#define TEMP A1 //costante per pin del sensore LM35

float val_temp=0.0; //variabile per ilvalore di temperatura
int val_analogico=0; //variabile per leggere valore analogico pin A1

String s = "";

void setup() 
{
  Serial.begin(9600); //attivo la comunicazione seriale 
  pinMode(TEMP,INPUT); //imposto pin di input per il sensore
}

void loop()
{
    val_analogico = analogRead(TEMP); // valore: 0 - 1023

    //conversione del valore analogico letto da Arduino in gradi centrigradi
    val_temp=(5.0 * val_analogico * 100.0) / 1024;

    //mi creo stringa da visualizzare su monitor seriale
    s = "La temperatura e': " + String(val_temp)+ " gradi";
    
    Serial.println(s);

    delay(5000);

}
