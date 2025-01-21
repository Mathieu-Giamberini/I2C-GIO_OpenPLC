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





void NEWBLOCK_init__(NEWBLOCK *data__, BOOL retain) {
  DI_1_init__(&data__->DI_10,retain);
  __INIT_VAR(data__->DI_11,0,retain)
  DQ_1_init__(&data__->DQ_10,retain);
  DI_8_init__(&data__->DI_80,retain);
  DQ_8_init__(&data__->DQ_81,retain);
  RLY_1_init__(&data__->RLY_10,retain);
  RLY_8_init__(&data__->RLY_80,retain);
  __INIT_EXTERNAL(AW9523B,BOARD1,data__->BOARD1,retain)
  __INIT_EXTERNAL(BOOL,Q1,data__->Q1,retain)
  __INIT_EXTERNAL(BOOL,Q2,data__->Q2,retain)
  __INIT_EXTERNAL(BOOL,Q3,data__->Q3,retain)
  __INIT_EXTERNAL(BOOL,BP1,data__->BP1,retain)
  __INIT_EXTERNAL(BOOL,LED1,data__->LED1,retain)
  __INIT_EXTERNAL(BOOL,KM1,data__->KM1,retain)
  __INIT_EXTERNAL(BOOL,KM2,data__->KM2,retain)
  __INIT_EXTERNAL(BOOL,KM3,data__->KM3,retain)
  __INIT_EXTERNAL(BOOL,M4,data__->M4,retain)
  __INIT_EXTERNAL(BOOL,L1,data__->L1,retain)
  __INIT_EXTERNAL(BOOL,L2,data__->L2,retain)
  __INIT_EXTERNAL(BOOL,L3,data__->L3,retain)
}

// Code part
void NEWBLOCK_body__(NEWBLOCK *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->DI_10.,B_AD,,0x58);
  __SET_VAR(data__->DI_10.,P_AD,,011);
  DI_1_body__(&data__->DI_10);
  __SET_EXTERNAL(data__->,BP1,,__GET_VAR(data__->DI_10.PIN,));
  __SET_VAR(data__->DI_80.,B_AD,,0x59);
  __SET_VAR(data__->DI_80.,X,,1);
  DI_8_body__(&data__->DI_80);
  __SET_EXTERNAL(data__->,Q1,,__GET_VAR(data__->DI_80.PX_3,));
  __SET_EXTERNAL(data__->,Q2,,__GET_VAR(data__->DI_80.PX_5,));
  __SET_EXTERNAL(data__->,Q3,,__GET_VAR(data__->DI_80.PX_7,));
  __SET_VAR(data__->DQ_10.,B_AD,,0x58);
  __SET_VAR(data__->DQ_10.,P_AD,,03);
  __SET_VAR(data__->DQ_10.,PIN,,(__GET_EXTERNAL(data__->LED1,) && __BOOL_LITERAL(TRUE)));
  DQ_1_body__(&data__->DQ_10);
  __SET_VAR(data__->DQ_81.,B_AD,,0x59);
  __SET_VAR(data__->DQ_81.,X,,0);
  __SET_VAR(data__->DQ_81.,PX_3,,__GET_EXTERNAL(data__->KM1,));
  __SET_VAR(data__->DQ_81.,PX_5,,__GET_EXTERNAL(data__->KM2,));
  __SET_VAR(data__->DQ_81.,PX_7,,__GET_EXTERNAL(data__->KM3,));
  DQ_8_body__(&data__->DQ_81);
  __SET_VAR(data__->RLY_10.,B_AD,,0x70);
  __SET_VAR(data__->RLY_10.,P_AD,,01);
  __SET_VAR(data__->RLY_10.,RLY,,__GET_EXTERNAL(data__->M4,));
  RLY_1_body__(&data__->RLY_10);
  __SET_VAR(data__->RLY_80.,B_AD,,0x74);
  __SET_VAR(data__->RLY_80.,RLY3,,__GET_EXTERNAL(data__->L1,));
  __SET_VAR(data__->RLY_80.,RLY5,,__GET_EXTERNAL(data__->L2,));
  __SET_VAR(data__->RLY_80.,RLY7,,__GET_EXTERNAL(data__->L3,));
  RLY_8_body__(&data__->RLY_80);

  goto __end;

