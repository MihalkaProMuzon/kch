#include "kursach_gui_pages.h"
#include "kursach_utility.h"

void setup() {
  Serial.begin(9600);
   // инициализируем экран
  //lcd.init();
  // включаем подсветку
  //lcd.backlight();
  //lcd.printCyrillic("\x088" "p" "\x098" "\x093" "e" "\x09F" ", " "M" "\x098" "p!",0,0);
  
  kurshachGuiPagesInit();
  cirilicChars("ff","va");
}

void loop() {
  Serial.println(cirilicChars["hh"]);
}
