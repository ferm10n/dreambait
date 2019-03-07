#include <Ticker.h>
#define FADE 16
#define BLUE 5
#define RED 4

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

  startTime = millis();
  breathing.attach_ms(20, breath, 8000);
}

void loop() {
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
