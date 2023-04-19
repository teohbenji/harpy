#include <FastLED.h>

//Display LEDs
#define LED_PIN    2
#define NUM_LEDS   240

CRGB leds[NUM_LEDS];

void setup() {
  //Display LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
}
