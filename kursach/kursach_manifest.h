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

struct Button{
  byte pin;
  byte lastState;
  void (*ptrF)(); // функция нажатия
};

Button butEnter = (Button) {2, HIGH, nullptr};
Button butPositive = (Button) {3, HIGH, nullptr};
Button butNegative = (Button) {4, HIGH, nullptr};

Button* BUTTONS[] = {&butNegative, &butPositive, &butEnter};
const byte BUTTONS_COUNT = sizeof(BUTTONS) / sizeof(BUTTONS[0]); 



#endif
