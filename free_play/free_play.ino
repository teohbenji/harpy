#include <FastLED.h>
#include <ezButton.h>
#include <LinkedList.h>

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

//Lists used to store string states
LinkedList<String> idleStrsList;
LinkedList<String> pulledStrsList;
LinkedList<String> releasedStrsList;

//Variables for making LEDs light up together
const unsigned long ledOnDuration = 500; //standard for all leds, can be varied in the future 
unsigned long timeNow = 0;
int numOfStrs = 7;

String allStrsArr[] = {"C", "D", "E", "F", "G", "A", "B"}; 
//update first index when numOfStrs changes
int strsRGBArr[7][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}}; 
LinkedList<unsigned long> releasedStrTimesList;
LinkedList<int> strCountsList;

void setup() {
  Serial.begin(9600);
  //Limit switches setup
  limitSwitch1.setDebounceTime(50);
  limitSwitch2.setDebounceTime(50);
  limitSwitch3.setDebounceTime(50);
  limitSwitch4.setDebounceTime(50);
  limitSwitch5.setDebounceTime(50);
  limitSwitch6.setDebounceTime(50);
  limitSwitch7.setDebounceTime(50);

  //Leds setup
  FastLED.addLeds<WS2812, LED_PIN_C, GRB>(ledsC, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_D, GRB>(ledsD, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_E, GRB>(ledsE, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_F, GRB>(ledsF, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_G, GRB>(ledsG, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_A, GRB>(ledsA, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_B, GRB>(ledsB, NUM_LEDS);
  FastLED.setBrightness(122);

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
  // //checkIdleStrsList if its not empty
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
