#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

const String point = "8";
const int nearby_1 = 7;
const int nearby_2 = 9;

void GET_traffic()
{
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  const String url = baseUrl + "/all_traffic";
  http.begin(url);

  Serial.println("Nearby traffic");
  int httpResponseCode = http.GET();
if (httpResponseCode >= 200 && httpResponseCode < 300) {
        String payload = http.getString();
        deserializeJson(doc,payload);
        JsonArray all = doc["all_traffic"].as<JsonArray>();
        Serial.println(nearby_1);
        Serial.println((const char*)all[nearby_1-1]["traffic"]);
        Serial.println(nearby_2);
        Serial.println((const char*)all[nearby_2-1]["traffic"]);
        Serial.println("me-8");
        Serial.println((const char*)all[8-1]["traffic"]);
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

void POST_traffic(String led)
{
  const String url = baseUrl + "/my_traffic?point=" + point;
  String json;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  DynamicJsonDocument doc(2048);
  doc["code"] = "td7vz";
  doc["traffic"] = led;
  serializeJson(doc, json);

  Serial.println("POST " + led);
  int httpResponseCode = http.POST(json);
  if (httpResponseCode == 200)
  {
    Serial.print("DONE");
    Serial.println();
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}