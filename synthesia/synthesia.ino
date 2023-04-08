//https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/
//https://arduinogetstarted.com/tutorials/arduino-limit-switch

#include <FastLED.h>
#include <ezButton.h>

#define LED_PIN_C    41
#define LED_PIN_D    43
#define LED_PIN_E    45
#define LED_PIN_F    47
#define LED_PIN_G    49
#define LED_PIN_A    51
#define LED_PIN_B    53
#define NUM_LEDS     26

CRGB ledsC[NUM_LEDS];
CRGB ledsD[NUM_LEDS];
CRGB ledsE[NUM_LEDS];
CRGB ledsF[NUM_LEDS];
CRGB ledsG[NUM_LEDS];
CRGB ledsA[NUM_LEDS];
CRGB ledsB[NUM_LEDS];

ezButton limitSwitch1(3);  
ezButton limitSwitch2(4);  
ezButton limitSwitch3(5);
ezButton limitSwitch4(7);  
ezButton limitSwitch5(9);  
ezButton limitSwitch6(11);  
ezButton limitSwitch7(13);  

//Containers
String allStrsArr[] = {"C", "D", "E", "F", "G", "A", "B"}; 
int numOfStrs = 7;
int strsRGBArr[7][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}};

//Songsheet
String notesArr[] = {"C", "C", "E", "F", "G", "A", "B"}; 
int numOfNotes = 7; //update when notesArr is different

void setup() {
  Serial.begin(9600); //Baud rate has to match Python
  
  FastLED.addLeds<WS2812, LED_PIN_C, GRB>(ledsC, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D, GRB>(ledsD, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E, GRB>(ledsE, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F, GRB>(ledsF, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G, GRB>(ledsG, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A, GRB>(ledsA, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B, GRB>(ledsB, NUM_LEDS);
  FastLED.setBrightness(255);
  
  limitSwitch1.setDebounceTime(50); 
  limitSwitch2.setDebounceTime(50); 
  limitSwitch3.setDebounceTime(50); 
  limitSwitch4.setDebounceTime(50); 
  limitSwitch5.setDebounceTime(50); 
  limitSwitch6.setDebounceTime(50); 
  limitSwitch7.setDebounceTime(50); 
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
  if (str == "C") {
    limitSwitch1.loop();
    return limitSwitch1.getState();
  } else if (str == "D") {
    limitSwitch2.loop();
    return limitSwitch2.getState();
  } else if (str == "E") {
    limitSwitch3.loop();
    return limitSwitch3.getState();
  } else if (str == "F") {
    limitSwitch4.loop();
    return limitSwitch4.getState();
  } else if (str == "G") {
    limitSwitch5.loop();
    return limitSwitch5.getState();
  } else if (str == "A") {
    limitSwitch6.loop();
    return limitSwitch6.getState();
  } else if (str == "B") {
    limitSwitch7.loop();
    return limitSwitch7.getState();
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
  if(str == "C"){
    turnOnSpecificLEDStrip(ledsC, rgbArr);
  } else if(str == "D"){
    turnOnSpecificLEDStrip(ledsD, rgbArr);
  } else if(str == "E"){
    turnOnSpecificLEDStrip(ledsE, rgbArr);
  } else if(str == "F"){
    turnOnSpecificLEDStrip(ledsF, rgbArr);
  } else if(str == "G"){
    turnOnSpecificLEDStrip(ledsG, rgbArr);
  } else if(str == "A"){
    turnOnSpecificLEDStrip(ledsA, rgbArr);
  } else if(str == "B"){
    turnOnSpecificLEDStrip(ledsB, rgbArr);
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
  if(str == "C"){
    turnOffSpecificLEDStrip(ledsC);
  } else if(str == "D"){
    turnOffSpecificLEDStrip(ledsD);
  } else if(str == "E"){
    turnOffSpecificLEDStrip(ledsE);
  } else if(str == "F"){
    turnOffSpecificLEDStrip(ledsF);
  } else if(str == "G"){
    turnOffSpecificLEDStrip(ledsG);
  } else if(str == "A"){
    turnOffSpecificLEDStrip(ledsA);
  } else if(str == "B"){
    turnOffSpecificLEDStrip(ledsB);
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

