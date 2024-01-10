#ifndef kursach_utily
#define kursach_utily

#include "kursach_manifest.h"

void kursachDevicesInit() {
  pinMode(LED_R_PIN, OUTPUT);
  digitalWrite(LED_R_PIN, HIGH);
  pinMode(LED_G_PIN, OUTPUT);
  digitalWrite(LED_G_PIN, HIGH);
  pinMode(LED_B_PIN, OUTPUT);
  digitalWrite(LED_B_PIN, HIGH);

  for (int i = 0; i < BUTTONS_COUNT; i++) {
    pinMode(BUTTONS[i]->pin, INPUT_PULLUP);
  }

  lcd.init();
  lcd.backlight();
}

bool butPressed(Button* but) {
  if (digitalRead(but->pin) != but->lastState) {
    delay(BUT_READ_DELAY_MS);
    byte state = digitalRead(but->pin); 
    bool pressed = (state == LOW) && (but->lastState == HIGH);
    but->lastState = state;
    return pressed;
  }
  return false;
}

void handleButs() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    Button* but = BUTTONS[i];
    if(butPressed(but)) {
      if(but->ptrF != nullptr){
        but->ptrF();
      }
    }
  }
}

template<typename T>
void lcdPrint(T varible,byte posX = 0,byte posY = 0){
  lcd.setCursor(posX,posY);
  lcd.print(String(varible) + "      ");
}

void doLightShow() {
  long lightTick = millis() / 75;

  digitalWrite(LED_R_PIN, lightTick % 4 == 0);
  digitalWrite(LED_G_PIN, lightTick % 5 == 0);
  digitalWrite(LED_B_PIN, lightTick % 6 == 0);
}
void lightsOff() {
  digitalWrite(LED_R_PIN, HIGH);
  digitalWrite(LED_G_PIN, HIGH);
  digitalWrite(LED_B_PIN, HIGH);
}



#endif
