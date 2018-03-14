#ifndef I2C_OPERATOR_H  
#define I2C_OPERATOR_H

class I2C_Operator {
private:    
  unsigned char cache[32];

public:
  I2C_Operator();
  void *I2C_WIFICOM(uint8_t* cache_com, float* posture_temp, uint8_t destination);
  void I2C_Report(uint8_t *errorID, uint8_t destination, uint8_t command);
  void I2C_Command(uint8_t destination, uint8_t command);
  void* I2C_Require(float *cache_float, uint8_t destination, uint8_t command, uint8_t floatNumber);
  void* I2C_Require(int *cache_int, uint8_t destination, uint8_t command, uint8_t intNumber);
  void* I2C_Require(uint8_t *cache_int, uint8_t destination, uint8_t command, uint8_t intNumber);
  void I2C_Send(uint8_t destination, uint8_t command, uint8_t* data, uint8_t dataNumber);
};

#endif 
