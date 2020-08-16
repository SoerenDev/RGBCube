/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com  
*********/

#ifdef ESP32
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_NeoPixel.h>
#else
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include <Adafruit_NeoPixel.h>
#endif

#define LED_PIN 5
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Replace with your network credentials
const char *ssid = "devolo-30d32dd04fe6";
const char *password = "CSKHQHPICXLOWQOV";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setColor(int,int,int);

void setup()
{

  //Setup RGB
  strip.begin();
  strip.show();
  
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/404.html", "text/html");
  });

  server.on("/", HTTP_ANY, [](AsyncWebServerRequest *request){
    int red = request->arg("red").toInt();
    int green = request->arg("green").toInt();
    int blue = request->arg("blue").toInt();
    setColor(red,green,blue);
    request->send(SPIFFS, "/start.html", "text/html");
  });

  // Start server
  server.begin();
}

void loop()
{
}

void setColor(int r, int g, int b) {
  for(int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(0, r, g, b);
  }
  strip.show();
}
