#include <FastLED.h>
#include <ezButton.h>

//First octave
#define LED_PIN_C4    25
#define LED_PIN_D4    27
#define LED_PIN_E4    29
#define LED_PIN_F4    31
#define LED_PIN_G4    33
#define LED_PIN_A4    35
#define LED_PIN_B4    37

//Second octave
#define LED_PIN_C5    39
#define LED_PIN_D5    41
#define LED_PIN_E5    43
#define LED_PIN_F5    45
#define LED_PIN_G5    47
#define LED_PIN_A5    49
#define LED_PIN_B5    51

#define NUM_LEDS      26
#define NUM_DISPLAY_LEDS      26

//Display LEDs
#define DISPLAY_LED_PIN_1    2
#define DISPLAY_LED_PIN_2    3
#define DISPLAY_LED_PIN_3    4
#define DISPLAY_LED_PIN_4    5

//First octave
ezButton limitSwitchC4(24);  
ezButton limitSwitchD4(26);  
ezButton limitSwitchE4(28);
ezButton limitSwitchF4(30);  
ezButton limitSwitchG4(32);  
ezButton limitSwitchA4(34);  
ezButton limitSwitchB4(36); 

//Second octave
ezButton limitSwitchC5(38);  
ezButton limitSwitchD5(40);  
ezButton limitSwitchE5(42);
ezButton limitSwitchF5(44);  
ezButton limitSwitchG5(46);  
ezButton limitSwitchA5(48);  
ezButton limitSwitchB5(50);  

//First octave
CRGB ledsC4[NUM_LEDS];
CRGB ledsD4[NUM_LEDS];
CRGB ledsE4[NUM_LEDS];
CRGB ledsF4[NUM_LEDS];
CRGB ledsG4[NUM_LEDS];
CRGB ledsA4[NUM_LEDS];
CRGB ledsB4[NUM_LEDS];

//Second octave
CRGB ledsC5[NUM_LEDS];
CRGB ledsD5[NUM_LEDS];
CRGB ledsE5[NUM_LEDS];
CRGB ledsF5[NUM_LEDS];
CRGB ledsG5[NUM_LEDS];
CRGB ledsA5[NUM_LEDS];
CRGB ledsB5[NUM_LEDS];

//Display leds #REMEMBER TO CHANGE LED NUM
CRGB displayLEDs1[NUM_DISPLAY_LEDS];
CRGB displayLEDs2[NUM_DISPLAY_LEDS];
CRGB displayLEDs3[NUM_DISPLAY_LEDS];
CRGB displayLEDs4[NUM_DISPLAY_LEDS];

int numOfStrs = 14;
String allStrsArr[14] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "B5"}; 
int strsRGBArr[14][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211},
                        {255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}};

//D4 and E4 LED not hooked up
String notesArr[] = {"C5", "G5", "C5", "D5", "E5", "F5", "E5", "D5", "G4", "A4", "B4", "C5", "D5", "E5", "F5", "E5", "D5", "C5"};
int numOfNotes = 18;

int count = 0;

