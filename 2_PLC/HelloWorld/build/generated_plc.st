PROGRAM Main
  VAR
    In AT %IX0.0 : BOOL;
    out AT %QX0.1 : BOOL;
  END_VAR

  out := In;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Main;
  END_RESOURCE
END_CONFIGURATION
