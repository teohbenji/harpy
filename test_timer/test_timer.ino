//https://roboticsbackend.com/arduino-delay/#Code_example_-_Arduino_delay_without_delay

#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN_1    12
#define NUM_LEDS     26

CRGB leds_1[NUM_LEDS];

ezButton limitSwitch1(13); 

unsigned long releasedStr1Time = 0;
unsigned long ledOnDuration = 500; //500ms

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.setBrightness(122);

  limitSwitch1.setDebounceTime(50);
}

void turnOnLEDStrip(CRGB leds[], int rgb[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  FastLED.show();
}

void turnOffLEDStrip(CRGB leds[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}


void detectString1Pull(){ 
  limitSwitch1.loop();
  int state = limitSwitch1.getState();
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      limitSwitch1.loop();
      state = limitSwitch1.getState();
    }
    //on switch release, set released1Time to current time
    releasedStr1Time = millis();
  }
}


void loop() {
  detectString1Pull();
  unsigned long timeNow = millis();
  if((releasedStr1Time != 0)) {
    unsigned long elaspedTime = timeNow - releasedStr1Time;
    int count = 0;
    //turn on LED on first loop, subsequently dont do anything until time elapsed > ledOnDuration
    if((timeNow - releasedStr1Time <= ledOnDuration) && count == 0) {
      int rgb[] = {0, 255, 0};
      turnOnLEDStrip(leds_1, rgb);
    } else if(timeNow - releasedStr1Time > ledOnDuration) {
      //turn off LED strip and reset releasedStrTime
      turnOffLEDStrip(leds_1);
      releasedStr1Time = 0;
    } 
  }
}

