//https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
//https://arduinogetstarted.com/tutorials/arduino-limit-switch

#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN_7    2
#define NUM_LEDS    26

CRGB leds_7[NUM_LEDS];

ezButton limitSwitch1(13);  
ezButton limitSwitch2(11);  
ezButton limitSwitch3(9);
ezButton limitSwitch4(7);  
ezButton limitSwitch5(5);  
ezButton limitSwitch6(3);  
ezButton limitSwitch7(4);  

void setup() {
  Serial.begin(9600); //Baud rate has to match Python
  
  FastLED.addLeds<WS2812, LED_PIN_7, GRB>(leds_7, NUM_LEDS);
  FastLED.setBrightness(122);
  
  limitSwitch1.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch2.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch3.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch4.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch5.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch6.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch7.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void loop() {
  detectString1Pull();
  detectString2Pull();
  detectString3Pull();
  detectString4Pull();
  detectString5Pull();
  detectString6Pull();
  detectString7Pull();
}

void detectString1Pull(){
  limitSwitch1.loop();
  int state = limitSwitch1.getState();
  int rgb[] = {0, 0, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("C");
      limitSwitch1.loop();
      state = limitSwitch1.getState();
    }
    // blinkLedStrip(leds_1, rgb);
  }
}

void detectString2Pull(){
  limitSwitch2.loop();
  int state = limitSwitch2.getState();
  int rgb[] = {0, 0, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("D");
      limitSwitch2.loop();
      state = limitSwitch2.getState();
    }
    // blinkLedStrip(leds_2, rgb);
  }
}

void detectString3Pull()  {
  limitSwitch3.loop();
  int state = limitSwitch3.getState();
  int rgb[] = {0, 0, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("E");
      limitSwitch3.loop();
      state = limitSwitch3.getState();
    }
    // blinkLedStrip(leds_3, rgb);
  }
}

void detectString4Pull()  {
  limitSwitch4.loop();
  int state = limitSwitch4.getState();
  int rgb[] = {0, 0, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("F");
      limitSwitch4.loop();
      state = limitSwitch4.getState();
    }
    // blinkLedStrip(leds_4, rgb);
  }
}

void detectString5Pull()  {
  limitSwitch5.loop();
  int state = limitSwitch5.getState();
  int rgb[] = {0, 0, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("G");
      limitSwitch5.loop();
      state = limitSwitch5.getState();
    }
    // blinkLedStrip(leds_5, rgb);
  }
}

void detectString6Pull() {
  limitSwitch6.loop();
  int state = limitSwitch6.getState();
  int rgb[] = {246, 190, 0};
  
  if(state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("A");
      limitSwitch6.loop();
      state = limitSwitch6.getState();
    }
    // blinkLedStrip(leds_6, rgb);
  }
}

void detectString7Pull() {
  limitSwitch7.loop();
  int state = limitSwitch7.getState();
  int rgb[] = {1, 50, 32};
  
  if (state == 0) {
        Serial.println("at rest");
      }
  else {
    while(state == 1) {
      Serial.println("B");
      limitSwitch7.loop();
      state = limitSwitch7.getState();
    }
    blinkLedStrip(leds_7, rgb);
  }
}

void blinkLedStrip(CRGB leds[], int rgb[]) {
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
