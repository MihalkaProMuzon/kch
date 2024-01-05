#ifndef kursach_gui_pages
#define kursach_gui_pages

#include "kursach_manifest.h"

Dictionary &cirilicChars = *(new Dictionary(6));
String cirilicCharsString =  "{ \"ы\" : \"\x0A3\", \"hh\" : \"af\",  \"ь\" : \"\x0A4\",    \"э\" : \"\x0A5\",  \"ю\" : \"\x0A6\",    \"я\" : \"\x0A7\"  }";

void kurshachGuiPagesInit(){
  cirilicChars.jload(cirilicCharsString);
}



void pageStart(){
  lcd.setCursor(0, 0);
  lcd.print("фыва");
  
}


#endif
