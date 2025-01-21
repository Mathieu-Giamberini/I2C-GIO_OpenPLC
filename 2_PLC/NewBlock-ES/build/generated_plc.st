TYPE
  In_Out : (Input, Output) := Input;
  AW9523B : STRUCT
    Address : BYTE := 16#00;
    Init : BOOL := True;
    P0_0 : In_Out := Input;
    P0_1 : In_Out := Input;
    P0_2 : In_Out := Input;
    P0_3 : In_Out := Input;
    P0_4 : In_Out := Input;
    P0_5 : In_Out := Input;
    P0_6 : In_Out := Input;
    P0_7 : In_Out := Input;
    P1_0 : In_Out := Input;
    P1_1 : In_Out := Input;
    P1_2 : In_Out := Input;
    P1_3 : In_Out := Input;
    P1_4 : In_Out := Input;
    P1_5 : In_Out := Input;
    P1_6 : In_Out := Input;
    P1_7 : In_Out := Input;
  END_STRUCT;
  AW9523B_2 : STRUCT
    Address : BYTE := 16#00;
    Init : BOOL := False;
    P1 : BYTE := 2#00000000;
    P2 : BYTE := 2#00000000;
  END_STRUCT;
  datatype1 : BOOL;
  RLY08 : STRUCT
    CurrentAdress : BYTE := 16#00;
    WantAddress : BYTE := 16#00;
  END_STRUCT;
END_TYPE

PROGRAM NewBlock
  VAR
    DI_10 : DI_1;
    DI_11 : DINT;
    DQ_10 : DQ_1;
    DI_80 : DI_8;
    DQ_81 : DQ_8;
    RLY_10 : RLY_1;
    RLY_80 : RLY_8;
  END_VAR
  VAR_EXTERNAL
    Board1 : AW9523B;
    Q1 : BOOL;
    Q2 : BOOL;
    Q3 : BOOL;
    BP1 : BOOL;
    LED1 : BOOL;
    KM1 : BOOL;
    KM2 : BOOL;
    KM3 : BOOL;
    M4 : BOOL;
    L1 : BOOL;
    L2 : BOOL;
    L3 : BOOL;
  END_VAR

  DI_10(B_AD := 16#58, P_AD := 8#11);
  BP1 := DI_10.PIN;
  DI_80(B_AD := 16#59, X := 1);
  Q1 := DI_80.PX_3;
  Q2 := DI_80.PX_5;
  Q3 := DI_80.PX_7;
  DQ_10(B_AD := 16#58, P_AD := 8#03, PIN := LED1 AND TRUE);
  DQ_81(B_AD := 16#59, X := 0, PX_3 := KM1, PX_5 := KM2, PX_7 := KM3);
  RLY_10(B_AD := 16#70, P_AD := 8#01, RLY := M4);
  RLY_80(B_AD := 16#74, RLY3 := L1, RLY5 := L2, RLY7 := L3);
END_PROGRAM

PROGRAM InitBlock
  VAR_EXTERNAL
    Board1 : AW9523B;
  END_VAR

  Board1.Address := 16#58;
END_PROGRAM

PROGRAM LED_Test1
  VAR
    DI_10 : DI_1;
    DQ_80 : DQ_8;
    RLY_10 : RLY_1;
    RLY_11 : RLY_1;
    RLY_12 : RLY_1;
    _TMP_NOT19_OUT : BOOL;
  END_VAR

  DI_10(B_AD := 16#58, P_AD := 8#15);
  DQ_80(B_AD := 16#58, X := 0, PX_2 := DI_10.PIN);
  RLY_10(B_AD := 16#38, P_AD := 8#03, RLY := DI_10.PIN);
  RLY_11(B_AD := 16#38, P_AD := 8#01, RLY := DI_10.PIN);
  _TMP_NOT19_OUT := NOT(DI_10.PIN);
  RLY_12(B_AD := 16#38, P_AD := 8#06, RLY := _TMP_NOT19_OUT);
END_PROGRAM

PROGRAM LED_Test2
  VAR
    DI_80 : DI_8;
    DQ_10 : DQ_1;
    RLY_80 : RLY_8;
  END_VAR

  DI_80(B_AD := 16#58, X := 1);
  DQ_10(B_AD := 16#58, P_AD := 8#02, PIN := DI_80.PX_5);
  RLY_80(B_AD := 16#38, RLY4 := DI_80.PX_5);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    VAR_GLOBAL
      Board1 : AW9523B := (Address := 16#58);
      Q1 : BOOL;
      Q2 : BOOL;
      Q3 : BOOL;
      BP1 : BOOL;
      LED1 : BOOL;
      KM1 : BOOL;
      KM2 : BOOL;
      KM3 : BOOL;
      M4 : BOOL;
      L1 : BOOL;
      L2 : BOOL;
      L3 : BOOL;
      v : BYTE;
    END_VAR
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : LED_Test1;
  END_RESOURCE
END_CONFIGURATION
