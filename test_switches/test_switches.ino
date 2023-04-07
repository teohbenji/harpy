#include <ezButton.h>
#include <LinkedList.h> // include the LinkedList library

ezButton limitSwitch1(13);
ezButton limitSwitch2(11);
ezButton limitSwitch3(9);

//Variables used for computation
LinkedList<int> idleStrsList = LinkedList<int>();
LinkedList<int> pulledStrsList = LinkedList<int>();
LinkedList<int> releasedStrsList = LinkedList<int>();

void setup() {
  Serial.begin(9600);

  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A4, OUTPUT);

  limitSwitch1.setDebounceTime(50);
  limitSwitch2.setDebounceTime(50);
  limitSwitch3.setDebounceTime(50);

  int numOfSwitches = 3;
  //Populate idleStrsList with all switches.
  for(int i = 1; i < numOfSwitches + 1; i++){
    idleStrsList.add(i);
  }
}

int get_limit_switch_state(int switchNum) {
  switch(switchNum) {
    case 1:
      limitSwitch1.loop();
      return limitSwitch1.getState();
    case 2:
      limitSwitch2.loop();
      return limitSwitch2.getState();
    case 3:
      limitSwitch3.loop();
      return limitSwitch3.getState();
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

void checkIdleStrsList(){
  for(int index = 0; index < idleStrsList.size(); index++) {
    int idleStrNum = idleStrsList.get(index);
    int isStrPulled = get_limit_switch_state(idleStrNum); //returns 1 when pulled
    
    //If pulled, remove from idleStrsList, and add to pulledStrsList
    if(isStrPulled) {
      idleStrsList.remove(index);
      pulledStrsList.add(idleStrNum);
      //if pulled, turn on corresponding LED
      if(idleStrNum == 1) {
        analogWrite(A0, 255);
      } else if(idleStrNum == 2) {
        analogWrite(A2, 255);
      } else {
        analogWrite(A4, 255);
      }
    }
  }
}

void checkPulledStrsList(){
  for(int index = 0; index < pulledStrsList.size(); index++) {
    int pulledStrNum = pulledStrsList.get(index);
    int isStrReleased = get_limit_switch_state(pulledStrNum); //returns 0 when pulled
    
    //If pulled, remove from pulledStrsList, and add to releasedStrsList
    if(!isStrReleased) {
      pulledStrsList.remove(index);
      releasedStrsList.add(pulledStrNum);
      //if released, turn off corresponding LED
      if(pulledStrNum == 1) {
        analogWrite(A0, 0);
      } else if(pulledStrNum == 2) {
        analogWrite(A2, 0);
      } else {
        analogWrite(A4, 0);
      }
    }
  }
}

void checkReleasedStrsList(){
  for(int i = 0; i < releasedStrsList.size(); i++) {
    int releasedStrNum = releasedStrsList.get(i);
    //append back to idleStrsList
    idleStrsList.add(releasedStrNum);
    String note = getMusicalNote(releasedStrNum);
    Serial.println(note);
  }
  //light up LED
  releasedStrsList.clear();
}

String getMusicalNote(int strNum) {
  //return corresponding note to string
  switch(strNum) {
    case 1:
      return "C";
    case 2:
      return "E";
    case 3:
      return "G";
  }
}

void printAllLists() {
  //Print idle strings
  Serial.println("=================");  
  Serial.println("Idle Strings: ");
  if(idleStrsList.size() != 0) {
    for(int i = 0; i < idleStrsList.size(); i++) {
      Serial.print(idleStrsList.get(i));
    }
  } else {
    Serial.print("No Idle Strings");
  }
  Serial.println("\n");
  Serial.println("=================");
  
  //Print Pulled strings
  Serial.println("=================");
  Serial.println("Pulled Strings: ");
  if(pulledStrsList.size() != 0) {
    for(int i = 0; i < pulledStrsList.size(); i++) {
      Serial.print(pulledStrsList.get(i));
    }
  } else {
    Serial.print("No Pulled Strings");
  }
  Serial.println("\n");
  Serial.println("=================");
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
}
