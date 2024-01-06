#include "kursach_gui_pages.h"
#include "kursach_utility.h"

void setup() {
  //kurshachGuiPagesInit();
  Serial.begin(9600);

   // инициализируем экран
  lcd.init();
  // включаем подсветку
  lcd.backlight();

  pageCompCountChoose();
}

void loop() {
  
  delay(2000);
}
