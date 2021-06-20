#include <ESP8266WiFi.h>
#include <AntaresESP8266HTTP.h>
WiFiClient wifiClient;;
#define ACCESSKEY "5abe069da3addc73:2d4471616fd0d7d6"
AntaresESP8266HTTP antares(ACCESSKEY);
void setup(){
    Serial.begin(9600);
    pinMode(D8, OUTPUT);
    pinMode(D13, OUTPUT);
    pinMode(D0,INPUT);
    WiFi.begin("Pacman","Sarden99");
    Serial.println("Connecting :");
    while(WiFi.status() != WL_CONNECTED){
       digitalWrite(D8, LOW);
       delay(500);
       digitalWrite(D8, HIGH);
       delay(500);
       Serial.println("*");
    }
    if (WiFi.status() == WL_CONNECTED){
      tone(D13,3,500);
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
//    antares.setDebug(true); //this for debuging or show antares output
    antares.wifiConnection("Pacman","Sarden99");
}
void loop(){
int z = analogRead(A0),r = digitalRead(D0);
  if (r == 0){
      digitalWrite(D13, HIGH);
  }else{
      digitalWrite(D13, LOW);
  }
  antares.add("rain",z);
  antares.send("Mydht","RainSensor");
delay(3000);
}
