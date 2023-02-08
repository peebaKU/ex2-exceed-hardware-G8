#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>


const String baseUrl = "http://group8.exceed19.online/";

int status_room1 = 0;//standard
int status_room2 = 0;//standard
int status_room3 = 0;//standard
int value_light1 = 255;//standard
int value_light2 = 255;//standard
int value_light3 = 255;//standard
int auto_light1 = 0;//standard
int auto_light2 = 0;//standard
int auto_light3 = 0;//standard


void Connect_Wifi()
{
  const char *ssid = "B";
  const char *password = "b123456789";
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}




void GET_room()
{
  DynamicJsonDocument doc(65536);

  HTTPClient http;
  const String url = baseUrl + "/web_data";
  http.begin(url);

  Serial.println("get room");
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);

    status_room1 = doc["room1"]["state"].as<int>();
    status_room2 = doc["room2"]["state"].as<int>();
    status_room3 = doc["room3"]["state"].as<int>();
    value_light1 = doc["room1"]["brigthness"].as<int>(); 
    value_light2 = doc["room2"]["brigthness"].as<int>(); 
    value_light3 = doc["room3"]["brigthness"].as<int>();
    auto_light1 = doc["room1"]["is_auto"].as<int>();
    auto_light2 = doc["room2"]["is_auto"].as<int>();
    auto_light3 = doc["room3"]["is_auto"].as<int>();

  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

void POST_update_room()
{
  const String url = baseUrl + "/update_web_data";
  String json;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  DynamicJsonDocument doc(2048);

  doc["room1"]["state"] = status_room1;
  doc["room2"]["state"] = status_room2;
  doc["room3"]["state"] = status_room3;
  doc["room1"]["brigthness"] =  value_light1;
  doc["room2"]["brigthness"] =  value_light2;
  doc["room3"]["brigthness"] =  value_light3;
  doc["room1"]["is_auto"] = auto_light1;
  doc["room2"]["is_auto"] = auto_light2;
  doc["room3"]["is_auto"] = auto_light3;
  
  
  serializeJson(doc, json);

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