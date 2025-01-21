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
// FUNCTION_BLOCK TESTBLOCK1
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,LED)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DINT,TEST2)
  __DECLARE_VAR(INT,TEST1)
  __DECLARE_VAR(BYTE,ID)
  __DECLARE_VAR(INT,THREASHOLD)
  TEST TEST0;
  BNO055 BNO0550;
  __DECLARE_VAR(BOOL,_TMP_LE6_OUT)
  __DECLARE_VAR(BOOL,_TMP_EQ10_OUT)

} TESTBLOCK1;

void TESTBLOCK1_init__(TESTBLOCK1 *data__, BOOL retain);
// Code part
void TESTBLOCK1_body__(TESTBLOCK1 *data__);
// PROGRAM PROGRAM0
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  TESTBLOCK1 TESTBLOCK10;
  __DECLARE_LOCATED(BOOL,LED)

} PROGRAM0;

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain);
// Code part
void PROGRAM0_body__(PROGRAM0 *data__);
#endif //__POUS_H