void setup() {
  Serial.begin(9600); //Baud rate has to match Python
  
  FastLED.addLeds<WS2812, LED_PIN_C4, GRB>(ledsC4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D4, GRB>(ledsD4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E4, GRB>(ledsE4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F4, GRB>(ledsF4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G4, GRB>(ledsG4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A4, GRB>(ledsA4, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B4, GRB>(ledsB4, NUM_LEDS);

  FastLED.addLeds<WS2812, LED_PIN_C5, GRB>(ledsC5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D5, GRB>(ledsD5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E5, GRB>(ledsE5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F5, GRB>(ledsF5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G5, GRB>(ledsG5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A5, GRB>(ledsA5, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B5, GRB>(ledsB5, NUM_LEDS);
  FastLED.setBrightness(255);

  //Display LEDs
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_1, GRB>(displayLEDs1, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_2, GRB>(displayLEDs2, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_3, GRB>(displayLEDs3, NUM_DISPLAY_LEDS);
  FastLED.addLeds<WS2812, DISPLAY_LED_PIN_4, GRB>(displayLEDs4, NUM_DISPLAY_LEDS);
  
  limitSwitchC4.setDebounceTime(50); 
  limitSwitchD4.setDebounceTime(50); 
  limitSwitchE4.setDebounceTime(50); 
  limitSwitchF4.setDebounceTime(50); 
  limitSwitchG4.setDebounceTime(50); 
  limitSwitchA4.setDebounceTime(50); 
  limitSwitchB4.setDebounceTime(50); 
  
  limitSwitchC5.setDebounceTime(50); 
  limitSwitchD5.setDebounceTime(50); 
  limitSwitchE5.setDebounceTime(50); 
  limitSwitchF5.setDebounceTime(50); 
  limitSwitchG5.setDebounceTime(50); 
  limitSwitchA5.setDebounceTime(50); 
  limitSwitchB5.setDebounceTime(50); 
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
  if (str == "C4") {
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

  } else if (str == "C5") {
    limitSwitchC5.loop();
    return limitSwitchC5.getState();
  } else if (str == "D5") {
    limitSwitchD5.loop();
    return limitSwitchD5.getState();
  } else if (str == "E5") {
    limitSwitchE5.loop();
    return limitSwitchE5.getState();
  } else if (str == "F5") {
    limitSwitchF5.loop();
    return limitSwitchF5.getState();
  } else if (str == "G5") {
    limitSwitchG5.loop();
    return limitSwitchG5.getState();
  } else if (str == "A5") {
    limitSwitchA5.loop();
    return limitSwitchA5.getState();
  } else if (str == "B5") {
    limitSwitchB5.loop();
    return limitSwitchB5.getState();
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
  if(str == "C4"){
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

  else if(str == "C5"){
    turnOnSpecificLEDStrip(ledsC5, rgbArr);
  } else if(str == "D5"){
    turnOnSpecificLEDStrip(ledsD5, rgbArr);
  } else if(str == "E5"){
    turnOnSpecificLEDStrip(ledsE5, rgbArr);
  } else if(str == "F5"){
    turnOnSpecificLEDStrip(ledsF5, rgbArr);
  } else if(str == "G5"){
    turnOnSpecificLEDStrip(ledsG5, rgbArr);
  } else if(str == "A5"){
    turnOnSpecificLEDStrip(ledsA5, rgbArr);
  } else if(str == "B5"){
    turnOnSpecificLEDStrip(ledsB5, rgbArr);
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
  if(str == "C4"){
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

  else if(str == "C5"){
    turnOffSpecificLEDStrip(ledsC5);
  } else if(str == "D5"){
    turnOffSpecificLEDStrip(ledsD5);
  } else if(str == "E5"){
    turnOffSpecificLEDStrip(ledsE5);
  } else if(str == "F5"){
    turnOffSpecificLEDStrip(ledsF5);
  } else if(str == "G5"){
    turnOffSpecificLEDStrip(ledsG5);
  } else if(str == "A5"){
    turnOffSpecificLEDStrip(ledsA5);
  } else if(str == "B5"){
    turnOffSpecificLEDStrip(ledsB5);
  }
}

void turnOffSpecificLEDStrip(CRGB leds[]) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void turnOffAllLEDs() {
  turnOffSpecificLEDStrip(ledsC4);
  turnOffSpecificLEDStrip(ledsD4);
  turnOffSpecificLEDStrip(ledsE4);
  turnOffSpecificLEDStrip(ledsF4);
  turnOffSpecificLEDStrip(ledsG4);
  turnOffSpecificLEDStrip(ledsA4);
  turnOffSpecificLEDStrip(ledsB4);

  turnOffSpecificLEDStrip(ledsC5);
  turnOffSpecificLEDStrip(ledsD5);
  turnOffSpecificLEDStrip(ledsE5);
  turnOffSpecificLEDStrip(ledsF5);
  turnOffSpecificLEDStrip(ledsG5);
  turnOffSpecificLEDStrip(ledsA5);
  turnOffSpecificLEDStrip(ledsB5);
}

void noteSynthesia(String str){
  int strIndex = getIndexOfStr(str);
  turnOnLEDStrip(strIndex);//turn on led for corresponding note
  
  waitForStringPluck(str);

  Serial.println(str);//play music
  turnOffLEDStrip(strIndex);//turn off led for corresponding note
}

void turnOnBottomLEDs(){
  int rgb[] = {255,127,0};
  turnOnSpecificLEDStrip(displayLEDs1, rgb);
  turnOnSpecificLEDStrip(displayLEDs2, rgb);
  turnOnSpecificLEDStrip(displayLEDs3, rgb);
  turnOnSpecificLEDStrip(displayLEDs4, rgb);  
}

void loop() {
  //Turn off all LEDs initially
  if(count == 0){
    turnOffAllLEDs();
    turnOnBottomLEDs();
    count = 1;
  }
  
  //loop through notesArr, basically your songsheet
  for(int i = 0; i < numOfNotes; i++){
    String note = notesArr[i];
    noteSynthesia(note);
  }
}

