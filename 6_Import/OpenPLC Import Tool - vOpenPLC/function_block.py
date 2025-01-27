import re

class FunctionBlock:
    def __init__(self, name, fbtype, locals, inputs, outputs, code):
        self.name = name
        self.type = fbtype
        self.locals = locals
        self.inputs = inputs
        self.outputs = outputs
        self.code = code

class Variable:
    def __init__(self, name, type):
        self.name = name
        self.type = type

def parse_variables(data):
    local_variables = []
    input_variables = []
    output_variables = []
    fb_code = ''

    looking_for_local = False
    looking_for_input = False
    looking_for_ouput = False

    lines = data.split('\n')
    for line in lines:
        if not looking_for_local and not looking_for_input and not looking_for_ouput:
            if 'VAR_INPUT' in line:
                looking_for_input = True
            elif 'VAR_OUTPUT' in line:
                looking_for_ouput = True
            elif 'VAR' in line:
                looking_for_local = True
            else:
                fb_code += line + '\n'
        else:
            if 'END_VAR' in line:
                looking_for_local = False
                looking_for_input = False
                looking_for_ouput = False
            elif ':' in line:
                if ':=' in line:
                    line = line.split(':=')[0] #Select only the variable declaration portion
                var_name, var_type = line.split(":")
                var_name = var_name.strip()
                var_type = var_type.strip()
                var_type = var_type.strip(';')
                if looking_for_ouput == True:
                    output_variables.append(Variable(var_name, var_type))
                elif looking_for_input == True:
                    input_variables.append(Variable(var_name, var_type))
                elif looking_for_local == True:
                    local_variables.append(Variable(var_name, var_type))

    return local_variables, input_variables, output_variables, fb_code


def parse_structured_text(data):
    function_blocks = re.findall(r"FUNCTION_BLOCK (\w+)\n(.*?)END_FUNCTION_BLOCK", data, re.DOTALL)
    functions = re.findall(r"FUNCTION (\w+) : (\w+)\n(.*?)END_FUNCTION", data, re.DOTALL)
    return_fb = []

    for f in functions:
        f_name = f[0]
        f_type = f[1]
        f_content = f[2]

        local_vars, input_vars, output_vars, f_code = parse_variables(f_content)

        f = FunctionBlock(f_name, f_type, local_vars, input_vars, output_vars, f_code)
        #print("Function: " + f_name + "\n")
        #for variable in local_vars:
            #print("\tlocal: " + variable.name + "\n")
        #print("Code: " + f_code)
        return_fb.append(f)

    for fb in function_blocks:
        fb_name = fb[0]
        fb_content = fb[1]

        local_vars, input_vars, output_vars, fb_code = parse_variables(fb_content)

        fb = FunctionBlock(fb_name, "FunctionBlock", local_vars, input_vars, output_vars, fb_code)
        #print("Function block: " + fb_name + "\n")
        #for variable in local_vars:
        #    print("\tlocal: " + variable.name + "\n")
        #print("Code: " + fb_code)
        return_fb.append(fb)
    
    return return_fb