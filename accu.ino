#include "global.h"
extern void setup_oled();
extern void loop_oled();

//全局变量参数配置
volatile bool g_bIsUpdateWaveDigital=false;  //更新波形数据标识位
volatile int g_nWaveType = 1;                //默认正弦信号
volatile uint8_t g_nCurrentState=0;         // 状态机
volatile bool g_bEnableLogicAn=false;       //更新逻辑分析仪标识位


volatile uint32_t g_nLogicAnValue=false;       //当前逻辑分析仪的数值
                  
volatile int g_aWavedigital[255];             //定义8位R2R DA输出的对应值
volatile boolean g_tTimer20ms=HIGH;           //全局20ms标志位

void setup() {
  // initialize serial communications at 9600 bps:
  InitPins() ;      //初始化外部IO
  InitTimer();    //初始化定时器
IIC_setup();  
  Serial.begin(115200);//保证串口必须可用
}


void loop() {
//  int sensorValue = analogRead(A0);
  //loop_oled();    //oled循环显示
  //UpdateWaveDigital();    //根据需要更新波形数据
  //MechineSateLoop();      //状态机维护
  IIC_loop();
  delay(10);              // delay in between reads for stability
  Serial.println("_running..."); 
}

