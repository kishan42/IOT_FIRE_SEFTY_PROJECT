#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
#define smoke A0
#define flam D1
#define s1 D5
#define led D0
#define HOST "maker.ifttt.com"
#define WIFI_SSID "Kishan"
#define WIFI_PASSWORD "93283Kish@n"
Servo servo1;
SoftwareSerial NodeMCU(D2,D3);
int sensorValue;
int angle;
int fValue;
void setup(){
  Serial.begin(9600);
  NodeMCU.begin(4800);
  servo1.attach(s1);
  servo1.write(angle);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
   pinMode(flam, INPUT);
    pinMode(led, OUTPUT);
 WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
}
}

void loop()
{
   WiFiClient clint;
           const int httpPort = 80;
           if(!clint.connect(HOST,httpPort))
           {
             Serial.println("connection failed");
             return;
           }
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
            sensorValue = analogRead(smoke);
            fValue = digitalRead(flam);
           Serial.println(fValue);     
           Serial.print("VALUE: ");
           Serial.print(sensorValue);
           Serial.println("ppm");
  //NodeMCU.print((String)sensorValue + (String)fValue);
  //NodeMCU.print();
 // NodeMCU.println("\n");
   if(fValue == 0)
           {
             digitalWrite(led,LOW);
             String url = "/trigger/Alert/json/with/key/pVbIpsLmp7ELRoVnjELg5lqJCPsBUHp4KhJuIDGy1wF";
             Serial.print("Requesting Url:");
             Serial.println(url);
             clint.print(String("GET ") + url + " HTTP/1.1\r\n" + "HOST: " + HOST + "\r\n" + "connection: close\r\n\r\n");
           }
   else if( sensorValue > 200 )
          {
            digitalWrite(led,LOW);
            String url = "/trigger/Alerts/json/with/key/pVbIpsLmp7ELRoVnjELg5lqJCPsBUHp4KhJuIDGy1wF";
            Serial.print("Requesting Url:");
            Serial.println(url);
            clint.print(String("GET ") + url + " HTTP/1.1\r\n" + "HOST: " + HOST + "\r\n" + "connection: close\r\n\r\n");
          }  
    else{
            Serial.println("EVERYTHING IS OHK");              
            digitalWrite(led,HIGH);
            delay(100);
           }
            NodeMCU.print((String)sensorValue + (String)fValue);
            NodeMCU.println("\n");
      delay(30);
}
