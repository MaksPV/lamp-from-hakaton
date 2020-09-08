#define NUM_LEDS 26
#include "FastLED.h"
#define PIN 13
CRGB leds[NUM_LEDS];
byte counter;
byte menu;
#define photo A0
#define onlight 310
#define pot1 A1
#define pot2 A2
#define pot3 A3
#define pot4 A4

void setup()
{
  butt.setType(HIGH_PULL);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);
  digitalWrite(8, 1);
  Serial.begin(9600);
}

void loop() {
  menu = map(analogRead(pot4), 0, 1023, 0, 4);
  if (menu == 0) customLight();
  if (menu == 1) blueLight();
  if (menu == 2) yellowLight();
  if (menu >= 3) SanicDash();
  FastLED.show();
}

void blueLight(){
  int photo_stats = analogRead(photo);
  if (photo_stats > onlight){photo_stats = onlight;}
  for (int i = 0; i < NUM_LEDS; i++ ) {
    Serial.println(photo_stats);
    leds[i] = CRGB(byte(map(photo_stats,0,onlight,135,0)),
                    byte(map(photo_stats,0,onlight,206,0)),
                      byte(map(photo_stats,0,onlight,235,0)));
  }
}

void YellowLight(){
  int photo_stats = analogRead(photo);
  if (photo_stats > onlight){photo_stats = onlight;}
  for (int i = 0; i < NUM_LEDS; i++ ) {
    Serial.println(photo_stats);
    leds[i] = CRGB(byte(map(photo_stats,0,onlight,255,0)),
                    byte(map(photo_stats,0,onlight,255,0)),
                      byte(map(photo_stats,0,onlight,0,0)));
  }
}

void customLight(){
  for (int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = CRGB(byte(map(analogRead(pot1),0,1023,0,255)),
                    byte(map(analogRead(pot2),0,1023,0,255)),
                      byte(map(analogRead(pot3),0,1023,0,255)));
  }
}


void SanicDash(){
  for (int i = 0; i < NUM_LEDS; i++ ) {leds[i] = CHSV(counter + i * 2, 255, 255);}
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  delay(5);         // скорость движения р,адуги
}
