#include "src/CaptivePortal.cpp"
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>
#include "src/secrets.h"

#define FADE 16
#define BLUE 5
#define RED 4

CaptivePortal captivePortal;
unsigned long startTime;
Ticker breathing;

void setup() {
  // put your setup code here, to run once:
  pinMode(FADE, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);

  digitalWrite(FADE, LOW);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);

  Serial.begin(74880);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(localSSID, localPassword);
  captivePortal.setup(WiFi.softAPIP());
  
  WiFi.begin(remoteSSID, remotePassword);
  Serial.println("Connecting...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("Connected!");
  Serial.println(WiFi.localIP());

  startTime = millis();
  breathing.attach_ms(20, breath, 8000);

  Serial.print("web server running at ");
  Serial.print(WiFi.softAPIP());
}

void loop() {
  // process event loop
  captivePortal.loop();
  delay(0);
}

void breath (int duration) {
  unsigned long now = millis();
  float x = now - startTime;
  x /= (float)duration;
  x *= 2*PI;
  int brightness = 255 * ((cos(x+PI)+1)*.5);
  analogWrite(FADE, brightness);
}
