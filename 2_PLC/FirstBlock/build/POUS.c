void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void TESTBLOCK1_init__(TESTBLOCK1 *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TEST2,0,retain)
  __INIT_VAR(data__->TEST1,0,1)
  __INIT_VAR(data__->LED,0,retain)
  __INIT_VAR(data__->ID,160,1)
  __INIT_VAR(data__->THREASHOLD,20,1)
  TEST_init__(&data__->TEST0,retain);
  BNO055_init__(&data__->BNO0550,retain);
  __INIT_VAR(data__->_TMP_LE6_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ10_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void TESTBLOCK1_body__(TESTBLOCK1 *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_LE6_OUT,,LE__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_VAR(data__->TEST1,),
    (INT)__GET_VAR(data__->THREASHOLD,)));
  __SET_VAR(data__->TEST0.,I0,,__GET_VAR(data__->TEST1,));
  __SET_VAR(data__->TEST0.,ACTIVE,,__GET_VAR(data__->_TMP_LE6_OUT,));
  TEST_body__(&data__->TEST0);
  __SET_VAR(data__->,TEST1,,__GET_VAR(data__->TEST0.OUT,));
  BNO055_body__(&data__->BNO0550);
  __SET_VAR(data__->,_TMP_EQ10_OUT,,EQ__BOOL__BYTE(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BYTE)__GET_VAR(data__->BNO0550.CHIP_ID,),
    (BYTE)__GET_VAR(data__->ID,)));
  __SET_VAR(data__->,LED,,__GET_VAR(data__->_TMP_EQ10_OUT,));

  goto __end;

__end:
  return;
} // TESTBLOCK1_body__() 





void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  TESTBLOCK1_init__(&data__->TESTBLOCK10,retain);
  __INIT_LOCATED(BOOL,__QX0_0,data__->LED,retain)
  __INIT_LOCATED_VALUE(data__->LED,__BOOL_LITERAL(FALSE))
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  TESTBLOCK1_body__(&data__->TESTBLOCK10);
  __SET_LOCATED(data__->,LED,,__GET_VAR(data__->TESTBLOCK10.LED,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





