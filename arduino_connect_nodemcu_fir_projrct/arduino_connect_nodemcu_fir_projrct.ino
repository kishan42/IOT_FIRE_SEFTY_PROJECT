#include <SoftwareSerial.h>
#include <Servo.h>
#define buzzer 5
#define s2 8
#define pump 12
SoftwareSerial ArduinoUno(3,2);
Servo servo2;
int angle;  
int fvalue,sensorvalue,val;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
void setup(){
   servo2.attach(s2);
   servo2.write(angle);
  Serial.begin(9600);
  ArduinoUno.begin(4800);
  pinMode(buzzer,OUTPUT);
  pinMode(pump,OUTPUT);
}

void loop(){ 
  while(ArduinoUno.available()>0){
    val = ArduinoUno.parseInt();
  if(ArduinoUno.read()== '\n'){
   fvalue  = val%10;
   sensorvalue = val/10;
  Serial.println(fvalue);
  Serial.println(sensorvalue);
  }
 if(sensorvalue > 200 || fvalue == 0)
 {  
   digitalWrite(buzzer,HIGH);
   digitalWrite(pump,HIGH);
    for(angle = 0; angle <= 90; angle++)
    {                                  
       servo2.write(angle); 
       delay(25);                  
    } 
    for(angle = 90; angle >= 0; angle--)    
    {                                
       servo2.write(angle);    
       delay(25);         
    }  
   delay(50);
 }
 if(sensorvalue < 200 || fvalue == 1)
 {
   digitalWrite(buzzer,LOW);
   digitalWrite(pump,LOW);
 }
}
delay(30);
}
