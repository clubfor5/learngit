#include <Wire.h>
#include <SPI.h>
#include "LoRa.h"
#define DEBUG
#define COMMUNICATE_BOARD 0x12

uint8_t data[51], dataCount;

void receiveEvent(int howMany);
bool flag = false;

void setup() {
  Wire.begin(COMMUNICATE_BOARD);
  Wire.onReceive(receiveEvent);
  /****开启Debug模式用串口输出*****/
#ifdef DEBUG
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");
#endif
  /****开启Debug模式用串口输出*****/
  if (!LoRa.begin(433E6))
  {
    /****开启Debug模式用串口输出*****/
#ifdef DEBUG
    Serial.println("Starting LoRa failed!");
#endif
    /****开启Debug模式用串口输出*****/
    while (1); //掉入死循环
  }
}

void loop() {
  if (flag)
  {
    LoRa.beginPacket();
    for (int i = 0; i < 51; i++)
    {
      LoRa.print((char)data[i]);
      /****开启Debug模式用串口输出*****/
#ifdef DEBUG
      Serial.print(data[i]);
      Serial.print(" ");
#endif
      /****开启Debug模式用串口输出*****/
    }
    LoRa.endPacket();
#ifdef DEBUG
    Serial.println();
#endif
    flag = false;
  }
}

void receiveEvent(int howMany) {
  switch (howMany)
  {
    case 32:
      for (dataCount = 0; dataCount < 32; dataCount++)
        data[dataCount] = Wire.read();
      break;
    case 19:
      for (dataCount = 32; dataCount < 51; dataCount++)
        data[dataCount] = Wire.read();
      if (data[0] == 0xff && data[50] == 0xff)
        flag = true;
      break;
    default: break;
  }

}


