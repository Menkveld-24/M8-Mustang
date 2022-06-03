#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    10

CRGBArray<NUM_LEDS> leds;
byte color = 255;
byte dim = 155;
byte saturation = 255;
void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
//  leds[0] = CRGB::White;
//  FastLED.show();
}

void loop() {
  color--;
  dim++;
  saturation --;
  for (int i = 0; i <= 3; i++) {
    leds[i] = CHSV(color, saturation, dim);
    FastLED.show();
    delay(200);
  }
  for (int i = 4; i <=9; i++){
    leds[i] = CHSV(color, saturation-50, dim);
    FastLED.show();
    delay(200);
  }
  for (int i = 9; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(200);
  }
}