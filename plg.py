"""File to test python code (playground)"""

with open("6_Import\\lib\\AW9523B\\toModif\\plcopen\\definitions.py", 'r') as definitions_py_file:
    definitions_py = definitions_py_file.read()

n_StdTC6Libs = definitions_py.find("StdTC6Libs")
n_endList = definitions_py[n_StdTC6Libs:].find("]") + n_StdTC6Libs


definitions_py =  definitions_py[:n_endList] \
                + ',\n              (_("RLY08"), join(sd, "RLY08.xml"))'\
                + definitions_py[n_endList:] 

with open("6_Import\\lib\\AW9523B\\toModif\\plcopen\\definitions.py", 'w') as definitions_py_file:
    definitions_py_file.write(definitions_py)
