#include "kursach_utility.h"
#include "kursach_core.h"


void pageStart(){
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
    lcdPrint(intToTimeStr(blendTime / 60) + ":" + intToTimeStr(blendTime % 60),8,1);
  };
  changeBlndTime(0);

  butNegative.ptrF = [](){ changeBlndTime(-1); };
  butNegative.ptrFRepeat = [](){ changeBlndTime(-1*BLEND_TIME_CHANGE_MUL); };

  butPositive.ptrF = [](){ changeBlndTime(1); };
  butPositive.ptrFRepeat = [](){ changeBlndTime(1*BLEND_TIME_CHANGE_MUL); };
  
  butEnter.ptrF = [](){
    confirmParametrs();
  };
}

void pageWeighing(){
  
}


void showGUI(byte gui){
  switch(gui){
    case(POS_ENTER_PARAMS): pageStart(); break;
    case(POS_WEIGHING): pageWeighing(); break;
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
