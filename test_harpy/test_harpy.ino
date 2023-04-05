#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN     2
#define NUM_LEDS    26

CRGB leds[NUM_LEDS];
ezButton limitSwitch(13);

void setup(){
  Serial.begin(9600);
  limitSwitch.setDebounceTime(50);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(122);
}

void loop(){
  int rgb[] = {255, 0, 0};
  testblinkLedStrip(leds, rgb);
  // test_switch();
}

void test_switch() {
   limitSwitch.loop(); // MUST call the loop() function first
  
  if (limitSwitch.getState() == 0){
    Serial.println("untouched");
  }
  else{
    while (limitSwitch.getState() == 1){
        limitSwitch.loop();
        Serial.println("touched");
    }
    Serial.println();
    Serial.println("-------------------------released-------------------------");
    delay(5000);
  }
}

void testblinkLedStrip(CRGB leds[], int rgb[]) {
  //turns on LED for 0.25s
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  FastLED.show();
  delay(500);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  delay(500);
}
