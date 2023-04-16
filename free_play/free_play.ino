#include <FastLED.h>
#include <ezButton.h>
#include <LinkedList.h>

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

CRGB ledsC4[NUM_LEDS];
CRGB ledsD4[NUM_LEDS];
CRGB ledsE4[NUM_LEDS];
CRGB ledsF4[NUM_LEDS];
CRGB ledsG4[NUM_LEDS];
CRGB ledsA4[NUM_LEDS];
CRGB ledsB4[NUM_LEDS];

CRGB ledsC5[NUM_LEDS];
CRGB ledsD5[NUM_LEDS];
CRGB ledsE5[NUM_LEDS];
CRGB ledsF5[NUM_LEDS];
CRGB ledsG5[NUM_LEDS];
CRGB ledsA5[NUM_LEDS];
CRGB ledsB5[NUM_LEDS];

//Lists used to store string states
LinkedList<String> idleStrsList;
LinkedList<String> pulledStrsList;
LinkedList<String> releasedStrsList;

//Variables for making LEDs light up together
const unsigned long ledOnDuration = 500; //standard for all leds, can be varied in the future 
unsigned long timeNow = 0;

int numOfStrs = 14;
String allStrsArr[14] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "C5", "D5", "E5", "F5", "G5", "A5", "B5"}; 
int strsRGBArr[14][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211},
                        {255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}};

LinkedList<unsigned long> releasedStrTimesList;
LinkedList<int> strCountsList;

int count = 0;

void setup() {
  Serial.begin(9600);
  
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
    turnOffSpecificLEDStrip(ledsC4, rgbArr);
  } else if(str == "D4"){
    turnOffSpecificLEDStrip(ledsD4, rgbArr);
  } else if(str == "E4"){
    turnOffSpecificLEDStrip(ledsE4, rgbArr);
  } else if(str == "F4"){
    turnOffSpecificLEDStrip(ledsF4, rgbArr);
  } else if(str == "G4"){
    turnOffSpecificLEDStrip(ledsG4, rgbArr);
  } else if(str == "A4"){
    turnOffSpecificLEDStrip(ledsA4, rgbArr);
  } else if(str == "B4"){
    turnOffSpecificLEDStrip(ledsB4, rgbArr);
  }

  else if(str == "C5"){
    turnOffSpecificLEDStrip(ledsC5, rgbArr);
  } else if(str == "D5"){
    turnOffSpecificLEDStrip(ledsD5, rgbArr);
  } else if(str == "E5"){
    turnOffSpecificLEDStrip(ledsE5, rgbArr);
  } else if(str == "F5"){
    turnOffSpecificLEDStrip(ledsF5, rgbArr);
  } else if(str == "G5"){
    turnOnSpecificLEDStrip(ledsG5, rgbArr);
  } else if(str == "A5"){
    turnOffSpecificLEDStrip(ledsA5, rgbArr);
  } else if(str == "B5"){
    turnOffSpecificLEDStrip(ledsB5, rgbArr);
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
  //Turn off all LEDs initially
  if(count == 0){
    turnOffAllLEDs();
    count = 1;
  }

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
