#ifndef kursach_manifest
#define kursach_manifest

#include <Wire.h>

#define _LCD_TYPE 1
#include <LCD_1602_RUS_ALL.h>
LCD_1602_RUS lcd(0x27, 16, 2, 0);


#define LED_R_PIN 7
#define LED_G_PIN 6
#define LED_B_PIN 5


#define BUT_READ_DELAY_MS 45
#define BUT_AFTERPUSH_DELAY_MS 400
#define BUT_REPEAT_DELAY_MS 75

struct Button{
  byte pin;
  byte lastState;
  long timeSave;
  void (*ptrF)(); // функция нажатия
  void (*ptrFRepeat)(); // функция зажатия
};

Button butEnter = (Button) {2, HIGH, 0};
Button butPositive = (Button) {3, HIGH, 0};
Button butNegative = (Button) {4, HIGH, 0};

Button* BUTTONS[] = {&butNegative, &butPositive, &butEnter};
const byte BUTTONS_COUNT = sizeof(BUTTONS) / sizeof(BUTTONS[0]); 


#define MAX_COMP_COUNT 5
#define MAX_COMP_WEIGHT 1000
#define WEIGHT_CHANGE_MUL 25
#define MAX_BLEND_TIME 600
#define BLEND_TIME_CHANGE_MUL 10

#define GRAM 0

#define POS_ENTER_PARAMS 0
#define POS_WEIGHING 1

#endif
