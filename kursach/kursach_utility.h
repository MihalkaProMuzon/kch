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

  scale.begin(HX711_DT, HX711_SCK);
  scale.set_scale();
  scale.tare();
  scale.set_scale(HX711_CALIBRATION_FACTOR);  

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
void setLights(byte r, byte g, byte b) {
  digitalWrite(LED_R_PIN, r);
  digitalWrite(LED_G_PIN, g);
  digitalWrite(LED_B_PIN, b);
}




int flashPercent = -1;
void percentagesToFlashing(){
  if(flashPercent == -1) return;
  if(flashPercent == 0) flashPercent = 1;
  
  if (flashPercent >= CAUTION_COMP_WEIGHT){
    setLights(LOW, HIGH, HIGH); return;
  }
  if (flashPercent >= 100){
    setLights(HIGH, LOW, HIGH); return;
  }
  
  int flashtime = (100 - flashPercent)*20;
  bool blue = fmod( (millis() / flashtime) , 2) < 1;
  setLights(HIGH, HIGH, blue);
}


float getCellWeight(){
  float units = 0;
  for (int i = 0; i < HX711_MEASURE_COUNT; i ++) {
    units = + scale.get_units(1);
  }
  return (units / HX711_MEASURE_COUNT) * CONVERSION_K_GRAM;
}

#endif
