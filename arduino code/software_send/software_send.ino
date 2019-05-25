#define INTERVAL_MESSAGE1 5000

 
unsigned long time_1 = 0;

void setup() {
    Serial.begin(9600);
}
 
void loop() {
    if(millis() > time_1 + INTERVAL_MESSAGE1){
        time_1 = millis();
        //print_time(time_1);
        int tic=22;
        Serial.println(tic);
    }
   
   
}
// 
//void print_time(unsigned long time_millis){
//    Serial.print("Time: ");
//    Serial.print(time_millis/1000);
//    Serial.print("s - ");
//}
