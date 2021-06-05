/*
04-05-2021
Script for esp8266 WeMos D1 R1
to send Temp Humidity and Temprature to Antares
Author by :
Arif Rahman Hakim JI200021
Ayu Pujiastuti
Muhammad Nurul Fadjri
Muhammad Rifky Ramadhan
Raina Sevira Agustin
*/
#include <ESP8266WiFi.h>
#include <AntaresESP8266HTTP.h>
#include "DHT.h"
WiFiClient wifiClient;
DHT dht(D2,DHT11);
#define ACCESSKEY "5abe069da3addc73:2d4471616fd0d7d6"
AntaresESP8266HTTP antares(ACCESSKEY);
void setup(){
    Serial.begin(9600);
    pinMode(D8, OUTPUT);
    pinMode(D0,INPUT);
    dht.begin();
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
float H = dht.readHumidity(),T = dht.readTemperature();
int z = analogRead(A0),r = digitalRead(D0);

  Serial.println("Sending data to Antares:");
  Serial.print("Humidity: ");
  Serial.print(H);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" *C ");
  if (r == 0){
      tone(D13,8,500);
  }else{
    Serial.print("it's not raining");
  }
  antares.add("temprature",T);
  antares.add("humidity",H);
  antares.send("Mydht","Arduino");
  antares.add("rain",z);
  antares.send("Mydht","RainSensor");
delay(3000);
}
