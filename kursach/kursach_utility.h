#ifndef kursach_utily
#define kursach_utily

#include "kursach_manifest.h"

void kursachUtilyInit(){
  pinMode(LED_R, OUTPUT); digitalWrite(LED_R, HIGH);
  pinMode(LED_G, OUTPUT); digitalWrite(LED_G, HIGH);
  pinMode(LED_B, OUTPUT); digitalWrite(LED_B, HIGH);
}

void doLightShow(){
  long lightTick = millis()/75;
  
  digitalWrite(LED_R, lightTick%4 == 0);
  digitalWrite(LED_G, lightTick%5 == 0);
  digitalWrite(LED_B, lightTick%6 == 0);
}



#endif
