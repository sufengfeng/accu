#ifndef __GLOBAL__H
#define __GLOBAL__H
#include "Arduino.h"

extern volatile bool g_bIsUpdateWaveDigital;

extern volatile uint8_t g_nCurrentState;
extern volatile bool g_bEnableLogicAn;
extern volatile uint32_t g_nLogicAnValue;

extern volatile boolean g_tTimer20ms;

#define u8 uint8_t
#define u32 uint32_t
//定义所有的IO引脚
enum PinAssignments {
  //REGESTER_PIN=, //滑动变阻器 
  AIN_PIN = A0 ,     //模拟量输入
  AOUT_PIN = A1,   //模拟量输入
  BUTTON_PIN0=0,   //
  BUTTON_PIN1=1,   //
  DIGITAL_PIN=2,
  
  IIC_SCK_PIN = 8,
  IIC_SDA_PIN = 9,
  drivePin = 6,
  loadLed = 12,
  loadPin = 4,
  brakingLed = 8
};
void InitPins();

void InitTimer();
void IIC_loop();
void IIC_setup();
#endif

