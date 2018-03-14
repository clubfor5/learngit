#ifndef TIME_H  
#define TIME_H

#include <Arduino.h>
#include "DS3231.h"

class Time  {
private:   
  DS3231 ds3231;
  uint8_t date[7];
  
public:
  Time();
  void setTime(uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DoW, int Hour, uint8_t Minute, uint8_t Second);
  void readTime(uint8_t *timeDate);
  void getDate(uint8_t* tempDate);
  void getTemperature(uint8_t *temper);
};

#endif 
