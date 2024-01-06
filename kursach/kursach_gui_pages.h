#ifndef kursach_gui_pages
#define kursach_gui_pages

#include "kursach_manifest.h"
#include "kursach_utility.h"

void clearPage(byte x, byte y){
  lcd.clear();
  lcd.setCursor(x, y);
}

void pageStart(){
  clearPage(0,0);
  lcd.print("CMEШAPИK 3500EXT");
  lcd.setCursor(0, 1);
  lcd.print("BBOД ДЛЯ CTAPTA");
}

void pageCompCountChoose(){
  clearPage(0,0);
  lcd.print("KOЛ-BO KOMПOHEHT.");
  lcd.setCursor(12, 1);
  lcd.print("2");
}


#endif
