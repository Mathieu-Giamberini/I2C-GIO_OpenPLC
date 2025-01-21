// FUNCTION_BLOCK RLY_1

// Data part
typedef struct
{
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, B_AD)
    __DECLARE_VAR(BYTE, P_AD)
    __DECLARE_VAR(BOOL, RLY)
} RLY_1;

// Initialization part
static void RLY_1_init__(RLY_1 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, /*TF: initial value*/, retain)
    __INIT_VAR(data__->P_AD, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY, /*TF: initial value*/, retain)
}

// Code part
static void RLY_1_body__(RLY_1 *data__)
{
    // Control execution - this should be the same for every Function Block
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
/*TF: Code*/
#undef GetFbVar
#undef SetFbVar
    return;
} // RLY_1_body__()


// FUNCTION_BLOCK RLY_8

// Data part
typedef struct
{
    // FB Interface - IN, OUT, IN_OUT variables
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
} RLY_8;

// Initialization part
static void RLY_8_init__(RLY_8 *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->B_AD, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY1, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY2, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY3, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY4, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY5, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY6, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY7, /*TF: initial value*/, retain)
    __INIT_VAR(data__->RLY8, /*TF: initial value*/, retain)
}

// Code part
static void RLY_8_body__(RLY_8 *data__)
{
    // Control execution - this should be the same for every Function Block
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
/*TF: Code*/
#undef GetFbVar
#undef SetFbVar
    return;
} // RLY_8_body__()


// FUNCTION_BLOCK SET_ADDR

// Data part
typedef struct
{
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(BYTE, CONFIG)
    __DECLARE_VAR(BYTE, CONFIG)
} SET_ADDR;

// Initialization part
static void SET_ADDR_init__(SET_ADDR *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->CONFIG, /*TF: initial value*/, retain)
    __INIT_VAR(data__->CONFIG, /*TF: initial value*/, retain)
}

// Code part
static void SET_ADDR_body__(SET_ADDR *data__)
{
    // Control execution - this should be the same for every Function Block
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
/*TF: Code*/
#undef GetFbVar
#undef SetFbVar
    return;
} // SET_ADDR_body__()


