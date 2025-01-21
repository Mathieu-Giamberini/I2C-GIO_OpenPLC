// AW9523B.h – this file contains the C code for the blocks used to communicate
// with the AW9523B board define in the “AW9523B” Library

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
    __INIT_VAR(data__->B_AD, 0x58, retain)
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
    __INIT_VAR(data__->B_AD, 0x58, retain)
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
    __INIT_VAR(data__->B_AD, 0x58, retain)
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
    __INIT_VAR(data__->B_AD, 0x58, retain)
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

#undef GetFbVar
#undef SetFbVar

    return;
} // DQ_8_body__()