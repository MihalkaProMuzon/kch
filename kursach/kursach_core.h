#ifndef kursach_core
#define kursach_core

#include "kursach_manifest.h"
#include "kursach_utility.h"


static byte programmPosition = 0;  //  позиция програмыы

static byte componentsCount = 1;
static int componentsWeights[MAX_COMP_COUNT] = {1,1,1,1,1};
static int blendTime = 10;
static bool paramsSetted = false;

static byte componentNumber;
static byte tareWeight;


void (*showGuiPtr)(byte gui);                     // Указатель на функцию отображения интерфейса для текущего этапа программы
void setCoreGuiShowPtr(void(*shwGuiPtr)(byte gui)){
  showGuiPtr = shwGuiPtr;
}

static void nextStep(){
  switch(programmPosition){
    case(POS_ENTER_PARAMS): programmPosition = POS_WEIGHING; break; 
    //case(POS_WEIGHING): programmPosition = POS_WEIGHING; break;
  }
  showGuiPtr(programmPosition);
}


void setComponentsCount(byte compCount){
  componentsCount = limit( compCount, 1, MAX_COMP_COUNT);
}
void setComponentWeight(byte compI,int weight){
  componentsWeights[compI] = limit(weight, 1, MAX_COMP_WEIGHT);
}
void setBlendTime(int blendT){
  blendTime = limit(blendT, 10, MAX_BLEND_TIME);
}
void confirmParametrs(){      //завершить ввод параметров и перейти к следующему шагу
  paramsSetted = true;
}



void resetProgramm(){              // Стартовое положение (ввод параметров)
  programmPosition = POS_ENTER_PARAMS;
  paramsSetted = false;
  showGuiPtr(programmPosition);
}
void enterParams(){
  if(paramsSetted)
    nextStep();
}
void weighing(){             // Начать изготовление (взвешивние -> смешивание)
  
}


void runProgramm(){
  switch(programmPosition){
    case(POS_WEIGHING): weighing(); break;
  }
}



#endif
