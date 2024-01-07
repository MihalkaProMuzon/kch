#ifndef kursach_utily
#define kursach_utily

#include "kursach_manifest.h"

void kursachUtilyInit() {
  pinMode(LED_R_PIN, OUTPUT);
  digitalWrite(LED_R_PIN, HIGH);
  pinMode(LED_G_PIN, OUTPUT);
  digitalWrite(LED_G_PIN, HIGH);
  pinMode(LED_B_PIN, OUTPUT);
  digitalWrite(LED_B_PIN, HIGH);

  for (int i = 0; i < BUTTONS_COUNT; i++) {
    pinMode(BUTTONS[i]->pin, INPUT_PULLUP);
  }
}

byte readButState(Button* but) {
  if (digitalRead(but->pin) != but->lastState) {
    delay(BUT_READ_DELAY_MS);
    return digitalRead(but->pin);
  }
  return but->lastState;
}

bool butWasPressed(Button* but) {
  return (readButState(but) == LOW) && (but->lastState == HIGH);
}

void handleButs() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    Button* but = BUTTONS[i];
    if(butWasPressed(but)) {
      if(but->ptrF != nullptr){
        but->ptrF();
      }
    }   
    but->lastState = readButState(but);
  }
}


void doLightShow() {
  long lightTick = millis() / 75;

  digitalWrite(LED_R_PIN, lightTick % 4 == 0);
  digitalWrite(LED_G_PIN, lightTick % 5 == 0);
  digitalWrite(LED_B_PIN, lightTick % 6 == 0);
}



#endif
