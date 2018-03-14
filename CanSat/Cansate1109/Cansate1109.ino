#include  <Wire.h>
#include "config.h"
#include "Time.h"
#include "BMP180.h"
#include "GPS.h"
#define DEBUG
Time time;
BMP180 bmp;
uint8_t dataBag[51];
uint16_t count = 0;
GPS GPS;
SoftwareSerial gpsSerial = SoftwareSerial(5,6);
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  bmp.bmp085Calibration();
  GPS.begin(gpsSerial,9600);
 
}

void packData()
{
  /**********0xff 数据次数 时间 高度和气压 GPS 温度 电源板数据 结束*******************/
  dataBag[0] = 0xff;
  memcpy(dataBag+1,&count,2);
  time.readTime(dataBag+3);
  bmp.printDate(dataBag+10);
  memcpy(dataBag+22,GPS.getData(),8);
  time.getTemperature(dataBag+30);
  Wire.requestFrom(POWER_BOARD, 16);
  while (Wire.available()) {
    for (int i = 34; i < 50; i++)
    {
      dataBag[i] = Wire.read();
    }
    dataBag[50] = 0xff;
  }
  count++;
}
void sendData()
{
  Wire.beginTransmission(COMMUNICATE_BOARD);
  for (int i = 0; i < 32; i++) {
    Wire.write(dataBag[i]); delay(1);
  }
  Wire.endTransmission();
  Wire.beginTransmission(COMMUNICATE_BOARD);
  for (int i = 32; i < 51; i++) {
    Wire.write(dataBag[i]); delay(1);
  }
  Wire.endTransmission();
}

void debugPrint()
{
  for (int i = 0; i < 51; i++)
  {
    Serial.print(dataBag[i]);
    Serial.print(" ");
  }
  Serial.println();
}
void loop() {
  packData();
  sendData();
  #ifdef DEBUG
  debugPrint();
  #endif
}
