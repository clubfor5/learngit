
#include "LCD12864RSPI.h"
//#include "word_data.h"      //汉字数组 
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )

unsigned char show2[] = {0xCE, 0xC0, 0xD0, 0xC7, 0xB7, 0xC0, 0xB8, 0xF4, 0xC8, 0xC8};
unsigned char show0[] = {0xB5, 0xE7, 0xC1, 0xF7}; //电流
unsigned char mA[] = "mA";                   //mA
unsigned char show1[] = {0xCE, 0xC2, 0xB6, 0xC8}; //温度
unsigned char wendu1[] = "1";                   //mA
unsigned char wendu2[] = "2";                   //mA
unsigned char du[] = {0xB6, 0xC8} ;                  //mA
unsigned int count;

void PrintLCD(uint8_t Row, uint8_t Column, char* Temp, uint8_t Length)            //从ROM中调用数据并输出
{
  unsigned char Display[8];
  for (int i = 0; i < Length; i++) {
    Display[i] = Temp[i];
  }
  LCDA.DisplayString(Row, Column, Display, Length);
}


//  DS18B20    温度模块
#include "DS18B20_S.h"
DS18B20_S ds1(10);           //pin7连接DS18B20
DS18B20_S ds2(9);           //pin7连接DS18B20
//DS18B20_S ds3(13);           //pin7连接DS18B20
float Temp1;
float Temp2;
float Temp_read1,Temp_read2;
//float TempMax;

// 测量电阻两侧电压
#define High_Voltage A0
float V0;

void setup() {
  // put your setup code here, to run once:
  LCDA.Initialise();               // 屏幕初始化
  delay(100);

  pinMode(High_Voltage, INPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  ds1.set(0x7F);//DS18B20 设置为12位数据读取
  delay(1000);
  ds2.set(0x7F);//DS18B20 设置为12位数据读取
  //ds3.set(0x7F);//DS18B20 设置为12位数据读取
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  V0 = 2 * analogRead(A0);

  Serial.print("the Current is:");
  Serial.print(V0);
  Serial.println("mA");

   ds2.start();                 //开始测量
  while (!ds2.ready())
  {
    delay(10);
    count++;
    if (count >= 100)
    { count == 0;
      break;
    }
  }
  Temp_read2 = ds2.get();  //读取温度              //读取温度

  if (0) {
    Temp2 = Temp2;
    Serial.println("Temperature2 error!");
    
  }
  else Temp2 = Temp_read2;
  Serial.print("the Temperature2 is:");
  Serial.print(Temp2);
  Serial.println("C");
   delay(500);
  ///////////////////////////////////////////////////////////////////
  ds1.start();                 //开始测量
  while (!ds1.ready())
  {
    delay(10);
    count++;
    if (count >= 100)
    { count == 0;
     // Serial.println("hello!");
      //delay(5000);
      break;
    }
  }
  Temp_read1 = ds1.get();            //读取温度

  if (0) {
    Temp1 = Temp1;
    Serial.println("Temperature1 error!");
  }
  else Temp1 = Temp_read1;
  Serial.print("the Temperature1 is:");
  Serial.print(Temp1);
  Serial.println("C");

 

  //TempMax=Temp2;
  LCDA.DisplayString(3, 3, wendu2, AR_SIZE(wendu2)); //第三行第一格开始，显示文字温度

  //TempMax=Temp1;
  LCDA.DisplayString(2, 3, wendu1, AR_SIZE(wendu1)); //第三行第一格开始，显示文字温度



  //max temperature
  Serial.print("the max Temperature is:");
  //Serial.print(TempMax);
  Serial.println("C");
  char temp[5];   //临时字符串用于输出数值到LCD
  char curr[4];
  delay(500);
  ///////////////////////////////////////////////////////////////////////////
  LCDA.DisplayString(1, 1, show0, AR_SIZE(show0)); //第二行第一格开始，显示文字电流

  dtostrf(V0, 1, 2, curr); //转换为字符串输出
  PrintLCD(1, 4, curr, 4);

  LCDA.DisplayString(0, 1, show2, AR_SIZE(show2));
  LCDA.DisplayString(1, 6, mA, AR_SIZE(mA));

  LCDA.DisplayString(2, 1, show1, AR_SIZE(show1)); //第2行第一格开始，显示文字温度
  LCDA.DisplayString(3, 1, show1, AR_SIZE(show1)); //第三行第一格开始，显示文字温度
  dtostrf(Temp1, 2, 2, temp); //转换为字符串输出
  PrintLCD(2, 4, temp, 5);
  dtostrf(Temp2, 2, 2, temp); //转换为字符串输出
  PrintLCD(3, 4, temp, 5);
  LCDA.DisplayString(2, 6, du, AR_SIZE(du)); //第三行第一格开始，显示文字温度
  LCDA.DisplayString(3, 6, du, AR_SIZE(du)); //第三行第一格开始，显示文字温度
  delay(100);
}


