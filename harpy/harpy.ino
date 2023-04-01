//https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
//https://arduinogetstarted.com/tutorials/arduino-limit-switch

#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN_1     4
#define LED_PIN_2     52
#define NUM_LEDS    1

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
ezButton limitSwitch1(13);  
ezButton limitSwitch2(12);  
ezButton limitSwitch3(11);
ezButton limitSwitch4(10);  
ezButton limitSwitch5(9);  
ezButton limitSwitch6(8);  
ezButton limitSwitch7(7);  
int switchesArr[] = {}; //List of switches

void setup() {
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  Serial.begin(9600); //Baud rate has to match Python
  limitSwitch1.setDebounceTime(50); // set debounce time to 50 milliseconds
  limitSwitch2.setDebounceTime(50); // set debounce time to 50 milliseconds
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
  Serial.println(state);
  
  if (state == 0){
        Serial.println("at rest");
  }
  else{
    while (state == 1){
        Serial.println("C");
        limitSwitch1.loop();
        state = limitSwitch1.getState();
    }
  //   delay(100);
  //   Serial.println("released");
  //   leds_1[0] = CRGB(255, 0, 0);
  //   FastLED.show();
  //   delay(250);
  //   leds_1[0] = CRGB(0, 0, 0);
  //   FastLED.show();
  //   delay(250);
  }
}

void detectString2Pull(){
  limitSwitch2.loop();
  int state = limitSwitch2.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("D");
        limitSwitch2.loop();
        state = limitSwitch2.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}

void detectString3Pull()  {
  limitSwitch3.loop();
  int state = limitSwitch3.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("E");
        limitSwitch3.loop();
        state = limitSwitch3.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}

void detectString4Pull()  {
  limitSwitch4.loop();
  int state = limitSwitch4.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("F");
        limitSwitch4.loop();
        state = limitSwitch4.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}

void detectString5Pull()  {
  limitSwitch5.loop();
  int state = limitSwitch5.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("G");
        limitSwitch5.loop();
        state = limitSwitch5.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}

void detectString6Pull()  {
  limitSwitch6.loop();
  int state = limitSwitch6.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("A");
        limitSwitch6.loop();
        state = limitSwitch6.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}

void detectString7Pull()  {
  limitSwitch7.loop();
  int state = limitSwitch7.getState();
  
  if (state == 0){
        Serial.println("at rest");
      }
  else{
      while (state == 1){
        Serial.println("B");
        limitSwitch7.loop();
        state = limitSwitch7.getState();
    }
    //   delay(100);
    //   Serial.println("released");
    //   leds_2[0] = CRGB(255, 0, 0);
    //   FastLED.show();
    //   delay(250);
    //   leds_2[0] = CRGB(0, 0, 0);
    //   FastLED.show();
    }
}
