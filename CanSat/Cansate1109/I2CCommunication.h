#ifndef I2CCOMMUNICATION_H
#define I2CCOMMUNICATION_H

#include <Arduino.h>
#include <Wire.h>

class I2CCom{
  public:
    I2CCom();
    void powerReceive();
    void communicateReceive();
  private:
   unsigned char cache[32];
};


#endif
