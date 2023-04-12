#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN_C3    25
#define LED_PIN_D3    27
#define LED_PIN_E3    29
#define LED_PIN_F3    31
#define LED_PIN_G3    33
#define LED_PIN_A3    35
#define LED_PIN_B3    39

#define LED_PIN_C4    41
#define LED_PIN_D4    43
#define LED_PIN_E4    45
#define LED_PIN_F4    47
#define LED_PIN_G4    49
#define LED_PIN_A4    51
#define LED_PIN_B4    53
#define NUM_LEDS      26

CRGB ledsC3[NUM_LEDS];
CRGB ledsD3[NUM_LEDS];
CRGB ledsE3[NUM_LEDS];
CRGB ledsF3[NUM_LEDS];
CRGB ledsG3[NUM_LEDS];
CRGB ledsA3[NUM_LEDS];
CRGB ledsB3[NUM_LEDS];

CRGB ledsC4[NUM_LEDS];
CRGB ledsD4[NUM_LEDS];
CRGB ledsE4[NUM_LEDS];
CRGB ledsF4[NUM_LEDS];
CRGB ledsG4[NUM_LEDS];
CRGB ledsA4[NUM_LEDS];
CRGB ledsB4[NUM_LEDS];

ezButton limitSwitchC3(26);  
ezButton limitSwitchD3(28);  
ezButton limitSwitchE3(30);
ezButton limitSwitchF3(32);  
ezButton limitSwitchG3(34);  
ezButton limitSwitchA3(36);  
ezButton limitSwitchB3(38); 

ezButton limitSwitchC4(40);  
ezButton limitSwitchD4(42);  
ezButton limitSwitchE4(44);
ezButton limitSwitchF4(46);  
ezButton limitSwitchG4(48);  
ezButton limitSwitchA4(50);  
ezButton limitSwitchB4(52);  

int numOfStrs = 14;
String allStrsArr[14] = {"C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4"}; 
int strsRGBArr[14][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211},
                    {0,49,150}, {176,100,220}, {220,100,130}, {237,28,36}, {241,90,36}, {250,230,0}, {0,148,68}};

//D4 and E4 LED not hooked up
String notesArr[] = {"F4", "G4", "A4", "F4", "A4", "F4", "A4", "G4", "A4", "B4", "B4", "A4", "G4", "B4"};
int numOfNotes = 14;

