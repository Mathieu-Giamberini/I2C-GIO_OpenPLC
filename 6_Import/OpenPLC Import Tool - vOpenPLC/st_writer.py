from function_block import FunctionBlock, Variable

def generate_vars(var_block):
    return_str = ''
    for variable in var_block:
        return_str += variable.name + ' : ' + variable.type + ';\n'
    
    return return_str

def generate_st(function_blocks, st_file):
    if st_file is None:
        st_file = ''
    
    for fb in function_blocks:
        if fb.type == "FunctionBlock":
            st_file += 'FUNCTION_BLOCK ' + fb.name + '\n'
        else:
            st_file += 'FUNCTION ' + fb.name + ' : ' + fb.type + '\n'

        if len(fb.inputs) > 0:
            st_file += 'VAR_INPUT\n'
            st_file += generate_vars(fb.inputs)
            st_file += 'END_VAR\n'
        if len(fb.outputs) > 0:
            st_file += 'VAR_OUTPUT\n'
            st_file += generate_vars(fb.outputs)
            st_file += 'END_VAR\n'
        if len(fb.locals) > 0:
            st_file += 'VAR\n'
            st_file += generate_vars(fb.locals)
            st_file += 'END_VAR\n'
        
        st_file += fb.code

        if fb.type == "FunctionBlock":
            st_file += 'END_FUNCTION_BLOCK\n\n'
        else:
            st_file += 'END_FUNCTION\n\n'

    return st_file

def update_lib(st_filename, data):
    lines = data.split('\n')
    return_str = ''
    for line in lines:
        if st_filename in line:
            # Lib file already includes st_filename
            return data
        if 'enable code generation' in line:
            # Last line of lib file... must include st_filename
            return_str += '{#include "' + st_filename + '" }\n{enable code generation}'
        else:
            return_str += line + '\n'
    
    return return_str
