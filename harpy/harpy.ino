//https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
//https://arduinogetstarted.com/tutorials/arduino-limit-switch

#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN     7
#define NUM_LEDS    1

CRGB leds[NUM_LEDS];
ezButton limitSwitch(8);  // create ezButton object that attach to pin 8;
int state = 0;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  Serial.begin(115200); //Baud rate has to match Python
  limitSwitch.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
//  analogWrite(ANALOG_PIN, 200);
//  leds[0] = CRGB(255, 0, 0);
//  FastLED.show();
//  delay(500); 
//  leds[0] = CRGB(0, 255, 0);
//  FastLED.show();
//  delay(500);  
//  leds[0] = CRGB(0, 0, 255);
//  FastLED.show();
//  delay(500);
  limitSwitch.loop(); // MUST call the loop() function first
  state = limitSwitch.getState();

  
  //TODO: When at rest, shouldnt print note
  //NO. when open is 0, closed is 1. when is open, delay. then check if its closed.
  if(state == 1) {
    Serial.println("String is being pulled");
    if(state == 0) {
      Serial.println("C1"); // string returns to original position
    }
    else {
      Serial.println("Done");
    }
  }
}
