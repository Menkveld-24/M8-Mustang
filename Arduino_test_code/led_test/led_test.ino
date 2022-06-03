#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    10

CRGBArray<NUM_LEDS> leds;
byte color = 100;
byte dim = 155;
byte saturation = 200;

void setup() {

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop() {
  for (int i = 0; i <= 9; i+= 2) {
    leds[i] = CHSV(color+i*20, saturation, dim);
    leds[i+1] = CHSV(color+i*20, saturation, dim);
    FastLED.show();
    delay(50);
  }

  for (int i = 9; i >= 0; i-= 2) {
    leds[i] = CHSV(color-i*20, saturation, dim);
    leds[i-1] = CHSV(color-i*20, saturation, dim);
    FastLED.show();
    delay(50);
  }
}
