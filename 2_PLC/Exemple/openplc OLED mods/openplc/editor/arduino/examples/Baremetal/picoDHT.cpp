#include "PicoDHT.h"

DHT::DHT(uint8_t pin) {
  _pin = pin;
  _temperature = 0;
  _humidity = 0;

  pinMode(_pin, INPUT);
  digitalWrite(_pin, HIGH);
}

int8_t DHT::getHumidity() {
	return _humidity;
}	

int16_t DHT::getTemperature() {
	return _temperature;
}

int DHT::read()
{

  // INIT BUFFERVAR TO RECEIVE DATA
  uint8_t mask = 0x80;
  uint8_t idx = 0;

  // EMPTY BUFFER
  for (uint8_t i = 0; i < 5; i++) _bits[i] = 0;

  // REQUEST SAMPLE - SEND WAKEUP TO SENSOR
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);

  // WAKE UP - add 10% extra for timing inaccuracies in sensor.
  uint32_t startWakeup = micros();
  do
  {
    // HANDLE PENDING IRQ
    yield();
    // 180 gives good wakeup delay on UNO for DHT22 / DHT11 (issue #72)
    delayMicroseconds(180UL);  
  }
  while((micros() - startWakeup) < (18 * 1100UL));

  // HOST GIVES CONTROL TO SENSOR
  digitalWrite(_pin, HIGH);
  delayMicroseconds(2);
  pinMode(_pin, INPUT_PULLUP);

  // DHT11
  // SENSOR PULLS LOW after 6000-10000 us
  if (_waitFor(LOW, 15000UL)) return DHT_ERROR_NOT_READY;

  // SENSOR STAYS LOW for ~80 us => or TIMEOUT
  if (_waitFor(HIGH, 90)) return DHT_ERROR_TIMEOUT_A;

  // SENSOR STAYS HIGH for ~80 us => or TIMEOUT
  if (_waitFor(LOW, 90)) return DHT_ERROR_TIMEOUT_B;

  // SENSOR HAS NOW SEND ACKNOWLEDGE ON WAKEUP
  // NOW IT SENDS THE BITS

  // READ THE OUTPUT - 40 BITS => 5 BYTES
  for (uint8_t i = 40; i != 0; i--)
  {
    // EACH BIT START WITH ~50 us LOW
    if (_waitFor(HIGH, 90)) 
    {
      // Most critical timeout
      // Serial.print("IC: ");
      // Serial.println(i);
      return DHT_ERROR_TIMEOUT_C;
    }

    // DURATION OF HIGH DETERMINES 0 or 1
    // 26-28 us ==> 0
    //    70 us ==> 1
    uint32_t t = micros();
    if (_waitFor(LOW, 90))
    {
      // Serial.print("ID: ");
      // Serial.println(i);
      return DHT_ERROR_TIMEOUT_D;
    }
    
    // bits are timing based (datasheet)
    // 26-28us ==> 0
    // 70 us   ==> 1
    // See https://github.com/RobTillaart/DHTNew/issues/11
    if ((micros() - t) > 50)
    {
      _bits[idx] |= mask;
    }

    // PREPARE FOR NEXT BIT
    mask >>= 1;
    if (mask == 0)   // next byte?
    {
      mask = 0x80;
      idx++;
    }
  }
  // After 40 bits the sensor pulls the line LOW for 50 us
  // No functional need to wait for this one
  // if (_waitFor(HIGH, 60)) return DHTLIB_ERROR_TIMEOUT_E;

  // CATCH RIGHTSHIFT BUG ESP (only 1 single bit shift)
  // humidity is maximum 1000 = 0x03E8 for DHT22 and 0x6400 for DHT11
  // so most significant bit may never be set.
  _humidity    = -1;
  _temperature = -999;
  
  if (_bits[0] & 0x80) return DHT_ERROR_BIT_SHIFT;

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
  //_lastRead = millis();

  _humidity    = _bits[0]; //+ _bits[1] * 0.1;
  _temperature = (int16_t)_bits[2];// + _bits[3] * 0.1;
  // TEST CHECKSUM
  uint8_t sum = _bits[0] + _bits[1] + _bits[2] + _bits[3];
  if (_bits[4] != sum)
  {
    return DHT_ERROR_CHECKSUM;
  }
  return DHT_OK;
}

// returns true  if timeout has passed.
// returns false if timeout is not reached and state is seen.
bool DHT::_waitFor(uint8_t state, uint32_t timeout)
{
  uint32_t start = micros();
  uint8_t  count = 2;
  while ((micros() - start) < timeout)
  {
    if (digitalRead(_pin) == state)
    {
      count--;
      if (count == 0) return false;  // requested state seen count times
    }
  }
  return true;
}