#include <Wire.h>

// Declare external C++/C function
extern "C" byte read(byte addr, byte reg);
extern "C" void write(byte addr, byte reg, byte value);
extern "C" void write_bit(byte addr, byte reg, byte n, bool value);

extern "C" void print_hex_on_serial(byte num);
extern "C" bool getBit(byte b, int pos);
extern "C" void print(String text);

bool getBit(byte b, int pos)
{
    return (b >> pos) & 0x01;
}

// Return the value of register 'reg' of the device 'addr'
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

// Write the 1 byte long value 'value' to the register 'reg' of the device 'addr'
void write(byte addr, byte reg, byte value)
{
    Wire.beginTransmission(addr);

    Wire.write(reg);
    Wire.write(value);

    Wire.endTransmission();
}

// Write the bit number 'n' of the reg 'reg' without altering the others
void write_bit(byte addr, byte reg, byte n, bool value)
{
    byte pos = 0x01 << n;

    byte old_config = read(addr, reg);
    byte new_config = old_config & (~pos) | pos * value;
    // set to zero and the to the wanted value

    write(addr, reg, new_config);
}

// begin the serial if it isn't already
bool first_serial = true;
void serial_begin()
{
    if (first_serial)
    {
        Serial.begin(115200);
        first_serial = false;
    }
}

// Serial print byte in hexadecimal
void print_hex_on_serial(byte num)
{
    serial_begin();
    Serial.println(num, HEX);
}

void print(String text)
{
    serial_begin();
    Serial.println(text);
}