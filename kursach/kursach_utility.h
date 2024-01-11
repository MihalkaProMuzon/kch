#ifndef kursach_utily
#define kursach_utily

#include "kursach_manifest.h"

void kursachDevicesInit() {
  digitalWrite(LED_R_PIN, HIGH);
  digitalWrite(LED_G_PIN, HIGH);
  digitalWrite(LED_B_PIN, HIGH);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  

  for (int i = 0; i < BUTTONS_COUNT; i++) {
    pinMode(BUTTONS[i]->pin, INPUT_PULLUP);
  }

  lcd.init();
  lcd.backlight();
}

byte readButState(Button* but) {
  byte state = digitalRead(but->pin);
  if (state != but->lastState) {
    delay(BUT_READ_DELAY_MS);
    return digitalRead(but->pin);
  }
  return state;
}

void handleButs() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    Button* but = BUTTONS[i];
    byte state = readButState(but);

    if( (state == LOW) && (but->lastState == HIGH) ){
      but->timeSave = millis();
      if(but->ptrF != nullptr){
        but->ptrF();
      }
    }
    else if((state == LOW) && ((millis() - but->timeSave) >  BUT_AFTERPUSH_DELAY_MS) ){
      if(but->ptrFRepeat != nullptr){
        but->ptrFRepeat();
        delay(BUT_REPEAT_DELAY_MS);
      }
    }
    but->lastState = state;
  }
}

template<typename T>
void lcdPrint(T varible,byte posX = 0,byte posY = 0){
  lcd.setCursor(posX,posY);
  lcd.print(String(varible) + "      ");
}

int limit(int val, int minVal, int maxVal){
  if (val < minVal)
    val = minVal;
  if (val > maxVal)
    val = maxVal;
  return val;
}

String intToTimeStr(int val){
  String s = String(val);
  return (val < 10) ? "0"+s : s;
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
