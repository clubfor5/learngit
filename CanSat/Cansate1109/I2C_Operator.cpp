#include <Arduino.h>
#include "I2C_Operator.h"
#include "config.h"
#include <Wire.h>

I2C_Operator::I2C_Operator() {}

void *I2C_Operator::I2C_Require(float *cache_float, uint8_t destination, uint8_t command, uint8_t floatNumber) {
  
  if (floatNumber>8) {
    floatNumber = 8;
  }
  
  Wire.beginTransmission(destination); 
  Wire.write(command);
  Wire.endTransmission( );
  Wire.requestFrom(destination,(uint8_t)(floatNumber<<2));
  
  uint8_t count = 0;
  
  while (Wire.available()) {
    cache[count++] = Wire.read();
    
    #ifdef TEST_MODE
      Serial.write(cache[count-1]);
    #endif
  }
  
  memcpy(cache_float, cache, sizeof(cache));
}

void *I2C_Operator::I2C_Require(int *cache_int, uint8_t destination, uint8_t command, uint8_t intNumber) {
  if (intNumber>16) {
    intNumber = 16;
  }
  
  Wire.beginTransmission(destination); 
  Wire.write(command);
  Wire.endTransmission( );
  Wire.requestFrom(destination,(uint8_t)(intNumber<<1));
  uint8_t count = 0;
  
  while (Wire.available()) {
    cache[count++] = Wire.read();
    
    #ifdef TEST_MODE
      Serial.write(cache[count-1]);
    #endif
  }

  memcpy(cache_int, cache, sizeof(cache));
}

void *I2C_Operator::I2C_Require(uint8_t *cache_int, uint8_t destination, uint8_t command, uint8_t intNumber) {
  if (intNumber>32) {
    intNumber = 32;
  }
  
  Wire.beginTransmission(destination); 
  Wire.write(command);
  Wire.endTransmission( );
  Wire.requestFrom(destination,(uint8_t)intNumber);
  uint8_t count = 0;
  
  while (Wire.available()) {
    cache[count++] = Wire.read();
    
    #ifdef TEST_MODE
      Serial.write(cache[count-1]);
    #endif
  }

  memcpy(cache_int, cache, sizeof(cache));
}

void *I2C_Operator::I2C_WIFICOM(uint8_t* cache_com, float* posture_temp, uint8_t destination) {
  uint8_t cache[12];
  uint8_t count = 0;
  Wire.beginTransmission(destination); 
  Wire.write(RECEIVE_COMMAND);
  Wire.endTransmission();
  Wire.requestFrom(destination,(uint8_t)2);
  while (Wire.available()) {
    cache[count++] = Wire.read();
 
  }
  
/*  memcpy(cache_com, cache, 2);
  if ((cache[0] == POSTURE_BOARD) && (cache[1] == TARGET_POSTURE)) {
    Wire.beginTransmission(destination); 
    Wire.write(RECEIVE_POSTURE);
    Wire.endTransmission();
    Wire.requestFrom(destination,(uint8_t)12);
    count = 0;
    while (Wire.available()) {
      cache[count++] = Wire.read();
    }
    memcpy(posture_temp,cache,12);
  }*/
}

void I2C_Operator::I2C_Command(uint8_t destination, uint8_t command) {
  Wire.beginTransmission(destination); 
  Wire.write(command);
  Wire.endTransmission();
  Wire.requestFrom(destination,(uint8_t)1);
  uint8_t temp = Wire.read();
}

/*void I2C_Operator::I2C_Report(uint8_t *errorID, uint8_t destination, uint8_t command) {
  Wire.beginTransmission(destination); 
  Wire.write(REPORT_ERROR);
  Wire.endTransmission();
  Wire.requestFrom(destination,(uint8_t)1);
  *errorID = Wire.read();
}*/

void I2C_Operator::I2C_Send(uint8_t destination, uint8_t command, uint8_t* data, uint8_t dataNumber) {
  Wire.beginTransmission(destination); 
  Wire.write(command);
  for (uint8_t temp = 0; temp < dataNumber; temp++) {
    Wire.write(data[temp]);
  }
  Wire.endTransmission();
}

