#include <ESP8266WiFi.h>
#include <Servo.h>  //red = vcc ,brown = ground,yellow = data

#define buzzer D3
#define flam D1
#define smoke A0
#define s1 D4
#define s2 D7
#define pump D5
// Set these to run example.
#define HOST "maker.ifttt.com"
#define WIFI_SSID "Kishan"
#define WIFI_PASSWORD "93283Kish@n"

Servo servo1;
Servo servo2;
int angle;
int fValue;
int sensorValue;

void setup() {
  servo1.attach(s1);
  servo2.attach(s2);
  servo1.write(angle);
  servo2.write(angle);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(flam, INPUT);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
 /*Serial.println("enter the value");
  while(Serial.available()==0){};
   a = Serial.parseInt();  
  Serial.println((String)"your value is : " + a);     */
}

void loop() 
{
             WiFiClient clint;
           const int httpPort = 80;
           if(!clint.connect(HOST,httpPort)){
             Serial.println("connection failed");
             return;
           }
          /* Serial.println("enter the value");
           while(Serial.available()==0){};
           a = Serial.parseInt();  
           Serial.println((String)"your value is : " + a); */
            for(angle = 0; angle <= 90; angle++)  
             {                                  
             servo1.write(angle);               
             delay(50);                   
             } 
            for(angle = 90; angle >= 0; angle--)    
             {                                
            servo1.write(angle);           
            delay(50);       
             } 
            fValue = digitalRead(flam);
           Serial.println(fValue);
           sensorValue = analogRead(smoke);
           Serial.print("VALUE: ");
           Serial.print(sensorValue);
           Serial.println("ppm");
           if(fValue == 0)
           {
             
             String url = "/trigger/Alert/json/with/key/pVbIpsLmp7ELRoVnjELg5lqJCPsBUHp4KhJuIDGy1wF";
             Serial.print("Requesting Url:");
             Serial.println(url);
             clint.print(String("GET ") + url + " HTTP/1.1\r\n" + "HOST: " + HOST + "\r\n" + "connection: close\r\n\r\n");
             digitalWrite(buzzer, HIGH);
              for(angle = 0; angle <= 90; angle++)  
              {                                  
              servo2.write(angle); 
              servo1.write(angle); 
               digitalWrite(pump,LOW);               
              delay(25);                  
              } 
             for(angle = 90; angle >= 0; angle--)    
              {                                
             servo2.write(angle);
              servo1.write(angle);   
              digitalWrite(pump,LOW);          
             delay(25);         
              }  
           }
          if( sensorValue > 32 )
          {
            
            String url = "/trigger/Alerts/json/with/key/pVbIpsLmp7ELRoVnjELg5lqJCPsBUHp4KhJuIDGy1wF";
            Serial.print("Requesting Url:");
            Serial.println(url);
            clint.print(String("GET ") + url + " HTTP/1.1\r\n" + "HOST: " + HOST + "\r\n" + "connection: close\r\n\r\n");
            digitalWrite(buzzer, HIGH); 
             for(angle = 0; angle <= 90; angle++)  
             {                                  
             servo2.write(angle); 
              servo1.write(angle);   
              digitalWrite(pump,LOW);             
             delay(25);                  
             } 
            for(angle = 90; angle >= 0; angle--)    
             {                                
            servo2.write(angle); 
             servo1.write(angle); 
             digitalWrite(pump,LOW);           
            delay(25);         
             }    
          }
           else{
            Serial.println("EVERYTHING IS OHK");   
            digitalWrite(buzzer, LOW);   
            digitalWrite(pump,HIGH); 
            
            delay(100);
           }
  }
