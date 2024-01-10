#ifndef kursach_core
#define kursach_core

#include "kursach_manifest.h"
#include "kursach_utility.h"


static byte programmPosition = 0;  //  позиция програмыы

static byte componentsCount;
static byte* componentsWeights;
static byte componentNumber;

static byte tareWeights;
static byte blendTime;


void (*showGuiPtr)(byte gui);                     // Указатель на функцию отображения интерфейса для текущего этапа программы
void setCoreGuiPtr(void(*shwGuiPtr)(byte gui)){
  showGuiPtr = shwGuiPtr;
}


void resetProgramm(){
  programmPosition = ENTER_PARAMS;
  showGuiPtr(programmPosition);
}

void setParametrs(byte compCount, byte compWeights[],int timeToBlend){
  componentsCount = compCount;
  componentsWeights = compWeights;
  blendTime = timeToBlend;
  componentNumber = 0;
}





#endif
