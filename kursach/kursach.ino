#include "kursach_gui_pages.h"
#include "kursach_utility.h"



void setup() {
  Serial.begin(9600);
  kursachUtilyInit();


   // инициализируем экран
  lcd.init();
  // включаем подсветку
  //lcd.backlight();

  pageStart();
  
}

byte sy = 0;
void loop() {
  
}
