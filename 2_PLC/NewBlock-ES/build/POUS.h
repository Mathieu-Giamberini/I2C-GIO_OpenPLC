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
__DECLARE_ENUMERATED_TYPE(IN_OUT,
  IN_OUT__INPUT,
  IN_OUT__OUTPUT
)
__DECLARE_STRUCT_TYPE(AW9523B,
  BYTE ADDRESS;
    BOOL INIT;
    IN_OUT P0_0;
    IN_OUT P0_1;
    IN_OUT P0_2;
    IN_OUT P0_3;
    IN_OUT P0_4;
    IN_OUT P0_5;
    IN_OUT P0_6;
    IN_OUT P0_7;
    IN_OUT P1_0;
    IN_OUT P1_1;
    IN_OUT P1_2;
    IN_OUT P1_3;
    IN_OUT P1_4;
    IN_OUT P1_5;
    IN_OUT P1_6;
    IN_OUT P1_7;
  )
__DECLARE_STRUCT_TYPE(AW9523B_2,
  BYTE ADDRESS;
    BOOL INIT;
    BYTE P1;
    BYTE P2;
  )
__DECLARE_DERIVED_TYPE(DATATYPE1,BOOL)
__DECLARE_STRUCT_TYPE(RLY08,
  BYTE CURRENTADRESS;
    BYTE WANTADDRESS;
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
// PROGRAM NEWBLOCK
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  DI_1 DI_10;
  __DECLARE_VAR(DINT,DI_11)
  DQ_1 DQ_10;
  DI_8 DI_80;
  DQ_8 DQ_81;
  RLY_1 RLY_10;
  RLY_8 RLY_80;
  __DECLARE_EXTERNAL(AW9523B,BOARD1)
  __DECLARE_EXTERNAL(BOOL,Q1)
  __DECLARE_EXTERNAL(BOOL,Q2)
  __DECLARE_EXTERNAL(BOOL,Q3)
  __DECLARE_EXTERNAL(BOOL,BP1)
  __DECLARE_EXTERNAL(BOOL,LED1)
  __DECLARE_EXTERNAL(BOOL,KM1)
  __DECLARE_EXTERNAL(BOOL,KM2)
  __DECLARE_EXTERNAL(BOOL,KM3)
  __DECLARE_EXTERNAL(BOOL,M4)
  __DECLARE_EXTERNAL(BOOL,L1)
  __DECLARE_EXTERNAL(BOOL,L2)
  __DECLARE_EXTERNAL(BOOL,L3)

} NEWBLOCK;

void NEWBLOCK_init__(NEWBLOCK *data__, BOOL retain);
// Code part
void NEWBLOCK_body__(NEWBLOCK *data__);
// PROGRAM INITBLOCK
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_EXTERNAL(AW9523B,BOARD1)

} INITBLOCK;

void INITBLOCK_init__(INITBLOCK *data__, BOOL retain);
// Code part
void INITBLOCK_body__(INITBLOCK *data__);
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
