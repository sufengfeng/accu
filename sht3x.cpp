  #include "global.h"
#include <Wire.h>
/*
  GND      --------  GND
   A4      --------  A4   (SDA, data)
   A5      --------  A5   (SCL, clock)
   5V      --------  Vin
   */
 #define SHTC3ADDR 0xE0
 float Humidity,Temperature;
/*================================================================
【  Name  】void SoftReset(void)
【Function】SHTC3软件复位，主函数中调用
【  Notes 】从高到低，依次接收
================================================================*/
void SoftReset(void)                    
{
//        I2CInit();                       //I2C initialize
//        I2CStart();                      //start I2C   
//        I2C_Write_Byte(SHTC3ADDR&0xfe);  //I2C address + write
//        I2CDelay(1);
//        I2C_Write_Byte(0x80);            //soft reset MSB
//        I2C_Write_Byte(0x5D);            //soft reset LSB
//        I2CStop();                       //stop I2C

  Wire.beginTransmission(SHTC3ADDR);
  Wire.write(0x80);
  Wire.write(0x5D);
  Wire.endTransmission();
}
   
void IIC_setup()
{
    Wire.begin(); // join i2cbus (主机，不用写IIC地址)
    SoftReset();
}
int i = 1;



/*================================================================
【  Name  】float ReadShtc3(char whatdo)
【Function】非主机模式，读取函数函数
【  Notes 】
================================================================*/
void ReadShtc3()
{
        uint16_t HumData=0,TempData=0;

//        I2CStart();        
//        I2C_Write_Byte(SHTC3ADDR&0xfe);           //I2C address + write + ACK   
//        I2C_Write_Byte(0X35);                     //Wakeup MSB  唤醒
//        I2C_Write_Byte(0X17);                     //Wakeup LSB
//        I2CStop();  
//        delay_ms(10);      
  Wire.beginTransmission(SHTC3ADDR);
  Wire.write(0X35);
  Wire.write(0XE0);
  Wire.endTransmission();
  delay(10);  
//        I2CStart();
//        I2C_Write_Byte(SHTC3ADDR&0xfe);           //I2C address + write + ACK     
//        I2C_Write_Byte(0X58);                     //Measurement command MSB 湿度值优先 不锁存SCL时钟线
//        I2C_Write_Byte(0XE0);                     //Measurement command LSB
//        I2CStop(); 
//        delay_ms(50);                             //等待测量完成
  Wire.beginTransmission(SHTC3ADDR);
  Wire.write(0X58);
  Wire.write(0XE0);
  Wire.endTransmission();
  delay(50);     
  
//        I2CStart();
//        I2C_Write_Byte(SHTC3ADDR|0x01);           //I2C address + read  可通过ACK来判断是否测量完成。完成则有响应
//        delay_ms(1); 
//        HumData = I2C_Read_Byte(ACK);             //Data(MSB) 先读湿度
//        HumData=HumData<<8;
//        HumData |= I2C_Read_Byte(ACK);            //Data(LSB)
//        I2C_Read_Byte(ACK);  

    //读数据
     Wire.requestFrom(SHTC3ADDR, 2); // 要求2号IIC设备，通过Wire传送 6个 char过来
     while(Wire.available()) // 如果Wire上有 char 等读取
     {
          HumData |=Wire.read(); // 从Wire 上读取一个char
          HumData=HumData<<8;          
     }
//        TempData = I2C_Read_Byte(ACK);            //Data(MSB) 后读温度
//        TempData=TempData<<8;
//        TempData |= I2C_Read_Byte(ACK);           //Data(LSB)
//        I2C_Read_Byte(NACK); 
//        I2CStop();                                //Stop I2C
     //读数据
     Wire.requestFrom(SHTC3ADDR, 2); // 要求2号IIC设备，通过Wire传送 6个 char过来
     while(Wire.available()) // 如果Wire上有 char 等读取
     {
          TempData |=Wire.read(); // 从Wire 上读取一个char
          TempData=HumData<<8;       
     }
//        I2CStart();        
//        I2C_Write_Byte(SHTC3ADDR&0xfe);           //I2C address + write + ACK   
//        I2C_Write_Byte(0XB0);                     //Sleep MSB 进入休眠
//        I2C_Write_Byte(0X98);                     //Sleep LSB
//        I2CStop();  
  Wire.beginTransmission(SHTC3ADDR);
  Wire.write(0XB0);
  Wire.write(0X98);
  Wire.endTransmission();
  delay(50);   
  
        /*-- calculate relative humidity [%RH] --*/ 
        Humidity =(HumData*100.0)/65536;                 //公式: RH%=100 * SRH/2^16                
        //Humidity =HumData;  
        /*-- calculate temperature [°C] --*/
        Temperature = (TempData*175.0)/65536-45;      //公式:T= -45 + 175 * ST/2^16       
        //Temperature = TempData;       
}
char tmpBuf[64];
void IIC_loop()
{
  ReadShtc3();//测量湿度%RH 温度T
  //sprintf(tmpBuf,"SHTC3 温度输出：%0.2f℃   湿度输出：%0.2fRH\r\n",Temperature,Humidity);
  Serial.println(Temperature);
  Serial.println(Humidity);
  return;
  
    //向从机写入数据
     Wire.beginTransmission(2);
     Wire.write(i);
     Wire.endTransmission();
     //读数据
     Wire.requestFrom(2, 6); // 要求2号IIC设备，通过Wire传送 6个 char过来
     while(Wire.available()) // 如果Wire上有 char 等读取
     {
           char c = Wire.read(); // 从Wire 上读取一个char
            Serial.print(c); //输出到串口监视器查看
     }
     delay(2000); // 等2秒
     Serial.println( ); // 输出到下一行方便查看        
     //向从机写入数据
     Wire.beginTransmission(3);
     Wire.write(i);
     Wire.endTransmission();
     //读数据
     Wire.requestFrom(3, 6); // 要求2号IIC设备，通过Wire传送 6个 char过来
     while(Wire.available()) // 如果Wire上有 char 等读取
     {
           char c = Wire.read(); // 从Wire 上读取一个char
            Serial.print(c); //输出到串口监视器查看
     }
      delay(2000); // 等2秒
      Serial.println( ); // 输出到下一行方便查看            
     //向从机写入数据
     Wire.beginTransmission(4);
     Wire.write(i);
     Wire.endTransmission();
     //读数据
     Wire.requestFrom(4, 6); // 要求2号IIC设备，通过Wire传送 6个 char过来
     while(Wire.available()) // 如果Wire上有 char 等读取
     {
           char c = Wire.read(); // 从Wire 上读取一个char
            Serial.print(c); //输出到串口监视器查看
     }
      delay(2000); // 等2秒
      Serial.println( ); // 输出到下一行方便查看      
     i++;
     i = i%4;
} // loop(
