#include <FastLED.h>

//Display LEDs
#define DISPLAY_LED_PIN_1    2
#define DISPLAY_LED_PIN_2    3
#define DISPLAY_LED_PIN_3    4
#define DISPLAY_LED_PIN_4    5

#define NUM_DISPLAY_LEDS      26

int count = 0;

//Display leds #REMEMBER TO CHANGE LED NUM
CRGB displayLEDs1[NUM_DISPLAY_LEDS];
CRGB displayLEDs2[NUM_DISPLAY_LEDS];
CRGB displayLEDs3[NUM_DISPLAY_LEDS];
CRGB displayLEDs4[NUM_DISPLAY_LEDS];

void setup() {
  //Display LEDs
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_1, GRB>(displayLEDs1, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_2, GRB>(displayLEDs2, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_3, GRB>(displayLEDs3, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_4, GRB>(displayLEDs4, NUM_DISPLAY_LEDS);

}

void turnOnTopLEDs(){
  int rgb[] = {255,127,0};
  turnOnSpecificLEDStrip(displayLEDs1, rgb);
  turnOnSpecificLEDStrip(displayLEDs2, rgb);
  turnOnSpecificLEDStrip(displayLEDs3, rgb);
  turnOnSpecificLEDStrip(displayLEDs4, rgb);  
}

void loop() {
  //Turn on display leds
  if(count == 0){
    turnOnTopLEDs();
    count = 1;
  }

}
