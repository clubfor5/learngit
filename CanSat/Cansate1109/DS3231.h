#ifndef DS3231_h
#define DS3231_h

#include <Arduino.h>
#include <Wire.h>

class DS3231 {
  public:
    DS3231();
    void getTime(uint8_t& year, uint8_t& month, uint8_t& date, uint8_t& DoW, uint8_t& hour, uint8_t& minute, uint8_t& second); 
    uint8_t getSecond(); 
    uint8_t getMinute(); 
    uint8_t getHour(bool& h12, bool& PM); 
    uint8_t getDoW(); 
    uint8_t getDate(); 
    uint8_t getMonth(bool& Century); 
    uint8_t getYear(); 
    void setSecond(uint8_t Second); 
    void setMinute(uint8_t Minute); 
    void setHour(uint8_t Hour); 
    void setDoW(uint8_t DoW); 
    void setDate(uint8_t Date); 
    void setMonth(uint8_t Month); 
    void setYear(uint8_t Year); 
    void setClockMode(bool h12); 
    float getTemperature(); 
    void getA1Time(uint8_t& A1Day, uint8_t& A1Hour, uint8_t& A1Minute, uint8_t& A1Second, uint8_t& AlarmBits, bool& A1Dy, bool& A1h12, bool& A1PM); 
    void getA2Time(uint8_t& A2Day, uint8_t& A2Hour, uint8_t& A2Minute, uint8_t& AlarmBits, bool& A2Dy, bool& A2h12, bool& A2PM); 
    void setA1Time(uint8_t A1Day, uint8_t A1Hour, uint8_t A1Minute, uint8_t A1Second, uint8_t AlarmBits, bool A1Dy, bool A1h12, bool A1PM); 
    void setA2Time(uint8_t A2Day, uint8_t A2Hour, uint8_t A2Minute, uint8_t AlarmBits, bool A2Dy, bool A2h12, bool A2PM); 
    void turnOnAlarm(uint8_t Alarm); 
    void turnOffAlarm(uint8_t Alarm); 
    bool checkAlarmEnabled(uint8_t Alarm); 
    bool checkIfAlarm(uint8_t Alarm); 
    void enableOscillator(bool TF, bool battery, uint8_t frequency); 
    void enable32kHz(bool TF); 
    bool oscillatorCheck();;
  private:
    uint8_t decToBcd(uint8_t val); 
    uint8_t bcdToDec(uint8_t val); 
    uint8_t readControluint8_t(bool which); 
    void writeControluint8_t(uint8_t control, bool which); 
};

#endif
