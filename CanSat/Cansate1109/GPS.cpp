#include "GPS.h"
GPS::GPS(){};
#ifdef GPS_SOFTWARESERIAL
bool GPS::begin(SoftwareSerial &uart, long frequency)  
{   
    m_puart = &uart;
    m_puart->begin(frequency);
    return (uart); //检测串口是否打开
}
#else
bool begin(HardwareSerial &uart, long frequency) 
{   m_puart = &uart;
    m_puart->begin(frequency);
    return (uart); //检测串口是否打开
}
#endif

uint8_t GPS::receiveChar()
{
    if (m_puart->available())
        return m_puart->read();
    else
        return 0;
}

bool GPS::getLL()
{
   if(receiveChar() == 'L')
   {  
     delay(1);//等待下一个'L'
     if(receiveChar() == 'L')
     return true;
   }
   return false;
}

bool GPS::getLat()
{   int timeCount = 0;
    while(!m_puart->available())
    {
       timeCount++;
       delay(1);
       if(timeCount == 1000)
       break; 
     }
    int count;
    while(count!=500)
    {
      if(!m_puart->available()) 
        {
         delayMicroseconds(20);
         count++; 
         continue;
        }
      count = 0;
      if(getLL())               
       break;
    }
   char buff[32];
   for(int i = 0;i<32; i++)
   { 
      buff[i] = receiveChar();
      delay(1);        
   }
  Lat[0] = buff[12];
  Lat[1] = (buff[1] - 48) * 10 + buff[2] - 48;
  Lat[2] = (buff[3] - 48) * 10 + buff[4] - 48;
  Lat[3] = buff[6] * 6 + buff[7] * 0.6;
  Lat[4] = buff[26];
  Lat[5] = (buff[14] - 48) * 100 + (buff[15] - 48) * 10 + buff[16] - 48;
  Lat[6] = (buff[17] - 48) * 10 + buff[18] - 48;
  Lat[7] = buff[20] * 6 + buff[21] * 0.6;
  if (Lat[0] == 'N' || Lat[0] == 'S')
    return true;
  return false;
}

char* GPS::getData()
{   
    char data[8];
    for(int i = 0; i<8;i++)
      data[i] = 0;
    if(getLat())
    return Lat;
    else
    return data;
}
