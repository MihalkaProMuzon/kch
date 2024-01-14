#ifndef kursach_manifest
#define kursach_manifest

#include <Wire.h>
#include "HX711.h"
#define _LCD_TYPE 1 // LCD_1602_RUS_ALL тип 1 - через I2C, тип 2 - 8 контактов
#include <LCD_1602_RUS_ALL.h>

LCD_1602_RUS lcd(0x27, 16, 2, 0);

#define LED_R_PIN 7
#define LED_G_PIN 6
#define LED_B_PIN 5

#define HX711_DT 8
#define HX711_SCK 9
#define HX711_MEASURE_COUNT 3          // кол-во измерений для среднего
#define HX711_CALIBRATION_FACTOR 7.65   // колибровочный коэфф
const float CONVERSION_K_GRAM    = 0.035274; // для перевода из унций в граммы
HX711 scale;

#define MOTOR 11


#define BUT_READ_DELAY_MS 45
#define BUT_AFTERPUSH_DELAY_MS 400
#define BUT_REPEAT_DELAY_MS 75
#define BUT_TIME_FOR_LONGPRESS 1000

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
#define POS_BLENDING 2
#define POS_END 3


#define CAUTION_COMP_WEIGHT 110

#endif
