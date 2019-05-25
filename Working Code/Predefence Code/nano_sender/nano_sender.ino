//char mystr[5] = "hello"; //String data

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
}
byte a = 0;
void loop() {

a = 27;

String b;
char c[5];
int i=0;

b = String(a);
//b.toCharArray(c,5);


//  x=247;
//  //char mystr[1]= {x};
//  String z=String(x);
  Serial.write(a); //Write the serial data
  Serial.print(a);
  delay(1000);
}
