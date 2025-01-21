#include <Arduino.h>
#include <Wire.h>

const byte BNO055 = 0x28;
const byte PAGE = 0x07;

byte read(byte addr, byte reg)
{
  Wire.begin();
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(int(addr), 1);

  byte res;
  while (Wire.available())
  {
    res = Wire.read();
  }

  return res;
}

void setPage(byte addr, byte page)
{
  byte curentPage = read(addr, PAGE);

  if (page != curentPage)
  {
    Wire.begin();
    Wire.beginTransmission(addr);
    Wire.write(PAGE);
    Wire.write(page);
    Wire.endTransmission();
  }
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  // Set page 1
}

void loop()
{
  setPage(BNO055, 0);
  byte acc = read(BNO055, 0x00);

  Serial.println(acc, HEX);
  delay(500);
}