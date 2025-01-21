// RLY08.h – this file contains the C code for the blocks used to communicate
// with the RLY08 board define in the “RLY08” Library

// FUNCTION_BLOCK RLY_1

typedef uint16_t byte;
void write(byte addr, byte reg, byte value);
void write_bit(byte addr, byte reg, byte n, bool value);

static const byte RLY_FIRST_ADDRESS = 0x38;

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BYTE, P_AD)
    __DECLARE_VAR(BOOL, RLY)
    __DECLARE_VAR(BOOL, DUMMY)
} RLY_1;

// Initialization part
static void RLY_1_init__(RLY_1 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x70, retain)
    __INIT_VAR(data__->P_AD, 0x00, retain)
    __INIT_VAR(data__->RLY, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void RLY_1_body__(RLY_1 *data__)
{

    // Control execution – this should be the same for every Function Block
    if (!__GET_VAR(data__->EN))
    {
        __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
        return;
    }
    else
    {
        __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
    }

// Actual Code
#define GetFbVar(var, ...) __GET_VAR(data__->var, __VA_ARGS__)
#define SetFbVar(var, val, ...) __SET_VAR(data__->, var, __VA_ARGS__, val)
    byte addr = GetFbVar(B_AD) + RLY_FIRST_ADDRESS;

    write_bit(addr, 0x01, GetFbVar(P_AD), GetFbVar(RLY));
#undef GetFbVar
#undef SetFbVar

    return;
} // RLY_1_body__()

// FUNCTION_BLOCK RLY_8

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BOOL, RLY1)
    __DECLARE_VAR(BOOL, RLY2)
    __DECLARE_VAR(BOOL, RLY3)
    __DECLARE_VAR(BOOL, RLY4)
    __DECLARE_VAR(BOOL, RLY5)
    __DECLARE_VAR(BOOL, RLY6)
    __DECLARE_VAR(BOOL, RLY7)
    __DECLARE_VAR(BOOL, RLY8)
    __DECLARE_VAR(BOOL, DUMMY)
} RLY_8;

// Initialization part
static void RLY_8_init__(RLY_8 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x70, retain)
    __INIT_VAR(data__->RLY1, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY2, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY3, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY4, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY5, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY6, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY7, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->RLY8, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void RLY_8_body__(RLY_8 *data__)
{

    // Control execution – this should be the same for every Function Block
    if (!__GET_VAR(data__->EN))
    {
        __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
        return;
    }
    else
    {
        __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
    }

// Actual Code
#define GetFbVar(var, ...) __GET_VAR(data__->var, __VA_ARGS__)
#define SetFbVar(var, val, ...) __SET_VAR(data__->, var, __VA_ARGS__, val)
#define PushAdd(reg, var, ...) reg = (reg << 1) | GetFbVar(var)
    byte addr = GetFbVar(B_AD) + RLY_FIRST_ADDRESS;

    byte RLY_reg = GetFbVar(RLY8);
    PushAdd(RLY_reg, RLY7);
    PushAdd(RLY_reg, RLY6);
    PushAdd(RLY_reg, RLY5);
    PushAdd(RLY_reg, RLY4);
    PushAdd(RLY_reg, RLY3);
    PushAdd(RLY_reg, RLY2);
    PushAdd(RLY_reg, RLY1);

    // Write side
    write(addr, 0x01, RLY_reg);

#undef PushAdd
#undef GetFbVar
#undef SetFbVar

    return;
} // RLY_8_body__()