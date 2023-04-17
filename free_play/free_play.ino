#include <FastLED.h>
#include <ezButton.h>
#include <LinkedList.h>

//First octave
#define LED_PIN_C3    49
#define LED_PIN_D3    47
#define LED_PIN_E3    45
#define LED_PIN_F3    43
#define LED_PIN_G3    41
#define LED_PIN_A3    39
#define LED_PIN_B3    37

//Second octave
#define LED_PIN_C4    35
#define LED_PIN_D4    33
#define LED_PIN_E4    31
#define LED_PIN_F4    53
#define LED_PIN_G4    27
#define LED_PIN_A4    25
#define LED_PIN_B4    23

#define NUM_LEDS      26
 
//g4 led not working

//First octave
ezButton limitSwitchC3(48);  
ezButton limitSwitchD3(46);  
ezButton limitSwitchE3(44);
ezButton limitSwitchF3(42);  
ezButton limitSwitchG3(40);  
ezButton limitSwitchA3(38);  
ezButton limitSwitchB3(36); 

//Second octave
ezButton limitSwitchC4(34);  
ezButton limitSwitchD4(32);  
ezButton limitSwitchE4(30);
ezButton limitSwitchF4(28);  
ezButton limitSwitchG4(26);  
ezButton limitSwitchA4(24);  
ezButton limitSwitchB4(22);  

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

//Lists used to store string states
LinkedList<String> idleStrsList;
LinkedList<String> pulledStrsList;
LinkedList<String> releasedStrsList;

//Variables for making LEDs light up together
const unsigned long ledOnDuration = 500; //standard for all leds, can be varied in the future 
unsigned long timeNow = 0;

int numOfStrs = 14;
String allStrsArr[14] = {"C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4"}; 
int strsRGBArr[14][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211},
                        {255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}};

LinkedList<unsigned long> releasedStrTimesList;
LinkedList<int> strCountsList;

void setup() {
  Serial.begin(9600);
  
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

  //Populate idleStrsList with all strings.
  for(int i = 0; i < numOfStrs; i++) {
    idleStrsList.add(allStrsArr[i]);
  }

  //Populate releasedStrTimesList and strCountsList with all 0s.
  for(int i = 0; i < numOfStrs; i++) {
    releasedStrTimesList.add(0);
    strCountsList.add(0);
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

void removeSharedElemsFromList(LinkedList<int>& list1, LinkedList<int>& list2) {
//Remove elements in list 2 present in list 1, from list 1.
  for (int i = 0; i < list1.size(); i++) {
    for (int j = 0; j < list2.size(); j++) {
      if (list1.get(i) == list2.get(j)) {
        list1.remove(i); // remove element from list1
        i--; // update index to check next element in list
        break; // exit inner loop after removing element
      }
    }
  }
}

void checkIdleStrsList() {
  for(int index = 0; index < idleStrsList.size(); index++) {
    String idleStr = idleStrsList.get(index);
    int isStrPulled = get_limit_switch_state(idleStr); //returns 1 when pulled
    
    //If pulled, remove from idleStrsList, and add to pulledStrsList
    if(isStrPulled) {
      idleStrsList.remove(index);
      pulledStrsList.add(idleStr);
    }
  }
}

void checkPulledStrsList() {
  for(int index = 0; index < pulledStrsList.size(); index++) {
    String pulledStr = pulledStrsList.get(index);
    int isStrReleased = get_limit_switch_state(pulledStr); //returns 0 when pulled
    
    //If pulled, remove from pulledStrsList, and add to releasedStrsList
    if(!isStrReleased) {
      pulledStrsList.remove(index);
      releasedStrsList.add(pulledStr);
    }
  }
}

void checkReleasedStrsList() {
  for(int i = 0; i < releasedStrsList.size(); i++) {
    String releasedStr = releasedStrsList.get(i);
    
    idleStrsList.add(releasedStr);//append back to idleStrsList
    Serial.println(releasedStr); //Python will read and play note

    int strIndex = getIndexOfStr(releasedStr); //get index from allStrsArr
    releasedStrTimesList.set(strIndex, millis()); //set corresponding release time to current time
  }
  
  releasedStrsList.clear();
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

void turnOffAllLEDs() {
  turnOffSpecificLEDStrip(ledsC3);
  turnOffSpecificLEDStrip(ledsD3);
  turnOffSpecificLEDStrip(ledsE3);
  turnOffSpecificLEDStrip(ledsF3);
  turnOffSpecificLEDStrip(ledsG3);
  turnOffSpecificLEDStrip(ledsA3);
  turnOffSpecificLEDStrip(ledsB3);

  turnOffSpecificLEDStrip(ledsC4);
  turnOffSpecificLEDStrip(ledsD4);
  turnOffSpecificLEDStrip(ledsE4);
  turnOffSpecificLEDStrip(ledsF4);
  turnOffSpecificLEDStrip(ledsG4);
  turnOffSpecificLEDStrip(ledsA4);
  turnOffSpecificLEDStrip(ledsB4);
}

void ledsController() {
  //After string pull, turn on corresponding LED for 500ms
  timeNow = millis();

  //Loop through releasedStrTimesList
  for(int strIndex = 0; strIndex < numOfStrs; strIndex++) {
    unsigned long releasedStrTime = releasedStrTimesList.get(strIndex);
    if(releasedStrTime != 0) {
      int count = strCountsList.get(strIndex);
      unsigned long elapsedTime = millis() - releasedStrTime;

      //turn on leds 
      if(elapsedTime <= ledOnDuration && count == 0) {
        turnOnLEDStrip(strIndex);
        strCountsList.set(strIndex, 1);
      } //turn off leds after 500ms
      else if(elapsedTime > ledOnDuration) {
        turnOffLEDStrip(strIndex);
        strCountsList.set(strIndex, 0); //reset count to 0
        releasedStrTimesList.set(strIndex, 0); //reset time to 0
      } 
    }
  }
}

void loop() {
  //checkIdleStrsList if its not empty
  if(idleStrsList.size() != 0){
    checkIdleStrsList();
  }

  //checkPulledStrsList if its not empty
  if(pulledStrsList.size() != 0){
    checkPulledStrsList();
  }

  //checkReleasedStrsList if its not empty
  if(releasedStrsList.size() != 0){
    checkReleasedStrsList();
  }

  ledsController();
}
