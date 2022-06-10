#include <CSV_Parser.h>
#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    90

CRGBArray<NUM_LEDS> leds;
byte color = 0; // white
byte dim = 255; // no dim for the chosen one
byte trans = 100; // for the leds beside the chosen led 
byte saturation = 0;
byte val;
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

}

void loop() {
  if (Serial.available() > 0) {
      int x = Serial.read();    // The "Serial.read" command returns integer-type
      val = x;                 //             
      switch (val) {
        case 0:
          leds[0] = CHSV(color, saturation, trans);
          leds[1] = CHSV(color, saturation, dim);
          leds[2] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 1:
          leds[3] = CHSV(color, saturation, trans);
          leds[4] = CHSV(color, saturation, dim);
          leds[5] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 2:
          leds[6] = CHSV(color, saturation, trans);
          leds[7] = CHSV(color, saturation, dim);
          leds[8] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 3:
          leds[9] = CHSV(color, saturation, trans);
          leds[10] = CHSV(color, saturation, dim);
          leds[11] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 4:
          leds[12] = CHSV(color, saturation, trans);
          leds[13] = CHSV(color, saturation, dim);
          leds[14] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 5:
          leds[15] = CHSV(color, saturation, trans);
          leds[16] = CHSV(color, saturation, dim);
          leds[17] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 6:
          leds[18] = CHSV(color, saturation, trans);
          leds[19] = CHSV(color, saturation, dim);
          leds[20] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 7:
          leds[21] = CHSV(color, saturation, trans);
          leds[22] = CHSV(color, saturation, dim);
          leds[23] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 8:
          leds[24] = CHSV(color, saturation, trans);
          leds[25] = CHSV(color, saturation, dim);
          leds[26] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 9:
          leds[27] = CHSV(color, saturation, trans);
          leds[28] = CHSV(color, saturation, dim);
          leds[29] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 10:
          leds[30] = CHSV(color, saturation, trans);
          leds[31] = CHSV(color, saturation, dim);
          leds[32] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 11:
          leds[33] = CHSV(color, saturation, trans);
          leds[34] = CHSV(color, saturation, dim);
          leds[35] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 12:
          leds[36] = CHSV(color, saturation, trans);
          leds[37] = CHSV(color, saturation, dim);
          leds[38] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 13:
          leds[39] = CHSV(color, saturation, trans);
          leds[40] = CHSV(color, saturation, dim);
          leds[41] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 14:
          leds[42] = CHSV(color, saturation, trans);
          leds[43] = CHSV(color, saturation, dim);
          leds[44] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 15:
          leds[45] = CHSV(color, saturation, trans);
          leds[46] = CHSV(color, saturation, dim);
          leds[47] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 16:
          leds[48] = CHSV(color, saturation, trans);
          leds[49] = CHSV(color, saturation, dim);
          leds[50] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 17:
          leds[51] = CHSV(color, saturation, trans);
          leds[52] = CHSV(color, saturation, dim);
          leds[53] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 18:
          leds[54] = CHSV(color, saturation, trans);
          leds[55] = CHSV(color, saturation, dim);
          leds[56] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 19:
          leds[57] = CHSV(color, saturation, trans);
          leds[58] = CHSV(color, saturation, dim);
          leds[59] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 20:
          leds[60] = CHSV(color, saturation, trans);
          leds[61] = CHSV(color, saturation, dim);
          leds[62] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 21:
          leds[63] = CHSV(color, saturation, trans);
          leds[64] = CHSV(color, saturation, dim);
          leds[65] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 22:
          leds[66] = CHSV(color, saturation, trans);
          leds[67] = CHSV(color, saturation, dim);
          leds[68] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 23:
          leds[69] = CHSV(color, saturation, trans);
          leds[70] = CHSV(color, saturation, dim);
          leds[71] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 24:
          leds[72] = CHSV(color, saturation, trans);
          leds[73] = CHSV(color, saturation, dim);
          leds[74] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 25:
          leds[75] = CHSV(color, saturation, trans);
          leds[76] = CHSV(color, saturation, dim);
          leds[77] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 26:
          leds[78] = CHSV(color, saturation, trans);
          leds[79] = CHSV(color, saturation, dim);
          leds[80] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 27:
          leds[81] = CHSV(color, saturation, trans);
          leds[82] = CHSV(color, saturation, dim);
          leds[83] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 28:
          leds[84] = CHSV(color, saturation, trans);
          leds[85] = CHSV(color, saturation, dim);
          leds[86] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
        case 29:
          leds[87] = CHSV(color, saturation, trans);
          leds[88] = CHSV(color, saturation, dim);
          leds[89] = CHSV(color, saturation, trans);
          FastLED.show();
          break;
      }
  }
}