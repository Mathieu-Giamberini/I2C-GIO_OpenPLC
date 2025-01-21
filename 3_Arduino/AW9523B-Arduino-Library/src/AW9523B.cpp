#include "AW9523B.h"

#define DEBUGPRINT 0

void PortMode(UBYTE port, UBYTE mode)
{
    if(DEBUGPRINT == 1) {
        Serial.print("set port:");
        Serial.print(port);
        Serial.print(" mode = ");
        Serial.println(mode==0?"out":"in");
    }
    I2C_Write_Byte(port==0? 0x04:0x05, mode==0?0:0xff);
}

UBYTE PortInput(UBYTE port)
{
    UBYTE indata = I2C_Read_Byte(port==0? 0x00:0x01);
    if(DEBUGPRINT == 1) {
        Serial.print("input port:");
        Serial.println(indata);
    }
    return indata;
}

void PortOutput(UBYTE port, UBYTE val)
{
    if(DEBUGPRINT == 1) {
        Serial.print("output port:");
        Serial.print(port);
        Serial.print(" val = ");
        Serial.println(val);
    }
    I2C_Write_Byte(port==0? 0x02:0x03, val);
}

void PortInt(UBYTE port, UBYTE en)
{
    if(DEBUGPRINT == 1) {
        Serial.print("enable port:");
        Serial.print(port);
        Serial.print(" int");
        Serial.println(en==0?"enable":"disenable");
    }
    I2C_Write_Byte(port==0? 0x06:0x07, en);
}

void PortIntClear(UBYTE port)
{
    if(DEBUGPRINT == 1) {
        Serial.print("clear port:");
        Serial.println(port);
    }
    I2C_Read_Byte(port==0? 0x06:0x07);
}

void PinMode(UBYTE port, UBYTE pin, UBYTE mode)
{
    I2C_Write_Byte(port==0? 0x04:0x05, mode<<pin);
}

UBYTE PortInput(UBYTE port, UBYTE pin)
{
    UBYTE indata = I2C_Read_Byte(port==0? 0x00:0x01);
    return indata&(1<<pin);
}

void PinOutput(UBYTE port, UBYTE pin, UBYTE val)
{
    I2C_Write_Byte(port==0? 0x02:0x03, val<<pin);
}

void PortInt(UBYTE port, UBYTE pin, UBYTE en)
{
    I2C_Write_Byte(port==0? 0x06:0x07, en<<pin);
}

// #gpomd=D[4]:0-Open-Drain 1-Push-Pull; just p0
// #iseld[1:0]:00-11(IMAX×1/4,IMAX×2/4, IMAX×3/4,IMAX)
void PortCtrl(UBYTE gpomd, UBYTE isel)
{
    UBYTE g,s,val;

    g = gpomd << 4;
    s = isel << 2;
    val = g | s;
    I2C_Write_Byte(0x11, val);
}

void LEDModeSwitch(UBYTE port, UBYTE mode)
{
    I2C_Write_Byte(port==0? 0x12:0x13, mode==0?0:0xff);
}

void LEDDims(UBYTE lednum, UBYTE i)
{
    I2C_Write_Byte(lednum, i);
}

/******************************************************************************
  function:	TSL2591 Initialization
  parameter:
  Info:
******************************************************************************/
UBYTE AW9523B_Init(void)
{
    DEV_ModuleInit();
    DEV_I2C_Init(AW9523B_ADDR);

    Serial.print("AW9523B Init\r\n");

    UBYTE id = I2C_Read_Byte(0x10);
    if(id != 0x23) { // 0x3220
        Serial.print("feature set should = 0x23, but val = 0X");
        Serial.println(id, HEX);
        return 1;
    } else {
        Serial.print("find AW9523B, ID = 0x");
        Serial.println(id, HEX);
    }

    LEDModeSwitch(0, 1);//set out mode gpio
    PortCtrl(1, 0); //set all gpio Push-Pull
    LEDModeSwitch(1, 1);//set out mode gpio

    DEV_GPIO_Mode(INT_PIN, 0);
    // PortMode(1, 1);
    // PortInput(1);
    return 0;
}

UBYTE ReadIntPin(void)
{
    return DEV_Digital_Read(INT_PIN);
}



