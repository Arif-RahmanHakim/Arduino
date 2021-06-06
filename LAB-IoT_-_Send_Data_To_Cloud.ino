#include <DHT.h>
#include <ESP8266WiFi.h>
String apiKey = "FLWAVBIJNUSDZM99";
const char* server = "api.thingspeak.com"; 
DHT dht(D0, DHT11);
WiFiClient client;
void setup() 
{
Serial.begin(9600);
delay(10);

dht.begin();
WiFi.begin("Pacman", "Sarden99");

Serial.println();
Serial.println();
 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("");
if (WiFi.status() == WL_CONNECTED){
  Serial.println("WiFi connected");
}}
 
void loop() 
{
 
float h = dht.readHumidity();
float t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
} 
if (client.connect(server,80)) {
  String postStr = apiKey;
  postStr +="&field1=";
  postStr += String(h);
  postStr +="&field2=";
  postStr += String(t);
  postStr += "\r\n\r\n";
   
  client.print("POST /update HTTP/1.1\n");
  client.print("Host: api.thingspeak.com\n");
  client.print("Connection: close\n");
  client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
  client.print("Content-Type: application/x-www-form-urlencoded\n");
  client.print("Content-Length: ");
  client.print(postStr.length());
  client.print("\n\n");
  client.print(postStr);
}else{
  Serial.println("cant connect");
}
Serial.print(h);
Serial.print(t);
delay(5000);
}
