// AW9523B.h – this file contains the C code for the blocks used to communicate
// with the AW9523B board define in the “AW9523B” Library
typedef uint16_t byte;
byte read(byte addr, byte reg);
void write(byte addr, byte reg, byte value);
void write_bit(byte addr, byte reg, byte n, bool value);

bool getBit(byte b, int pos);

static byte read_reg(bool P_AD) { return !P_AD ? 0x00 : 0x01; }
static byte write_reg(bool P_AD) { return !P_AD ? 0x02 : 0x03; }
static byte config_reg(bool P_AD) { return !P_AD ? 0x04 : 0x05; }
static const byte AW_FIRST_ADDRESS = 0x58;

static void
AW_setup(byte B_AD)
{
    write(B_AD, 0x11, 0x10); // 00010000
}

void print(char *text);
// FUNCTION_BLOCK DI_1

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BYTE, P_AD)
    __DECLARE_VAR(BOOL, PIN)
    __DECLARE_VAR(BOOL, DUMMY)
} DI_1;

// Initialization part
static void DI_1_init__(DI_1 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x00, retain)
    __INIT_VAR(data__->P_AD, 0x00, retain)
    __INIT_VAR(data__->PIN, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void DI_1_body__(DI_1 *data__)
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
    bool side = getBit(GetFbVar(P_AD), 3);
    byte i_pin = 0x07 & GetFbVar(P_AD);
    byte addr = GetFbVar(B_AD) + AW_FIRST_ADDRESS;

    // Config to input
    AW_setup(addr);
    write_bit(addr, config_reg(side), i_pin, true);

    // Read pin
    byte side_value = read(addr, read_reg(side));
    SetFbVar(PIN, getBit(side_value, i_pin));

#undef GetFbVar
#undef SetFbVar

    return;
} // DI_1_body__()

// FUNCTION_BLOCK DQ_1

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BYTE, P_AD)
    __DECLARE_VAR(BOOL, PIN)
    __DECLARE_VAR(BOOL, DUMMY)
} DQ_1;

// Initialization part
static void DQ_1_init__(DQ_1 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x00, retain)
    __INIT_VAR(data__->P_AD, 0x00, retain)
    __INIT_VAR(data__->PIN, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void DQ_1_body__(DQ_1 *data__)
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
    bool side = getBit(GetFbVar(P_AD), 3);
    byte i_pin = 0x07 & GetFbVar(P_AD);
    byte addr = GetFbVar(B_AD) + AW_FIRST_ADDRESS;

    // Config to output
    AW_setup(addr);
    write_bit(addr, config_reg(side), i_pin, false);

    // Write pin
    write_bit(addr, write_reg(side), i_pin, GetFbVar(PIN));

#undef GetFbVar
#undef SetFbVar

    return;
} // DQ_1_body__()

// FUNCTION_BLOCK DI_8

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BOOL, X)
    __DECLARE_VAR(BOOL, PX_1)
    __DECLARE_VAR(BOOL, PX_0)
    __DECLARE_VAR(BOOL, PX_2)
    __DECLARE_VAR(BOOL, PX_3)
    __DECLARE_VAR(BOOL, PX_4)
    __DECLARE_VAR(BOOL, PX_5)
    __DECLARE_VAR(BOOL, PX_6)
    __DECLARE_VAR(BOOL, PX_7)
    __DECLARE_VAR(BOOL, DUMMY)
} DI_8;

// Initialization part
static void DI_8_init__(DI_8 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x00, retain)
    __INIT_VAR(data__->X, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_0, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_1, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_2, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_3, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_4, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_5, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_6, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_7, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void DI_8_body__(DI_8 *data__)
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
#define SetBool(var, reg, n, ...) SetFbVar(var, getBit(reg, n))
    byte addr = GetFbVar(B_AD) + AW_FIRST_ADDRESS;

    // Config the side to output
    AW_setup(addr);
    write(addr, config_reg(GetFbVar(X)), 0xFF);

    // Get side state
    byte side_reg = read(addr, read_reg(GetFbVar(X)));

    SetBool(PX_0, side_reg, 0);
    SetBool(PX_1, side_reg, 1);
    SetBool(PX_2, side_reg, 2);
    SetBool(PX_3, side_reg, 3);
    SetBool(PX_4, side_reg, 4);
    SetBool(PX_5, side_reg, 5);
    SetBool(PX_6, side_reg, 6);
    SetBool(PX_7, side_reg, 7);

#undef SetBool
#undef GetFbVar
#undef SetFbVar

    return;
} // DQ_8_body__()

// FUNCTION_BLOCK DQ_8

// Data part
typedef struct
{
    // FB Interface – IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BOOL, X)
    __DECLARE_VAR(BOOL, PX_0)
    __DECLARE_VAR(BOOL, PX_1)
    __DECLARE_VAR(BOOL, PX_2)
    __DECLARE_VAR(BOOL, PX_3)
    __DECLARE_VAR(BOOL, PX_4)
    __DECLARE_VAR(BOOL, PX_5)
    __DECLARE_VAR(BOOL, PX_6)
    __DECLARE_VAR(BOOL, PX_7)
    __DECLARE_VAR(BOOL, DUMMY)
} DQ_8;

// Initialization part
static void DQ_8_init__(DQ_8 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, 0x00, retain)
    __INIT_VAR(data__->X, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_0, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_1, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_2, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_3, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_4, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_5, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_6, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->PX_7, __BOOL_LITERAL(FALSE), retain)
    __INIT_VAR(data__->DUMMY, __BOOL_LITERAL(FALSE), retain)
}

// Code part
static void DQ_8_body__(DQ_8 *data__)
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
    byte addr = GetFbVar(B_AD) + AW_FIRST_ADDRESS;

    // Config the side to input
    AW_setup(addr);
    write(addr, config_reg(GetFbVar(X)), 0x00);

    byte side_reg = GetFbVar(PX_7);
    PushAdd(side_reg, PX_6);
    PushAdd(side_reg, PX_5);
    PushAdd(side_reg, PX_4);
    PushAdd(side_reg, PX_3);
    PushAdd(side_reg, PX_2);
    PushAdd(side_reg, PX_1);
    PushAdd(side_reg, PX_0);

    // Write side
    write(addr, write_reg(GetFbVar(X)), side_reg);

#undef PushAdd
#undef GetFbVar
#undef SetFbVar

    return;
} // DQ_8_body__()