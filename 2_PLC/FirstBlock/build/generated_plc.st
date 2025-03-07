FUNCTION_BLOCK TestBlock1
  VAR
    Test2 : DINT;
  END_VAR
  VAR RETAIN
    Test1 : INT := 0;
  END_VAR
  VAR_OUTPUT
    LED : BOOL := 0;
  END_VAR
  VAR RETAIN
    ID : BYTE := 160;
    threashold : INT := 20;
  END_VAR
  VAR
    Test0 : Test;
    BNO0550 : BNO055;
    _TMP_LE6_OUT : BOOL;
    _TMP_EQ10_OUT : BOOL;
  END_VAR

  _TMP_LE6_OUT := LE(Test1, threashold);
  Test0(I0 := Test1, ACTIVE := _TMP_LE6_OUT);
  Test1 := Test0.OUT;
  BNO0550();
  _TMP_EQ10_OUT := EQ(BNO0550.CHIP_ID, ID);
  LED := _TMP_EQ10_OUT;
END_FUNCTION_BLOCK

PROGRAM program0
  VAR
    TestBlock10 : TestBlock1;
  END_VAR
  VAR
    LED AT %QX0.0 : BOOL;
  END_VAR

  TestBlock10();
  LED := TestBlock10.LED;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
