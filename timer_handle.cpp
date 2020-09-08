#include "FlexiTimer2Advance.h"

#include "global.h"
const int LED = LED_BUILTIN;

void UpdateLED(){
  static boolean output=HIGH;
  digitalWrite(LED,output);  
  static int counter=0;
  counter++;
  if(counter>25){
    counter=0;
    output=!output;  
  }
}
int g_nAinValue=0;//  AIn输入信号，用于示波器显示当前值

void TimerHandle()
{
  static uint32_t counter=0;
  counter++;
  if(counter>9600/50){      //设定20ms软定时器
    counter=0;
    UpdateLED();                    //LED闪烁
    g_tTimer20ms=!g_tTimer20ms;     //用于准确定时的全局变量
  }
  if(g_bEnableLogicAn){     //使能逻辑分析仪   小端模式，高位在前，低位在后
    int value=digitalRead(DIGITAL_PIN);
    g_nLogicAnValue = g_nLogicAnValue<1;
    g_nLogicAnValue = g_nLogicAnValue+value;
  }
}
//设置定时器基准为1/9600ms
void InitTimer(){
    pinMode(LED,OUTPUT);
    //FlexiTimer2Advance::set(20,1000,TimerHandle);//设置1000则，基准为1/1000ms,
    FlexiTimer2Advance::set(1,9600,TimerHandle);//设置1000则，基准为1/1000ms,
    FlexiTimer2Advance::start();
}

