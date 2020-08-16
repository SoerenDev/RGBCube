/*
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>


#define LED_PIN 5
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 2;

void handleRoot();              // function prototypes for HTTP handlers
void handleLED();
void handleNotFound();
void setColor(int,int,int);

void setup(void){
  strip.begin();
  strip.show();
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(led, OUTPUT);

  wifiMulti.addAP("foobar", "");   // add Wi-Fi networks you want to connect to
        wifiMulti.addAP("devolo-30d32dd04fe6", "CSKHQHPICXLOWQOV");
  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer


  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", "<html>\n<head>\n<title>RGB</title>\n</head>\n<body>\n<form action=\"LED\" method=\"POST\">\n<input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"slider\" name=\"red\"></br>\n<input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"slider\" name=\"green\"></br>\n<input type=\"range\" min=\"0\" max=\"255\" value=\"0\" class=\"slider\" name=\"blue\"></br>\n<input type=\"submit\" value=\"Send\">\n</form>\n</body>\n</html>");
}

void handleLED() {  
  // If a POST request is made to URI /LED
  Serial.println("Pfad LED");
  int red = server.arg("red").toInt();
  int green = server.arg("green").toInt();
  int blue = server.arg("blue").toInt();
  setColor(red,green,blue);
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "");
}
void setColor(int r, int g, int b) {
  for(int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(0, r, g, b);
  }
  strip.show();
}*/
