#include "kursach_core.h"

static void pageStart(){
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("CMEШAPИK 3500EXT");
  lcd.setCursor(0, 1);
  lcd.print("BBOД ДЛЯ CTAPTA");

  butEnter.ptrF = pageCompCountChoose;
}

static void pageCompCountChoose(){
  lcd.clear(); lcd.setCursor(0, 0);

  byte compCount = 0;
  
  lcd.print("KOЛ-BO KOMПOHEHT.");
  lcd.setCursor(12, 1);
  lcd.print(String(compCount));

  butPositive.ptrF = [](){ 
    componentsCount++;
    lcd.setCursor(12, 1);
    lcd.print(String(componentsCount));
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
