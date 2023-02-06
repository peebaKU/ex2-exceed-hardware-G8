#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

// code ---> td7vz

// endpoint --> https://exceed-hardware-stamp465.koyeb.app/all_traffic


const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";

const String point = "8";
const int nearby_1 = 7;
const int nearby_2 = 9;

// 0 --> green
// 1 --> yellow
// 2 ---> red

const String nearby_1s = "7";
const String nearby_2s = "9";

void GET_traffic()
{
  DynamicJsonDocument doc(65536);
  
  HTTPClient http;
  const String url = baseUrl + "/all_traffic";
  http.begin(url);

  Serial.println("Nearby traffic");
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);
    JsonArray all = doc["all_traffic"].as<JsonArray>();
    for (JsonObject a: all){
      if (a["point"].as<String>() == "7" || a["point"].as<String>() == "8" || a["point"].as<String>() == "9"){
        Serial.println("Point ---> " + a["point"].as<String>());
        Serial.println("Traffic ---> " + a["traffic"].as<String>());
      }
    }
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
  
  serializeJson(doc, json); // convert Dynamic ---> string json

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