void setup() {
  Serial.begin(9600); //Baud rate has to match Python
  
  FastLED.addLeds<WS2812, LED_PIN_C3, GRB>(ledsC3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D3, GRB>(ledsD3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E3, GRB>(ledsE3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F3, GRB>(ledsF3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G3, GRB>(ledsG3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A3, GRB>(ledsA3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B3, GRB>(ledsB3, NUM_LEDS);

  FastLED.addLeds<WS2812, LED_PIN_C4, GRB>(ledsC4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D4, GRB>(ledsD4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E4, GRB>(ledsE4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F4, GRB>(ledsF4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G4, GRB>(ledsG4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A4, GRB>(ledsA4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B4, GRB>(ledsB4, NUM_LEDS);
  FastLED.setBrightness(255);
  
  limitSwitchC3.setDebounceTime(50); 
  limitSwitchD3.setDebounceTime(50); 
  limitSwitchE3.setDebounceTime(50); 
  limitSwitchF3.setDebounceTime(50); 
  limitSwitchG3.setDebounceTime(50); 
  limitSwitchA3.setDebounceTime(50); 
  limitSwitchB3.setDebounceTime(50); 
  
  limitSwitchC4.setDebounceTime(50); 
  limitSwitchD4.setDebounceTime(50); 
  limitSwitchE4.setDebounceTime(50); 
  limitSwitchF4.setDebounceTime(50); 
  limitSwitchG4.setDebounceTime(50); 
  limitSwitchA4.setDebounceTime(50); 
  limitSwitchB4.setDebounceTime(50); 
}

void checkStringState(String str, String stateToCheck){
  //At rest/released, state 0. Pulled, state 1.
  int state = get_limit_switch_state(str);
  int x = (stateToCheck == "pulled") ? 1 : 0;  
  while(state != x) {
    state = get_limit_switch_state(str);
  }
}

int get_limit_switch_state(String str) {
  if (str == "C3") {
    limitSwitchC3.loop();
    return limitSwitchC3.getState();
  } else if (str == "D3") {
    limitSwitchD3.loop();
    return limitSwitchD3.getState();
  } else if (str == "E3") {
    limitSwitchE3.loop();
    return limitSwitchE3.getState();
  } else if (str == "F3") {
    limitSwitchF3.loop();
    return limitSwitchF3.getState();
  } else if (str == "G3") {
    limitSwitchG3.loop();
    return limitSwitchG3.getState();
  } else if (str == "A3") {
    limitSwitchA3.loop();
    return limitSwitchA3.getState();
  } else if (str == "B3") {
    limitSwitchB3.loop();
    return limitSwitchB3.getState();

  } else if (str == "C4") {
    limitSwitchC4.loop();
    return limitSwitchC4.getState();
  } else if (str == "D4") {
    limitSwitchD4.loop();
    return limitSwitchD4.getState();
  } else if (str == "E4") {
    limitSwitchE4.loop();
    return limitSwitchE4.getState();
  } else if (str == "F4") {
    limitSwitchF4.loop();
    return limitSwitchF4.getState();
  } else if (str == "G4") {
    limitSwitchG4.loop();
    return limitSwitchG4.getState();
  } else if (str == "A4") {
    limitSwitchA4.loop();
    return limitSwitchA4.getState();
  } else if (str == "B4") {
    limitSwitchB4.loop();
    return limitSwitchB4.getState();
  }
}

void waitForStringPluck(String str){
  //Initially, string should be at rest(state 0)
  checkStringState(str, "rest");

  //wait for string to be pulled(state 1)
  checkStringState(str, "pulled");

  //wait for string to be released(state 0)
  checkStringState(str, "released");
}

int getIndexOfStr(String str) {
  for(int i = 0; i < numOfStrs; i++) {
    if(str == allStrsArr[i]) {
      return i;
    }
  }
} 

void turnOnLEDStrip(int strIndex) {
  String str = allStrsArr[strIndex];
  int rgbArr = strsRGBArr[strIndex];

  //turnonSpecificLEDStrip based on str name
  if(str == "C3"){
    turnOnSpecificLEDStrip(ledsC3, rgbArr);
  } else if(str == "D3"){
    turnOnSpecificLEDStrip(ledsD3, rgbArr);
  } else if(str == "E3"){
    turnOnSpecificLEDStrip(ledsE3, rgbArr);
  } else if(str == "F3"){
    turnOnSpecificLEDStrip(ledsF3, rgbArr);
  } else if(str == "G3"){
    turnOnSpecificLEDStrip(ledsG3, rgbArr);
  } else if(str == "A3"){
    turnOnSpecificLEDStrip(ledsA3, rgbArr);
  } else if(str == "B3"){
    turnOnSpecificLEDStrip(ledsB3, rgbArr);

  } else if(str == "C4"){
    turnOnSpecificLEDStrip(ledsC4, rgbArr);
  } else if(str == "D4"){
    turnOnSpecificLEDStrip(ledsD4, rgbArr);
  } else if(str == "E4"){
    turnOnSpecificLEDStrip(ledsE4, rgbArr);
  } else if(str == "F4"){
    turnOnSpecificLEDStrip(ledsF4, rgbArr);
  } else if(str == "G4"){
    turnOnSpecificLEDStrip(ledsG4, rgbArr);
  } else if(str == "A4"){
    turnOnSpecificLEDStrip(ledsA4, rgbArr);
  } else if(str == "B4"){
    turnOnSpecificLEDStrip(ledsB4, rgbArr);
  }
}

void turnOnSpecificLEDStrip(CRGB leds[], int rgb[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  FastLED.show();
}

void turnOffLEDStrip(int strIndex) {
  String str = allStrsArr[strIndex];
  int rgbArr = strsRGBArr[strIndex];

  //turnoffSpecificLEDStrip based on str name
  if(str == "C3"){
    turnOffSpecificLEDStrip(ledsC3);
  } else if(str == "D3"){
    turnOffSpecificLEDStrip(ledsD3);
  } else if(str == "E3"){
    turnOffSpecificLEDStrip(ledsE3);
  } else if(str == "F3"){
    turnOffSpecificLEDStrip(ledsF3);
  } else if(str == "G3"){
    turnOffSpecificLEDStrip(ledsG3);
  } else if(str == "A3"){
    turnOffSpecificLEDStrip(ledsA3);
  } else if(str == "B3"){
    turnOffSpecificLEDStrip(ledsB3);

  } else if(str == "C4"){
    turnOffSpecificLEDStrip(ledsC4);
  } else if(str == "D4"){
    turnOffSpecificLEDStrip(ledsD4);
  } else if(str == "E4"){
    turnOffSpecificLEDStrip(ledsE4);
  } else if(str == "F4"){
    turnOffSpecificLEDStrip(ledsF4);
  } else if(str == "G4"){
    turnOffSpecificLEDStrip(ledsG4);
  } else if(str == "A4"){
    turnOffSpecificLEDStrip(ledsA4);
  } else if(str == "B4"){
    turnOffSpecificLEDStrip(ledsB4);
  }
}

void turnOffSpecificLEDStrip(CRGB leds[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void noteSynthesia(String str){
  int strIndex = getIndexOfStr(str);
  turnOnLEDStrip(strIndex);//turn on led for corresponding note
  
  waitForStringPluck(str);

  Serial.println(str);//play music
  turnOffLEDStrip(strIndex);//turn off led for corresponding note
}

void loop() {
  //loop through notesArr, basically your songsheet
  for(int i = 0; i < numOfNotes; i++){
    String note = notesArr[i];
    noteSynthesia(note);
  }
}

