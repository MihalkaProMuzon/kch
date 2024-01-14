#ifndef kursach_core
#define kursach_core

#include "kursach_manifest.h"
#include "kursach_utility.h"


byte programmPosition = 0;  //  позиция програмыы

byte componentsCount = 1;
int componentsWeights[MAX_COMP_COUNT] = {1,1,1,1,1};
long blendTime = 10;        // Время для смешивания


byte componentNumber; // номер взвешиваниемого компонета
float weight = 0;      // текущий вес на датчике

long blendingTime = 0;      // Времени смешивания прошло
long blendingTimeSave = 0;
bool blendPaused = true;

// Указатель на функцию отображения интерфейса для текущего этапа программы
void (*showGuiPtr)(byte gui);
void setCoreGuiShowPtr(void(*shwGuiPtr)(byte gui)){
  showGuiPtr = shwGuiPtr;
}
                                                                // ---------------
void nextStep();                                                                
                                                                // Ввод параметров
void posEnterParams(){
  programmPosition = POS_ENTER_PARAMS;
  blendPaused = true;
  blendingTime = 0;
  turnOffMotor();
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

                                                                 // Взвешивание
void resetTare(){
  scale.tare();
}
void posWeighing(){
  programmPosition = POS_WEIGHING;
  componentNumber = 0;
  scale.tare();
}
void weighing(){             
  weight = getCellWeight();
  showGuiPtr(programmPosition);
}
void weighingConfirm(){
  if((componentNumber+1) >= componentsCount){
    nextStep();
  }
  else{
    componentNumber++;
    weighing();
  }
}

                                                                 // Смешивание
void posBlending(){
  programmPosition = POS_BLENDING;
  
}
void turnOnBlend(){
  blendPaused = false;
  turnOnMotor();
}
void turnOffBlend(){
  blendPaused = true;
  turnOffMotor();
}
void blending(){
  if(!blendPaused){
    blendingTime += millis() - blendingTimeSave;
    if(blendingTime > blendTime*1000 + 100){
      turnOffBlend();
      nextStep();
    }
  }
  blendingTimeSave = millis();
  showGuiPtr(programmPosition);
}
void blendingConfirm(){
  if(blendPaused){
    turnOnBlend();
  }else{
    turnOffBlend();
  }
}

                                                                // Завершено
void posEnd(){
  programmPosition = POS_END;
}
void posEndConfirm(){
  nextStep();
}
                                                                //  -------------

// Сброс на стратовое положение
void resetProgramm(){                                       
  posEnterParams();
  showGuiPtr(programmPosition);
}                                                              
void nextStep(){
  switch(programmPosition){
    case(POS_ENTER_PARAMS): posWeighing(); break; 
    case(POS_WEIGHING): posBlending(); break;
    case(POS_BLENDING): posEnd(); break;
    case(POS_END): posEnterParams(); break;
  }
  showGuiPtr(programmPosition);
}
void confirm(){
  switch(programmPosition){
    case(POS_ENTER_PARAMS): nextStep(); break;
    case(POS_WEIGHING): weighingConfirm(); break;
    case(POS_BLENDING): blendingConfirm(); break;
    case(POS_END): posEndConfirm(); break;
  }
}
void runProgramm(){
  switch(programmPosition){
    case(POS_WEIGHING): weighing(); break;
    case(POS_BLENDING): blending(); break;
  }
}

#endif
