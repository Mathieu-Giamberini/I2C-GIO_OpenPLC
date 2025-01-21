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
// PROGRAM LED_TEST1
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  DI_1 DI_10;
  DQ_8 DQ_80;
  RLY_1 RLY_10;
  RLY_1 RLY_11;
  RLY_1 RLY_12;
  __DECLARE_VAR(BOOL,_TMP_NOT19_OUT)

} LED_TEST1;

void LED_TEST1_init__(LED_TEST1 *data__, BOOL retain);
// Code part
void LED_TEST1_body__(LED_TEST1 *data__);
// PROGRAM LED_TEST2
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  DI_8 DI_80;
  DQ_1 DQ_10;
  RLY_8 RLY_80;

} LED_TEST2;

void LED_TEST2_init__(LED_TEST2 *data__, BOOL retain);
// Code part
void LED_TEST2_body__(LED_TEST2 *data__);
#endif //__POUS_H
