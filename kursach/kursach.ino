#include "kursach_gui_pages.h"
#include "kursach_utility.h"

void setup() {
  Serial.begin(19200);
  kursachUtilyInit();

  lcd.init();
  lcd.backlight();
  pageStart();

  
  butNegative.ptrF = s0;
  butPositive.ptrF = s1;
  butEnter.ptrF = s2;
}

void s0(){ Serial.print("0"); }
void s1(){ Serial.print("1"); }
void s2(){ Serial.print("2"); }

void loop() {
  handleButs();
  if(butEnter.lastState == 0){
    doLightShow();  
  }else{
    lightsOff();  
  }
  
  
}
