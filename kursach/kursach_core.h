#ifndef kursach_core
#define kursach_core

#include "kursach_manifest.h"
#include "kursach_utility.h"


byte programmPosition = 0;  //  позиция програмыы

byte componentsCount = 1;
int componentsWeights[MAX_COMP_COUNT] = {1,1,1,1,1};
int blendTime = 10;

byte componentNumber; // номер взвешиваниемого компонета
float weight = 0;      // текущий вес на датчике


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
  showGuiPtr(POS_WEIGHING);
}
void weighingConfirm(){
  if(componentNumber >= componentsCount)
    nextStep();
  else{
    componentNumber++;
    weighing();
  }
}
                                                                //  -------------

// Сброс на стратовое положение
void resetProgramm(){                                       
  posEnterParams();
}                                                              
void nextStep(){
  switch(programmPosition){
    case(POS_ENTER_PARAMS): posWeighing(); break; 
  }
  showGuiPtr(programmPosition);
}
void confirm(){
  switch(programmPosition){
    case(POS_ENTER_PARAMS): nextStep(); break;
    case(POS_WEIGHING): weighingConfirm(); break;
  }
}
void runProgramm(){
  switch(programmPosition){
    case(POS_WEIGHING): weighing(); break;
  }
}

#endif
