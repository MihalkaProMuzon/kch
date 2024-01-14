#include "kursach_utility.h"
#include "kursach_core.h"


void pageEnterParams(){
  setLightsOff();
  lcd.clear();
  lcdPrint("CMEШAPИK 3500EXT");
  lcdPrint("BBOД ДЛЯ CTAPTA",0,1);

  butEnter.ptrF = pageCompCountChoose;
}

void pageCompCountChoose(){               // Выбор кол-ва комп.
  lcd.clear();
  lcdPrint("KOЛ-BO KOMПOHEHT.");
  lcdPrint(componentsCount,12,1);

  butNegative.ptrF = [](){
    setComponentsCount(componentsCount-1);
    lcdPrint(componentsCount,12,1);
  };
  butPositive.ptrF = [](){
    setComponentsCount(componentsCount+1);
    lcdPrint(componentsCount,12,1);
  };
  butEnter.ptrF = [](){
    pageCompIWeightChoose(0);
  };
}

byte compI = 0;
void pageCompIWeightChoose(byte i){         // Ввод целеовго веса iго компонента
  compI = i;
  
  lcdPrint("ВЕС "+ String(compI+1) +" KOMПOHEHTА");

  static auto changeCmpW = [](int8_t directn){
    setComponentWeight(compI, componentsWeights[compI] + directn);
    lcdPrint(String(componentsWeights[compI]) + " ГPM",8,1);
  };
  changeCmpW(0);

  butNegative.ptrF = [](){ changeCmpW(-1); };
  butNegative.ptrFRepeat = [](){ changeCmpW(-1*WEIGHT_CHANGE_MUL); };

  butPositive.ptrF = [](){ changeCmpW(1); };
  butPositive.ptrFRepeat = [](){ changeCmpW(1*WEIGHT_CHANGE_MUL); };
  
  butEnter.ptrF = [](){
    if(compI >= componentsCount-1){
      pageSetBlendTime();
    }else{
      pageCompIWeightChoose(compI+1);
    }
  };
}


void pageSetBlendTime(){         // Ввод времени смешивания
  lcd.clear();
  lcdPrint("BPEMЯ CMEШИBAHИЯ");
  
  static auto changeBlndTime = [](int8_t directn){
    setBlendTime(blendTime + directn);
    lcdPrint(intToTimeStr(blendTime),8,1);
  };
  changeBlndTime(0);

  butNegative.ptrF = [](){ changeBlndTime(-1); };
  butNegative.ptrFRepeat = [](){ changeBlndTime(-1*BLEND_TIME_CHANGE_MUL); };

  butPositive.ptrF = [](){ changeBlndTime(1); };
  butPositive.ptrFRepeat = [](){ changeBlndTime(1*BLEND_TIME_CHANGE_MUL); };
  
  butEnter.ptrF = confirm;
}

void pageWeighing(){
  lcdPrint("BЗBEШ KOMП " + String(componentNumber+1));
  byte prc = limit(weight / componentsWeights[componentNumber] * 100, 0, CAUTION_COMP_WEIGHT);
  lcdPrint(String(prc) + "%",0,1);
  lcdPrint(String((int)weight) + "/" + String(componentsWeights[componentNumber]) + "Г",6,1);
  percentagesToFlashing(prc);

  butPositive.ptrF = nullptr;
  butPositive.ptrFRepeat = [](){
   if(isButlongPress)
    resetTare();
  };

  butNegative.ptrF = nullptr;
  butNegative.ptrFRepeat = [](){
   if(isButlongPress)
    resetProgramm();
  };

  butEnter.ptrF = confirm;
}

void pageBlend(){
  setLightsOff();
  if(blendingTime == 0){
    lcdPrint("BBOД ДЛЯ HAЧAЛA ");
    lcdPrint("   CMEШИBAHИЯ   ",0,1);
    return;
  }

  if(blendPaused){
    lcdPrint("   CMEШИBAHИE   ");
    lcdPrint("    HA ПAУЗE    ",0,1);
  }else{
    lcdPrint("ИДET CMEШИBAHИE ");
    lcdPrint(intToTimeStr(blendingTime/1000) + " / " + intToTimeStr(blendTime) + "   ",0,1);
  }
  
  butEnter.ptrF = confirm;
}

void pageEnd(){
  lcdPrint("   CMEШИBAHИE   ");
  lcdPrint("   ЗABEPШEHO    ",0,1);
}


void showGUI(byte gui){
  switch(gui){
    case(POS_ENTER_PARAMS): pageEnterParams(); break;
    case(POS_WEIGHING): pageWeighing(); break;
    case(POS_BLENDING): pageBlend(); break;
    case(POS_END): pageEnd(); break;
  }
}

void setup() {
  Serial.begin(19200);
  kursachDevicesInit();
  setCoreGuiShowPtr(showGUI);
  resetProgramm();
}

void loop() {
  handleButs();
  runProgramm();
}
