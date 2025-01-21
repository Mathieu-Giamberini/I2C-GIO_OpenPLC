"""Code from the OpenPLC Import Tool"""
class Variable:
    def __init__(self, name:str, type:str):
        self.name = name
        self.type = type

    def __repr__(self) -> str:
        return f"<{self.type}>{self.name}"

class FunctionBlock:
    def __init__(self, name:str, fbtype:str, locals:list[Variable], inputs:list[Variable], outputs:list[Variable], code:str, doc:str):
        self.name = name
        self.type = fbtype
        self.locals = locals
        self.inputs = inputs
        self.outputs = outputs
        self.code = code
        self.doc = doc
  

def generate_vars(var_block):
    return_str = ''
    for variable in var_block:
        return_str += variable.name + ' : ' + variable.type + ';\n'
    
    return return_str[:-1]

def addIndent(text:str, level:int, len_indent:int=2):
    indent = level*len_indent*" " 
    res = ""
    for line in text.split("\n"):
        res += "\n" + indent + line
    return res

def generate_st(function_blocks:list[FunctionBlock], st_file:str|None=""):
    if st_file is None:
        st_file = ''
    
    for fb in function_blocks:
        noCode = fb.code == ""
        
        #Doc
        st_file += "(*"
        st_file += fb.doc
        st_file += "\n*)\n"
        
        if fb.type == "functionBlock":
            st_file += 'FUNCTION_BLOCK ' + fb.name 
        else:
            st_file += 'FUNCTION ' + fb.name + ' : ' + fb.type

        if len(fb.inputs) > 0:
            st_file += addIndent('VAR_INPUT', 1)
            st_file += addIndent(generate_vars(fb.inputs), 2)
            st_file += addIndent('END_VAR', 1)
        if len(fb.outputs) > 0 or noCode:
            st_file += addIndent('VAR_OUTPUT', 1)

            if len(fb.outputs) > 0:
                st_file += addIndent(generate_vars(fb.outputs), 2)

            if noCode:
                st_file += addIndent(generate_vars([Variable("DUMMY", "BOOL")]), 2)

            st_file += addIndent('END_VAR', 1)
        if len(fb.locals) > 0:
            st_file += addIndent('VAR', 1)
            st_file += addIndent(generate_vars(fb.locals), 2)
            st_file += addIndent('END_VAR', 1)
        
        if noCode :
            st_file += addIndent("DUMMY := 0;", 1)
        else:
            st_file += addIndent(fb.code, 1)

        if fb.type == "functionBlock":
            st_file += '\nEND_FUNCTION_BLOCK\n\n'
        else:
            st_file += '\nEND_FUNCTION\n\n'

    return st_file
