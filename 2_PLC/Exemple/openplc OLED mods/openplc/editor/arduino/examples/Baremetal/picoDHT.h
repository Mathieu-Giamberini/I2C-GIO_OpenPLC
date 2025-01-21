#ifndef DHT_H
#define DHT_H
#include "Arduino.h"

#define DHT_OK                         0
#define DHT_ERROR_CHECKSUM            -1
#define DHT_ERROR_TIMEOUT_A           -2
#define DHT_ERROR_BIT_SHIFT           -3
#define DHT_ERROR_NOT_READY           -4
#define DHT_ERROR_TIMEOUT_C           -5
#define DHT_ERROR_TIMEOUT_D           -6
#define DHT_ERROR_TIMEOUT_B           -7
#define DHT_PENDING                   -8

class DHT {
private:
  int16_t _temperature;
  int8_t _humidity;
  //uint8_t data[6];
  uint8_t _bits[5];
  uint8_t _pin;

  bool _waitFor(uint8_t state, uint32_t timeout);  
public:
  DHT(uint8_t pin);

  int16_t getTemperature();
  int8_t getHumidity();
  int read(void);
};
#endif
