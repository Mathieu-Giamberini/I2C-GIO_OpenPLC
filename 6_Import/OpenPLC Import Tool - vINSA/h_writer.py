from st_writer import FunctionBlock, Variable, addIndent

def generate_h(function_blocks:list[FunctionBlock], h_str:str=""):
    for fb in function_blocks :
        h_str += f"// FUNCTION_BLOCK {fb.name}\n"

        #Struct
        h_str +=  "\n// Data part\ntypedef struct\n{"
        h_str +=  addIndent("// FB Interface - IN, OUT, IN_OUT variables", 1, 4)
    
        vars = [Variable("EN", "BOOL"), Variable("ENO", "BOOL")] \
                + fb.inputs + fb.outputs + fb.locals
        
        for var in vars:
            h_str += addIndent(f"__DECLARE_VAR({var.type}, {var.name})", 1, 4)
        
        h_str +=  "\n} " + fb.name + ";\n"

        #Initial
        h_str += f"\n// Initialization part"
        h_str += f"\nstatic void {fb.name}_init__({fb.name} *data__, BOOL retain)"
        h_str += "\n{"

        for var in vars:
            default = "__BOOL_LITERAL(TRUE)" if var.name in ["EN", "ENO"] else "/*TF: initial value*/"
            h_str += addIndent(f"__INIT_VAR(data__->{var.name}, {default}, retain)", 1, 4)
        h_str +=  "\n}\n"
        
        #Body
        h_str +=  "\n// Code part"
        h_str += f"\nstatic void {fb.name}_body__({fb.name} *data__)"
        h_str += "\n{"
        h_str += addIndent("""// Control execution - this should be the same for every Function Block
if (!__GET_VAR(data__->EN))
{
    __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
    return;
}
else
{
    __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
}""", 1, 4)
        
        h_str += """\n\n// Actual Code
#define GetFbVar(var, ...) __GET_VAR(data__->var, __VA_ARGS__)
#define SetFbVar(var, val, ...) __SET_VAR(data__->, var, __VA_ARGS__, val)
/*TF: Code*/
#undef GetFbVar
#undef SetFbVar
    return;
} """
        h_str += f"// {fb.name}_body__()\n\n\n"


    return h_str
