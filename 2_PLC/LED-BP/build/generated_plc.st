PROGRAM Plus10
  VAR RETAIN
    Count : INT := 0;
  END_VAR
  VAR RETAIN
    BP AT %IX0.1 : BOOL := 0;
  END_VAR
  VAR
    Test0 : Test;
  END_VAR
  VAR RETAIN
    Test1 : BYTE := 16#FF;
    BP1 : BOOL;
    LED1 : BOOL;
  END_VAR
  VAR
    KM1 : BOOL;
    KM2 : BOOL;
    KM3 : BOOL;
    M4 : BOOL;
    L1 : BOOL;
    L2 : BOOL;
    L3 : BOOL;
    Q1 : BOOL;
    Q2 : BOOL;
    Q3 : BOOL;
    DI_10 : DI_1;
    DQ_10 : DQ_1;
    DI_80 : DI_8;
    DQ_81 : DQ_8;
    RLY_10 : RLY_1;
    RLY_80 : RLY_8;
  END_VAR

  Test0(I0 := Count, ACTIVE := BP);
  Count := Test0.OUT;
  DI_10(B_AD := 16#58, P_AD := 8#11);
  BP1 := DI_10.PIN;
  DQ_10(B_AD := 16#58, P_AD := 8#03, PIN := LED1 AND TRUE);
  DI_80(B_AD := 16#59, X := 1);
  DQ_81(B_AD := 16#59, X := 0, PX_3 := KM1, PX_5 := KM1, PX_7 := KM1);
  RLY_10(B_AD := 16#70, P_AD := 8#01, RLY := M4);
  RLY_80(B_AD := 16#74, RLY3 := L1, RLY5 := L2, RLY7 := L3);
END_PROGRAM

PROGRAM LED_BP
  VAR
    BP1 AT %IX0.0 : BOOL;
    LED AT %QX0.0 : BOOL;
  END_VAR

  LED := NOT(BP1);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Plus10;
  END_RESOURCE
END_CONFIGURATION
