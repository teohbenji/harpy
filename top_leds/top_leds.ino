#include <FastLED.h>

//Display LEDs
#define LED_PIN    2
#define NUM_LEDS   26

CRGB leds[NUM_LEDS];

void setup() {
  //Display LEDs
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  turnOnTopLEDs();
}

void turnOnSpecificLEDStrip(CRGB leds[], int rgb[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  FastLED.show();
}

void turnOnTopLEDs(){
  int rgb[] = {255,127,0};
  turnOnSpecificLEDStrip(leds, rgb);
}

void loop() {
}
