#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"
#define LED1 33
#define LED2 32
#define LED3 25

char * endpoint = "https://ecse-three-led-api.onrender.com/api/state";
void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  Serial.println("Connecting");
  while(WiFi.status()!=WL_CONNECTED)//WL_CONNECTED IS A CONSTANT IN WIFI HEADER FILE
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()==WL_CONNECTED)
  {
    HTTPClient http;

    String http_response;
    http.begin(endpoint);
    http.addHeader("X-API-Key","Spencer#3697");

    int httpResponseCode= http.GET(); //if a negative number is return then a connection to the servo was not established 

    if(httpResponseCode>0)
    {
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response from server");
      http_response=http.getString();
      Serial.println(http_response);

    }
    else{
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end(); 

    // String input;

StaticJsonDocument<192> doc;

DeserializationError error = deserializeJson(doc, http_response);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}

const char* id = doc["_id"]; // "63fac23a77ef4b58d4d5df3e"
const char* user = doc["user"]; // "Spencer#3697"
bool light_switch_1 = doc["light_switch_1"]; // true
bool light_switch_2 = doc["light_switch_2"]; // false
bool light_switch_3 = doc["light_switch_3"]; // false

if(light_switch_1 ==false)
{
  digitalWrite(LED1, LOW);
}
else
{
  digitalWrite(LED1,HIGH);
}
if(light_switch_2 ==false)
{
  digitalWrite(LED2, LOW);
}
else
{
  digitalWrite(LED2,HIGH);
}
if(light_switch_3 ==false)
{
  digitalWrite(LED3, LOW);
}
else
{
  digitalWrite(LED3,HIGH);
}

  }
  else{

    return;
  }
}
