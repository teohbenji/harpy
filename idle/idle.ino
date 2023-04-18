// SONGPLAY MODE:
// loop through notes array
// - Play sound
// - Light up corresponding LED for 500ms
// - Turn off corresponding LED for 500ms
// - small delay

#include <FastLED.h>
#include <ezButton.h>

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
#define LED_PIN_F4    29
#define LED_PIN_G4    27
#define LED_PIN_A4    52
#define LED_PIN_B4    23

#define NUM_LEDS 26

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

int numOfStrs = 14;
String allStrsArr[14] = { "C3", "D3", "E3", "F3", "G3", "A3", "B3", "C4", "D4", "E4", "F4", "G4", "A4", "B4" };
int strsRGBArr[14][3]= {{255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211},
                        {255,0,0}, {255,127,0}, {255,255,0}, {0,255,0}, {0,0,255}, {75,0,130}, {148,0,211}};

// //Songsheet for super mario bros
String notesArr[] = { "E4", "E4", "E4", "C4", "E4", "G4", "G1", "C4", "G3", "E3", "A3", "B3", "B3b", "A3", "G3", "E4", "G4", "A4", "F4", "G4",
                      "G3", "E3", "A3", "B3", "B3b", "A3", "G3", "E4", "G4", "A4", "F4", "G4", "E4", "C4", "D4", "B3", "E4", "C4", "D4", "B3", "C4",
                      "G4", "F4#", "F4", "E4b", "E4", "G3#", "A3", "C4", "A3", "C4", "A3", "D4", "G4", "F4#", "F4", "E4b", "E4", "C5+F4", "C5+F4", "C5+F4" };
int numOfNotes = 61;  //update when notesArr is different

void setup() {
  Serial.begin(1000000);  //Baud rate has to match Python

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

  turnOffAllLEDs();
}

int getIndexOfStr(String str) {
  for (int i = 0; i < numOfStrs; i++) {
    if (str == allStrsArr[i]) {
      return i;
    }
  }
}

void turnOnLEDStrip(int strIndex) {
  String str = allStrsArr[strIndex];
  int rgbArr = strsRGBArr[strIndex];

  //turnonSpecificLEDStrip based on str name
  if (str == "C3") {
    turnOnSpecificLEDStrip(ledsC3, rgbArr);
  } else if (str == "D3") {
    turnOnSpecificLEDStrip(ledsD3, rgbArr);
  } else if (str == "E3") {
    turnOnSpecificLEDStrip(ledsE3, rgbArr);
  } else if (str == "F3") {
    turnOnSpecificLEDStrip(ledsF3, rgbArr);
  } else if (str == "G3") {
    turnOnSpecificLEDStrip(ledsG3, rgbArr);
  } else if (str == "A3") {
    turnOnSpecificLEDStrip(ledsA3, rgbArr);
  } else if (str == "B3" or str == "B3b") {
    turnOnSpecificLEDStrip(ledsB3, rgbArr);
  } else if (str == "C4" or str == "C5") {
    turnOnSpecificLEDStrip(ledsC4, rgbArr);
  } else if (str == "D4") {
    turnOnSpecificLEDStrip(ledsD4, rgbArr);
  } else if (str == "E4" or str == "E4b") {
    turnOnSpecificLEDStrip(ledsE4, rgbArr);
  } else if (str == "F4" or str == "F4#") {
    turnOnSpecificLEDStrip(ledsF4, rgbArr);
  } else if (str == "G4") {
    turnOnSpecificLEDStrip(ledsG4, rgbArr);
  } else if (str == "A4") {
    turnOnSpecificLEDStrip(ledsA4, rgbArr);
  } else if (str == "B4") {
    turnOnSpecificLEDStrip(ledsB4, rgbArr);
  }
}

void turnOnSpecificLEDStrip(CRGB leds[], int rgb[]) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(rgb[0], rgb[1], rgb[2]);
  }
  FastLED.show();
}

void turnOffLEDStrip(int strIndex) {
  String str = allStrsArr[strIndex];
  int rgbArr = strsRGBArr[strIndex];

  //turnoffSpecificLEDStrip based on str name
  if (str == "C3") {
    turnOffSpecificLEDStrip(ledsC3);
  } else if (str == "D3") {
    turnOffSpecificLEDStrip(ledsD3);
  } else if (str == "E3") {
    turnOffSpecificLEDStrip(ledsE3);
  } else if (str == "F3") {
    turnOffSpecificLEDStrip(ledsF3);
  } else if (str == "G3") {
    turnOffSpecificLEDStrip(ledsG3);
  } else if (str == "A3") {
    turnOffSpecificLEDStrip(ledsA3);
  } else if (str == "B3" or str == "B3b") {
    turnOffSpecificLEDStrip(ledsB3);
  } else if (str == "C4" or str == "C5") {
    turnOffSpecificLEDStrip(ledsC4);
  } else if (str == "D4") {
    turnOffSpecificLEDStrip(ledsD4);
  } else if (str == "E4" or str == "E4b") {
    turnOffSpecificLEDStrip(ledsE4);
  } else if (str == "F4" or str == "F4#") {
    turnOffSpecificLEDStrip(ledsF4);
  } else if (str == "G4") {
    turnOffSpecificLEDStrip(ledsG4);
  } else if (str == "A4") {
    turnOffSpecificLEDStrip(ledsA4);
  } else if (str == "B4") {
    turnOffSpecificLEDStrip(ledsB4);
  }
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

void turnOffSpecificLEDStrip(CRGB leds[]) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void playNote(String str) {
  int strIndex = getIndexOfStr(str);
  Serial.println(str);  //play music
  turnOnLEDStrip(strIndex);   
  delay(200);                 //note length
  turnOffLEDStrip(strIndex);  
}

void playChord() {
  Serial.println("C5+F4");  //play music
}

//turn on C4 and F4 together
void turnOnLEDStrips(){
  int c4Index = getIndexOfStr("C4");
  int f4Index = getIndexOfStr("F4");
  int c4RGB[] = {255,0,0};
  int f4RGB[] = {0,255,0};

  for (int i = 0; i < NUM_LEDS; i++) {
    ledsC4[i] = CRGB(c4RGB[0], c4RGB[1], c4RGB[2]);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    ledsF4[i] = CRGB(f4RGB[0], f4RGB[1], f4RGB[2]);
  }

  FastLED.show();
}

//turn off C4 and F4 together
void turnOffLEDStrips(){
  for (int i = 0; i < NUM_LEDS; i++) {
    ledsC4[i] = CRGB(0, 0, 0);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    ledsF4[i] = CRGB(0, 0, 0);
  }

  FastLED.show();
}

void loop() {
  delay(5000); // time to run python program
  unsigned long x = millis();
  Serial.println("===========Program starts===========");
  //loop through notesArr, basically your songsheet
  for (int i = 0; i < numOfNotes; i++) {
    String note = notesArr[i];

    if(note == "C5+F4") {
      playChord();
      if(i == numOfNotes - 2) {
        turnOnLEDStrips();
      }
      delay(200);
    } else {
      playNote(note); //If single note
    }
    Serial.println(millis() - x);
  }
  turnOffLEDStrips();
}  
