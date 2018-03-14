#include "Time.h"
#include "Config.h"
#include <Wire.h>
float Temperature;
Time::Time() {
  //pinMode(LED_RTC, OUTPUT);
}

void Time::setTime(uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DoW, int Hour, uint8_t Minute, uint8_t Second) {
 // digitalWrite(LED_RTC, HIGH);
  ds3231.setYear(Year);
  ds3231.setMonth(Month);
  ds3231.setDate(Date);
  ds3231.setDoW(DoW);
  ds3231.setHour(Hour);
  ds3231.setMinute(Minute);
  ds3231.setSecond(Second); 
 // digitalWrite(LED_RTC, LOW);
}

void Time::readTime(uint8_t *timeDate) { 
 // digitalWrite(LED_RTC, HIGH);
  ds3231.getTime(date[0], date[1], date[2], date[3], date[4], date[5], date[6]);
//  digitalWrite(LED_RTC, LOW);
  memcpy(timeDate,date,7);
 /* Serial.print("20");
    if (date[0]<10) { 
    Serial.print('0');
  }
  Serial.print(date[0]);
  Serial.print("-");                                                                                                                                                                                                                                    
  if (date[1]<10) { 
    Serial.print('0');
  }
  Serial.print(date[1]);
  Serial.print("-");
  if (date[2]<10) { 
    Serial.print('0');
  }
  Serial.print(date[2]);
  
  Serial.print("  ");
  Serial.print(date[4], DEC);
  Serial.print(":");
  Serial.print(date[5], DEC);
  Serial.print(":");
  Serial.print(date[6], DEC);
  Serial.println();
*/
}
void Time::getTemperature(uint8_t *temper)
{ 
  float *temp;
   *temp=ds3231.getTemperature();
   Temperature=*temp;
  // Serial.println(Temperature);
   memcpy(temper,&Temperature,4);
}
void Time::getDate(uint8_t* tempDate) {
 // digitalWrite(LED_RTC, HIGH);
  memcpy(tempDate, date, 7);
  //digitalWrite(LED_RTC, LOW);
}

