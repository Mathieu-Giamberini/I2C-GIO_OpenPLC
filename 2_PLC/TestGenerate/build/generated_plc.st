PROGRAM program0
  VAR
    Test1 : INT;
    Test2 : INT;
    Test3 : BOOL;
    Test0 : Test;
  END_VAR

  Test0(I0 := Test1, ACTIVE := Test3);
  Test2 := Test0.OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
