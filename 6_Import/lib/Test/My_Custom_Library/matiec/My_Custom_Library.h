// FUNCTION_BLOCK TEST

// Data part
typedef struct
{
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL, EN)
    __DECLARE_VAR(BOOL, ENO)
    __DECLARE_VAR(INT, I0)
    __DECLARE_VAR(BOOL, ACTIVE)
    __DECLARE_VAR(INT, OUT)
} TEST;

// Initialization part
static void TEST_init__(TEST *data__, BOOL retain)
{
    __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
    __INIT_VAR(data__->I0, 0, retain)
    __INIT_VAR(data__->ACTIVE, 0, retain)
    __INIT_VAR(data__->OUT, __BOOL_LITERAL(TRUE), retain)
}

// Code part
static void TEST_body__(TEST *data__)
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
} // TEST_body__()
