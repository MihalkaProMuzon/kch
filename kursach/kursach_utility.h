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

  pinMode(MOTOR, OUTPUT);
  digitalWrite(10, LOW);
}

void resetButtons(){
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    Button* but = BUTTONS[i];
    but->ptrF = nullptr;
    but->ptrFRepeat = nullptr;
  }
}

byte readButState(Button* but) {
  byte state = digitalRead(but->pin);
  if (state != but->lastState) {
    delay(BUT_READ_DELAY_MS);
    return digitalRead(but->pin);
  }
  return state;
}

bool isButlongPress(Button *but,void (*func)()){
  return millis() - but->timeSave > BUT_TIME_FOR_LONGPRESS;
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

String addZeroToStr(int val){
  String s = String(val);
  return (val < 10) ? "0"+s : s;
}

String intToTimeStr(int val){
  return addZeroToStr(val / 60) + ":" + addZeroToStr(val % 60);
}

void doLightShow() {
  long lightTick = millis() / 75;

  digitalWrite(LED_R_PIN, lightTick % 4 == 0);
  digitalWrite(LED_G_PIN, lightTick % 5 == 0);
  digitalWrite(LED_B_PIN, lightTick % 6 == 0);
}


void setLights(byte r, byte g, byte b) {
  if(r!=-1) digitalWrite(LED_R_PIN, r);
  if(g!=-1) digitalWrite(LED_G_PIN, g);
  if(b!=-1) digitalWrite(LED_B_PIN, b);
}

void setLightsOff() {
  setLights(HIGH, HIGH, HIGH);
}

void percentagesToFlashing(float flashPercent){
  if(flashPercent == -1) return;
  if(flashPercent == 0) flashPercent = 1;
  
  if (flashPercent >= CAUTION_COMP_WEIGHT){
    setLights(LOW, HIGH, HIGH); return;
  }
  if (flashPercent >= 100){
    setLights(HIGH, LOW, HIGH); return;
  }
  
  setLights(HIGH, HIGH, -1);
  float fP = flashPercent / 100;
  fP *= fP;
  analogWrite(LED_B_PIN ,255 -  (255 * fP));
}

float getCellWeight(){
  float units = scale.get_units(HX711_MEASURE_COUNT);
  units/HX711_MEASURE_COUNT;
  return units * CONVERSION_K_GRAM;
}

void turnOnMotor(){
  digitalWrite(MOTOR, HIGH);
}
void turnOffMotor(){
  digitalWrite(MOTOR, LOW);
}



#endif
