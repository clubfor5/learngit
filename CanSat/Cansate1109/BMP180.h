#ifndef BMP180_H
#define BMP180_H

#include <Arduino.h>
#include <Wire.h>



class BMP180 {
  public:
    BMP180();
    void printDate(uint8_t* bmpDate);
    void bmp085Calibration();
  private:   
    float bmp085GetTemperature(unsigned int ut);
    long bmp085GetPressure(unsigned long up); 
    float calcAltitude(float pressure);
    char bmp085Read(unsigned char address);
    int bmp085ReadInt(unsigned char address);
    unsigned int bmp085ReadUT();
    unsigned long bmp085ReadUP();
    void writeRegister(int deviceAddress, byte address, byte val);
    int readRegister(int deviceAddress, byte address);
};

#endif
