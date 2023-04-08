#include <ezButton.h>
#include <LinkedList.h> // include the LinkedList library

ezButton limitSwitch1(13);
ezButton limitSwitch2(11);
ezButton limitSwitch3(9);

//Variables used for computation
LinkedList<String> idleStrsList;
LinkedList<String> pulledStrsList;
LinkedList<String> releasedStrsList;

void setup() {
  Serial.begin(9600);

  limitSwitch1.setDebounceTime(50);
  limitSwitch2.setDebounceTime(50);
  limitSwitch3.setDebounceTime(50);

  int numOfStrs = 3;
  String strsArr[] = {"C", "E", "G"};
  //Populate idleStrsList with all strings.
  for(int i = 0; i < numOfStrs; i++){
    idleStrsList.add(strsArr[i]);
  }
}

int get_limit_switch_state(String str) {
  if (str == "C") {
    limitSwitch1.loop();
    return limitSwitch1.getState();
  } else if (str == "E") {
    limitSwitch2.loop();
    return limitSwitch2.getState();
  } else if (str == "G") {
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
    String idleStr = idleStrsList.get(index);
    int isStrPulled = get_limit_switch_state(idleStr); //returns 1 when pulled
    
    //If pulled, remove from idleStrsList, and add to pulledStrsList
    if(isStrPulled) {
      idleStrsList.remove(index);
      pulledStrsList.add(idleStr);
    }
  }
}

void checkPulledStrsList(){
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

void checkReleasedStrsList(){
  for(int i = 0; i < releasedStrsList.size(); i++) {
    String releasedStr = releasedStrsList.get(i);
    //append back to idleStrsList
    idleStrsList.add(releasedStr);
    Serial.println(releasedStr);
  }
  releasedStrsList.clear();
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
