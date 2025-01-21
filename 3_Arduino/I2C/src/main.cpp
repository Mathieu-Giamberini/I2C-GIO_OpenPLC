#include <Arduino.h>
#include <Wire.h>

const byte AW9523B = 0x58;       // 01011100
const byte AW_ID = 0x10;         // R
const byte AW_CONFIG_GCR = 0x11; // W/R
const byte AW_CONFIG_IO0 = 0x04; // W/R
const byte AW_CONFIG_IO1 = 0x05; // W/R
const byte AW_Q0 = 0x02;         // W/R
const byte AW_I1 = 0x01;         // R

byte read(byte addr, byte reg)
{
    /*Return the value of register 'reg' of the device 'addr'*/
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

void write(byte addr, byte reg, byte value)
{
    /*Write the 1 byte long value 'value' to the register 'reg' of the device 'addr'*/
    Wire.beginTransmission(addr);

    Wire.write(reg);
    Wire.write(value);

    Wire.endTransmission();
}

void connect(String label, byte addr, byte ID_reg, byte ID, bool logger = false)
{
    Serial.print("Conneting to ");
    Serial.print(label);
    while (read(addr, ID_reg) != ID)
    {
        if (logger)
        {
            Serial.println(read(addr, ID_reg), HEX);
        }
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected");
}

void AW_setup()
{ // Connecting, using the ID
    connect("AW9523B", AW9523B, AW_ID, 0x23);

    // Configuration
    // set to Push-Pull P0
    write(AW9523B, AW_CONFIG_GCR, 0x10); // 00010000
    // set 0 to out and 1 to in
    write(AW9523B, AW_CONFIG_IO0, 0x00); // all out
    write(AW9523B, AW_CONFIG_IO1, 0xFF); // all in
}

const byte RLY08 = 0x38; // 00111100
const byte RY_ID = 0x00; // The soft-version
const byte RY_CMD = 0x01;

void RY_setup()
{ // Connecting, using the ID

    connect("RLY08", RLY08, RY_ID, 0x05);
    write(RLY08, 0x01, 0xFF);
}

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    AW_setup();
    RY_setup();
}

bool getBit(byte b, int pos)
{
    return (b >> pos) & 0x01;
}

byte AW_I1_save = 0x00;
byte AW_I1_state = 0x00;
byte AW_I15_state = 0x00;
byte cmd;
void loop()
{
    AW_I1_state = read(AW9523B, AW_I1);

    if (AW_I1_save != AW_I1_state)
    {
        // Relays
        AW_I1_save = AW_I1_state;
        AW_I15_state = getBit(AW_I1_state, 5);

        Serial.print("PA0: ");
        Serial.println(AW_I15_state);
        write(AW9523B, AW_Q0, AW_I15_state << 2);

        // Relays
        //  Two equivalent implementation
        if (false)
        {
            write(RLY08, 0x00, AW_I15_state ? 0x68 : 0x72);
        }
        else
        {
            write(RLY08, 0x01, AW_I15_state << 3);
        }
    }
}