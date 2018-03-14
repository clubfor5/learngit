#ifndef GPS_H
#define GPS_H
#define GPS_SOFTWARESERIAL

#ifdef GPS_SOFTWARESERIAL
#include <SoftwareSerial.h>
#endif
#include <Arduino.h>
class GPS
{
private:
   bool getLL();
   /*
      接收"LL"字符，没有串口数据或者收到不为"LL"则返回假，否则返回真。    
   */
   bool getLat();
   /*
       将经纬度数据存储到Lat[8]中。
   */
   char Lat[8];
   uint8_t receiveChar();
   /***
         如果串口有数据，读取，否则返回0；
   ***/
   #ifdef GPS_SOFTWARESERIAL
    SoftwareSerial *m_puart; /* The UART to communicate with ESP8266 */
   #else
    HardwareSerial *m_puart; /* The UART to communicate with ESP8266 */  
   #endif
public:
  GPS();
  /****定义初始化函数****/
  #ifdef GPS_SOFTWARESERIAL
  bool begin(SoftwareSerial &uart,long frequency);
  #else
  bool begin(HardwareSerial &uart,long frequency);
  #endif
  char* getData();

};
#endif

