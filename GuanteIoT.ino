
#include <WiFiClientSecure.h>


#include <WiFi.h>

#include <WiFiClient.h>

#include <WiFiServer.h>

#include <WiFiUdp.h>

#include <dummy.h>

#include "ThingSpeak.h"
 
char ssid[] = "FAMILIAFUENTES"; //SSID
char pass[] = "35TA0M555GG"; // Contraseña
//-------------------------------------------//
long duration;
int alarma;
int distance;
const int trigger = 12;
const int echo = 14;
const int buzzer = 4;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField = 1182784; // Channel ID de ThingSpeak
const int ChannelField = 1; // Campo
const char * myWriteAPIKey = "05ANPRP2AQ45WLY6"; // API KEY de ThingSpeak

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  ThingSpeak.begin(client);
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
  
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\Conexión exitosa");
  }

  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  Serial.print("Distance in cm: ");
  Serial.println(distanceCM);

  if(distanceCM<=50)
 {
  digitalWrite(buzzer, LOW);
  
 }
 else{
  digitalWrite(buzzer, HIGH);
 }

  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);
  delay(1000);
}
