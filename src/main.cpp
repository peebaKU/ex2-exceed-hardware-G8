// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define red 26
#define yellow 25
#define green 33
#define ldr 34
#define button 27

#define light 50

int state = 1;
int count = 0;

Bounce debouncer = Bounce();

int count_red = 0;
int count_green = 0;
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
  digitalWrite(green, HIGH);
}

void loop()
{
  // *** write your code here ***
  debouncer.update();
  if (debouncer.fell() && state ==1){
      state=2;
  }
  // Your can change everything that you want
  int x = map(analogRead(ldr), 1000, 4095, 0, 255);
  if (state == 1)//green
  {
    digitalWrite(green, HIGH);
    if(count_green==0)
    {  POST_traffic("green");
       GET_traffic();
       count_green=1;
    }
    delay(50);
  }
  else if (state == 2)//yelllow
  { digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    POST_traffic("yellow");
    delay(8000);
    digitalWrite(yellow, LOW);
    delay(10);
    state=3;
  }
  else if (state == 3)//red
  { digitalWrite(red, HIGH);
    if(count_red==0){POST_traffic("red");GET_traffic();delay(5000);}
    if(x<=light){
      state=1;
      digitalWrite(red, LOW);
      delay(10);
      
    }
    count_red++;
    count_green=0;
    
  }
}

void Connect_Wifi()
{
  const char *ssid = "M";
  const char *password = "leesoome123";
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