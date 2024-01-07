#include "kursach_gui_pages.h"
#include "kursach_utility.h"

void setup() {
  Serial.begin(19200);
  kursachUtilyInit();

  lcd.init();
  lcd.backlight();
  pageStart();
  
}

void loop() {
  handleButs();
}
