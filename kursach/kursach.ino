#include "kursach_utility.h"
#include "kursach_core.h"


static void pageStart(){
  lcd.clear();
  lcdPrint("CMEШAPИK 3500EXT");
  lcdPrint("BBOД ДЛЯ CTAPTA",0,1);

  butEnter.ptrF = pageCompCountChoose;
}

static void pageCompCountChoose(){
  lcd.clear();
  lcdPrint("KOЛ-BO KOMПOHEHT.");
  lcdPrint(componentsCount,12,1);

  butNegative.ptrF = [](){
    componentsCount--;
    lcdPrint(componentsCount,12,1);
  };
  butPositive.ptrF = [](){
    componentsCount++;
    lcdPrint(componentsCount,12,1);
  };
}

void showGUI(byte gui){
  switch(gui){
    case(ENTER_PARAMS): pageStart(); break;
  }
}



void setup() {
  Serial.begin(19200);
  kursachDevicesInit();
  setCoreGuiPtr(showGUI);
  resetProgramm();
}

void loop() {
  handleButs();
  
  /*if(butEnter.lastState == 0){
    doLightShow();  
  }else{
    lightsOff();  
  }*/
  
  
}