__end:
  return;
} // NEWBLOCK_body__() 





void INITBLOCK_init__(INITBLOCK *data__, BOOL retain) {
  __INIT_EXTERNAL(AW9523B,BOARD1,data__->BOARD1,retain)
}

// Code part
void INITBLOCK_body__(INITBLOCK *data__) {
  // Initialise TEMP variables

  __SET_EXTERNAL(data__->,BOARD1,.ADDRESS,0x58);

  goto __end;

__end:
  return;
} // INITBLOCK_body__() 





void LED_TEST1_init__(LED_TEST1 *data__, BOOL retain) {
  DI_1_init__(&data__->DI_10,retain);
  DQ_8_init__(&data__->DQ_80,retain);
  RLY_1_init__(&data__->RLY_10,retain);
  RLY_1_init__(&data__->RLY_11,retain);
  RLY_1_init__(&data__->RLY_12,retain);
  __INIT_VAR(data__->_TMP_NOT19_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LED_TEST1_body__(LED_TEST1 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->DI_10.,B_AD,,0x58);
  __SET_VAR(data__->DI_10.,P_AD,,015);
  DI_1_body__(&data__->DI_10);
  __SET_VAR(data__->DQ_80.,B_AD,,0x58);
  __SET_VAR(data__->DQ_80.,X,,0);
  __SET_VAR(data__->DQ_80.,PX_2,,__GET_VAR(data__->DI_10.PIN,));
  DQ_8_body__(&data__->DQ_80);
  __SET_VAR(data__->RLY_10.,B_AD,,0x38);
  __SET_VAR(data__->RLY_10.,P_AD,,03);
  __SET_VAR(data__->RLY_10.,RLY,,__GET_VAR(data__->DI_10.PIN,));
  RLY_1_body__(&data__->RLY_10);
  __SET_VAR(data__->RLY_11.,B_AD,,0x38);
  __SET_VAR(data__->RLY_11.,P_AD,,01);
  __SET_VAR(data__->RLY_11.,RLY,,__GET_VAR(data__->DI_10.PIN,));
  RLY_1_body__(&data__->RLY_11);
  __SET_VAR(data__->,_TMP_NOT19_OUT,,!(__GET_VAR(data__->DI_10.PIN,)));
  __SET_VAR(data__->RLY_12.,B_AD,,0x38);
  __SET_VAR(data__->RLY_12.,P_AD,,06);
  __SET_VAR(data__->RLY_12.,RLY,,__GET_VAR(data__->_TMP_NOT19_OUT,));
  RLY_1_body__(&data__->RLY_12);

  goto __end;

__end:
  return;
} // LED_TEST1_body__() 





void LED_TEST2_init__(LED_TEST2 *data__, BOOL retain) {
  DI_8_init__(&data__->DI_80,retain);
  DQ_1_init__(&data__->DQ_10,retain);
  RLY_8_init__(&data__->RLY_80,retain);
}

// Code part
void LED_TEST2_body__(LED_TEST2 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->DI_80.,B_AD,,0x58);
  __SET_VAR(data__->DI_80.,X,,1);
  DI_8_body__(&data__->DI_80);
  __SET_VAR(data__->DQ_10.,B_AD,,0x58);
  __SET_VAR(data__->DQ_10.,P_AD,,02);
  __SET_VAR(data__->DQ_10.,PIN,,__GET_VAR(data__->DI_80.PX_5,));
  DQ_1_body__(&data__->DQ_10);
  __SET_VAR(data__->RLY_80.,B_AD,,0x38);
  __SET_VAR(data__->RLY_80.,RLY4,,__GET_VAR(data__->DI_80.PX_5,));
  RLY_8_body__(&data__->RLY_80);

  goto __end;

__end:
  return;
} // LED_TEST2_body__() 





