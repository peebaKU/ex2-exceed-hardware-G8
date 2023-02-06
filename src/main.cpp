// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define red 25
#define yellow 26
#define green 33
#define ldr 34
#define button 27

#define light <แสดงมันมืด มีค่าเท่าไหร่>

int state = 1;
int count = 0;
Bounce debouncer = Bounce();

void Connect_Wifi();

void setup()
{
  Serial.begin(115200);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ldr, INPUT);
  debouncer.attach(button, INPUT_PULLUP);
  debouncer.interval(25);
  Connect_Wifi();

  delay(200);
  // start LED with GREEN and POST to database
  digitalWrite(green, HIGH);
  POST_traffic("green");
}

void loop()
{
  // *** write your code here ***
  // Your can change everything that you want
  if (state == 1)
  {
    // while led GREEN
  }
  else if (state == 2)
  {
    // while led YELLOW
  }
  else if (state == 3)
  {
    // while led RED
  }
}

void Connect_Wifi()
{
  const char *ssid = "Your Wifi Name";
  const char *password = "Your Wifi Password";
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