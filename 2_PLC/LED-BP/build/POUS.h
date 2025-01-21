#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM PLUS10
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(INT,COUNT)
  __DECLARE_LOCATED(BOOL,BP)
  TEST TEST0;
  __DECLARE_VAR(BYTE,TEST1)
  __DECLARE_VAR(BOOL,BP1)
  __DECLARE_VAR(BOOL,LED1)
  __DECLARE_VAR(BOOL,KM1)
  __DECLARE_VAR(BOOL,KM2)
  __DECLARE_VAR(BOOL,KM3)
  __DECLARE_VAR(BOOL,M4)
  __DECLARE_VAR(BOOL,L1)
  __DECLARE_VAR(BOOL,L2)
  __DECLARE_VAR(BOOL,L3)
  __DECLARE_VAR(BOOL,Q1)
  __DECLARE_VAR(BOOL,Q2)
  __DECLARE_VAR(BOOL,Q3)
  DI_1 DI_10;
  DQ_1 DQ_10;
  DI_8 DI_80;
  DQ_8 DQ_81;
  RLY_1 RLY_10;
  RLY_8 RLY_80;

} PLUS10;

void PLUS10_init__(PLUS10 *data__, BOOL retain);
// Code part
void PLUS10_body__(PLUS10 *data__);
// PROGRAM LED_BP
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(BOOL,BP1)
  __DECLARE_LOCATED(BOOL,LED)

} LED_BP;

void LED_BP_init__(LED_BP *data__, BOOL retain);
// Code part
void LED_BP_body__(LED_BP *data__);
#endif //__POUS_H
