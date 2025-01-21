#ifndef _AW9523B_H_
#define _AW9523B_H_

#include "DEV_Config.h"
#include "Debug.h"
#include "DEV_Config.h"

#define AW9523B_ADDR       (0x58)
#define INT_PIN             2


/***********************************************************************************/
UBYTE AW9523B_Init(void);
UBYTE ReadIntPin(void);


void PortMode(UBYTE port, UBYTE mode);
UBYTE PortInput(UBYTE port);
void PortOutput(UBYTE port, UBYTE val);
void PortInt(UBYTE port, UBYTE en);
void PortIntClear(UBYTE port);
void PinMode(UBYTE port, UBYTE pin, UBYTE mode);
UBYTE PortInput(UBYTE port, UBYTE pin);
void PinOutput(UBYTE port, UBYTE pin, UBYTE val);
void PortInt(UBYTE port, UBYTE pin, UBYTE en);
void PortCtrl(UBYTE gpomd, UBYTE isel);
void LEDModeSwitch(UBYTE port, UBYTE mode);
void LEDDims(UBYTE lednum, UBYTE i);

#endif
