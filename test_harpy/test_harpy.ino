#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN     3
#define NUM_LEDS    240

CRGB leds[NUM_LEDS];
ezButton limitSwitch(13);

void setup(){
  Serial.begin(9600);
  limitSwitch.setDebounceTime(50);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(5);

  pinMode(A0, OUTPUT);
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

void turnOnLEDStrip(CRGB leds[]) {
  int rgb[] = {255, 0, 0};
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
}

void rainbowLEDStrip(CRGB leds[]) {
  int rgb[] = {255, 0, 0};
  testblinkLedStrip(leds, rgb);
  int rgb2[] = {255, 165, 0};
  testblinkLedStrip(leds, rgb2);
  int rgb3[] = {255, 255, 0};
  testblinkLedStrip(leds, rgb3);
  int rgb4[] = {0, 128, 0};
  testblinkLedStrip(leds, rgb4);
  int rgb5[] = {0, 0, 255};
  testblinkLedStrip(leds, rgb5);
  int rgb6[] = {75, 0, 130};
  testblinkLedStrip(leds, rgb6);
  int rgb7[] = {238, 130, 238};
  testblinkLedStrip(leds, rgb7);
}

void loop(){ 
  // // analogWrite(A0, 255);
  // rainbowLEDStrip(leds);
  // // test_switch();
  // turnOnLEDStrip(leds);
  int rgb1[] = {253, 244, 220};
  int rgb2[] = {243, 231, 211};
  int rgb3[] = {250, 235, 215};
  int rgb4[] = {255, 239, 213};
  int rgb5[] = {255, 235, 205};
  int count = 0;

  if(count == 0) {
    //turns on LED for 0.25s
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(rgb1[0], rgb1[1], rgb1[2]);
    }
    FastLED.show();
    count = 1;
  }
  
  
}

