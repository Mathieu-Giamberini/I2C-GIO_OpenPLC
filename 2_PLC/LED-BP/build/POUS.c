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





void PLUS10_init__(PLUS10 *data__, BOOL retain) {
  __INIT_VAR(data__->COUNT,0,1)
  __INIT_LOCATED(BOOL,__IX0_1,data__->BP,1)
  __INIT_LOCATED_VALUE(data__->BP,0)
  TEST_init__(&data__->TEST0,retain);
  __INIT_VAR(data__->TEST1,0xFF,1)
  __INIT_VAR(data__->BP1,__BOOL_LITERAL(FALSE),1)
  __INIT_VAR(data__->LED1,__BOOL_LITERAL(FALSE),1)
  __INIT_VAR(data__->KM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->KM2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->KM3,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->M4,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->L1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->L2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->L3,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->Q3,__BOOL_LITERAL(FALSE),retain)
  DI_1_init__(&data__->DI_10,retain);
  DQ_1_init__(&data__->DQ_10,retain);
  DI_8_init__(&data__->DI_80,retain);
  DQ_8_init__(&data__->DQ_81,retain);
  RLY_1_init__(&data__->RLY_10,retain);
  RLY_8_init__(&data__->RLY_80,retain);
}

// Code part
void PLUS10_body__(PLUS10 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TEST0.,I0,,__GET_VAR(data__->COUNT,));
  __SET_VAR(data__->TEST0.,ACTIVE,,__GET_LOCATED(data__->BP,));
  TEST_body__(&data__->TEST0);
  __SET_VAR(data__->,COUNT,,__GET_VAR(data__->TEST0.OUT,));
  __SET_VAR(data__->DI_10.,B_AD,,0x58);
  __SET_VAR(data__->DI_10.,P_AD,,011);
  DI_1_body__(&data__->DI_10);
  __SET_VAR(data__->,BP1,,__GET_VAR(data__->DI_10.PIN,));
  __SET_VAR(data__->DQ_10.,B_AD,,0x58);
  __SET_VAR(data__->DQ_10.,P_AD,,03);
  __SET_VAR(data__->DQ_10.,PIN,,(__GET_VAR(data__->LED1,) && __BOOL_LITERAL(TRUE)));
  DQ_1_body__(&data__->DQ_10);
  __SET_VAR(data__->DI_80.,B_AD,,0x59);
  __SET_VAR(data__->DI_80.,X,,1);
  DI_8_body__(&data__->DI_80);
  __SET_VAR(data__->DQ_81.,B_AD,,0x59);
  __SET_VAR(data__->DQ_81.,X,,0);
  __SET_VAR(data__->DQ_81.,PX_3,,__GET_VAR(data__->KM1,));
  __SET_VAR(data__->DQ_81.,PX_5,,__GET_VAR(data__->KM1,));
  __SET_VAR(data__->DQ_81.,PX_7,,__GET_VAR(data__->KM1,));
  DQ_8_body__(&data__->DQ_81);
  __SET_VAR(data__->RLY_10.,B_AD,,0x70);
  __SET_VAR(data__->RLY_10.,P_AD,,01);
  __SET_VAR(data__->RLY_10.,RLY,,__GET_VAR(data__->M4,));
  RLY_1_body__(&data__->RLY_10);
  __SET_VAR(data__->RLY_80.,B_AD,,0x74);
  __SET_VAR(data__->RLY_80.,RLY3,,__GET_VAR(data__->L1,));
  __SET_VAR(data__->RLY_80.,RLY5,,__GET_VAR(data__->L2,));
  __SET_VAR(data__->RLY_80.,RLY7,,__GET_VAR(data__->L3,));
  RLY_8_body__(&data__->RLY_80);

  goto __end;

__end:
  return;
} // PLUS10_body__() 





void LED_BP_init__(LED_BP *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->BP1,retain)
  __INIT_LOCATED_VALUE(data__->BP1,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_0,data__->LED,retain)
  __INIT_LOCATED_VALUE(data__->LED,__BOOL_LITERAL(FALSE))
}

// Code part
void LED_BP_body__(LED_BP *data__) {
  // Initialise TEMP variables

  __SET_LOCATED(data__->,LED,,!(__GET_LOCATED(data__->BP1,)));

  goto __end;

__end:
  return;
} // LED_BP_body__() 





