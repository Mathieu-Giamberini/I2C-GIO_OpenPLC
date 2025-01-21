import platform
import os 
import shutil
import json
import glob
import xml.etree.ElementTree as ET 
from zipfile import ZipFile 

from generate import generate
from st_writer import FunctionBlock, Variable

def getOpenPLCPath():
    """Get the OpenPLC Editor path"""
    print("Detecting OpenPLC Editor installation...")
    Config = os.getcwd()
    if not (os.path.isfile(os.path.join(Config, 'editor', 'Beremiz.py'))):
        if platform.system() == 'Windows':
            Config = os.path.expanduser('~') + '\\OpenPLC_Editor'
        elif platform.system() == 'Darwin':
            Config = '/Applications/OpenPLC Editor.app/Contents/Resources'

        #Try again
        while not (os.path.isfile(os.path.join(Config, 'editor', 'Beremiz.py'))):
            print(f"Could not detect OpenPLC Editor installation at '{Config}'. Please type the folder where OpenPLC Editor was installed on your computer. Type 'exit' to exit")
            Config = input("Folder: ")
            if Config == 'exit':
                exit(-1)

    return Config


def askPath(query:str = "path : ") :
    """Ask to the user a path,  \\ replaced with / and the last / removed"""
    path = input(query).replace("\\", "/").replace("'", "").replace('"', "")
    if path[-1] == "/" :
        path = path[:-1]
    return path

def getLibPath():
    """Get the library path"""
    path = askPath("library path (ctr-c to exit): ")
    libPath = ""

    isValid = False
    isZip = False                
    needConfig = False                

    hasConfigFile = lambda : os.path.isfile(libPath + "/config.json") 
    while not isValid:
        file = os.path.basename(path).split(".")
        if file[-1] == "zip":
            with ZipFile(path, 'r') as zip: 
                zip.extractall(os.path.dirname(path))

            path = path[:-4]
            os.rename(path, path + "_unzip")
            path = path + "_unzip"

            file = [path]

            isZip = True  

        if len(file) > 1:
            isValid = False
            path = askPath("The library is not in a supported file (.zip or folder),\nlibrary path (ctr-c to exit): ")
            

        if len(file) == 1:
            libPath = path
            isValid = hasConfigFile()

            if not isValid:
                if isZip :
                    #Delete the dir
                    shutil.rmtree(libPath)
                
                if len(os.listdir(libPath)) == 0: #is an empty dir
                    if askYN("The config file is missing, do you want created it"):
                        needConfig = True
                        isValid = True
                
            if not isValid:
                path = askPath("The library is not valid, missing a config file,\nlibrary path (ctr-c to exit): ")
                
        
    return libPath, isZip, needConfig
    
def addToFile(path:str, conditions:list[str], text:str):
    """Add 'text' after 'conditions' in the file 'path' if missing """
    with open(path, 'r') as file:
        file_text = file.read()

    if file_text.find(text) == -1 :
        loc = 0
        for cond in conditions:
            loc += file_text[loc:].find(cond)
        
        file_text =   file_text[:loc] \
                    + text\
                    + file_text[loc:] 

    with open(path, 'w') as file:
        file.write(file_text)

#Function block
def getVars(pou:ET.Element, nameSpace:dict):
    """Get all the variable from the xml pou"""
    interface = pou.find("interface", nameSpace)
    all_var = {"inputVars":[], "outputVars":[], "localVars":[]}
    for key in all_var.keys():
        for var in interface.iterfind(f"{key}/variable", nameSpace):   # type: ignore
            var_name = var.get("name")
            var_type = var.find("type/", nameSpace).tag.split("}")[-1] # type: ignore

            all_var[key].append(Variable(var_name.upper(), var_type))          # type: ignore
    return all_var

def getCode(pou:ET.Element, nameSpace:dict):
    """Get the code of the xml pou if in ST"""
    code = pou.find("body/ST/xhtml:p", nameSpace)
    if code is None:
        return ""
    elif code.text is None:
        return ""
    else :
        return code.text  

def getAllFunctionBlock(xml_path:str):
    """Read all info from the xml for the functionBlock"""
    all_blocks_name = []
    all_blocks = []

    tree = ET.parse(xml_path)
    root = tree.getroot()
    nameSpace = {
        ""     :"http://www.plcopen.org/xml/tc6_0201",
        "xhtml":"http://www.w3.org/1999/xhtml"
    }
    for pou in root.iterfind("./types/pous/", nameSpace):
        all_blocks_name.append(pou.get("name"))

        #Interface
        all_var = getVars(pou, nameSpace)
        code = getCode(pou, nameSpace)
        doc = pou.find("documentation/xhtml:p", nameSpace).text # type: ignore

        all_blocks.append(FunctionBlock(
            pou.get("name").upper(), # type: ignore
            pou.get("pouType"),      # type: ignore
            all_var["localVars"],
            all_var["inputVars"],
            all_var["outputVars"],
            code,                    # type: ignore
            doc                      # type: ignore
        ))

    if len(all_blocks_name) == 0:
        print(f"There is no function in the xml, the name space (xmlns) should be {nameSpace}")
    
    return all_blocks_name, all_blocks

def write_definitionsPy(plcopen_path:str, name:str):
    """Add the call to the xml file in definitions.py"""
    addToFile(
        plcopen_path + "\\definitions.py",
        ["StdTC6Libs","]"],
        f',\n              (_("{name}"), join(sd, "{name}.xml"))'
    )

def askYN(text:str):
    """Ask the user if import and/or generate"""
    res = input(text + " (y, n): ")
    while not res in ["y", "n"]:
        res = input("Invalid choice (ctr-c to exit) :")

    return res == "y"

def getInDict(dictionary:dict, path:str):
    """Get an element in nested dict, ex 'a/b/c' -> dict[a][b][c] """
    d = dictionary
    for key in path.split("/"):
        d = d[key]

    return d


if __name__ == '__main__' :

    path_openplc = getOpenPLCPath()

    while True:
        lib_path, isZip, needConfig = getLibPath()

        #Config
        if needConfig:
            shutil.copyfile(f"{os.path.dirname(__file__)}/config.json", f"{lib_path}/config.json")
        
        with open(f"{lib_path}/config.json") as config_file:
            config = json.load(config_file)

        if needConfig:
            config["name"] = lib_path.split("/")[-1]
            for dict_path in ["arduino", "matiec", "xml", "arduino/module"]:
                path = f"{lib_path}/{getInDict(config, f"files/{dict_path}/path")}"
                if not os.path.exists(path):
                    os.mkdir(path)

            while not askYN("The library has no xml file, now?"):
                pass

        name = config["name"]

        #-xml
        xml_path = lib_path + "/" + config["files"]["xml"]["path"] + "/" + name + ".xml"
        all_blocks_names, all_blocks = getAllFunctionBlock(xml_path)
        config["blocks"] = all_blocks_names

        needImport = True
        needGenerate = False

        if not config["generated"]:
            needImport = False
            needGenerate = askYN("The library is not generated, do you want to do it")

        if needGenerate:
            generate(lib_path, config, all_blocks)  
            config["generated"] = True      
            needImport =  askYN("The library has been generated, do you want to import it")   
               
        if needImport:
            arduino_path = path_openplc + "/editor/arduino/src/lib"#Both .txt and .h in
            matiec_path  = path_openplc + "/matiec/lib"  #.txt in ./ and .h in ./C/
            plcopen_path = path_openplc + "/editor/plcopen"  
            modules_path = path_openplc + "/editor/arduino/examples/Baremetal/modules" 
            
        
            #Import file
            formPath = lambda src, dst, ext : (lib_path + "/" + src["path"] + "/" + name + ext, dst + "/" + name + ext)
            config_files = config["files"]
            
            copyList = [
                formPath(config_files["xml"],     plcopen_path,       ".xml"),
                formPath(config_files["matiec"],  matiec_path,        ".txt"),
                formPath(config_files["matiec"],  matiec_path + "/C", ".h"),
                formPath(config_files["arduino"], arduino_path,       ".txt"),
                formPath(config_files["arduino"], arduino_path,       ".h"),
            ]#(from, to)

            for arg in copyList :
                shutil.copyfile(*arg)

            #Arduino module
            needed_modules = config_files["arduino"]["module"]["modules"]
            all_modules = []
            modules_path = lib_path + "/" + config_files["arduino"]["module"]["path"]
            # - Add all available modules
            for file_path in glob.glob(modules_path + "/*.c"):
                module = os.path.basename(file_path).split(".")[0]
                all_modules.append(module)

                dst = modules_path + "/" + module + ".c"
                if os.path.isfile(dst):
                    print(f"Warning : The module {module} is already in OpenPLC")
                    if module in needed_modules :
                        needed_modules.remove(module)

                else :
                    shutil.copyfile(file_path, dst)
            
            # - Look for missing module
            for module in needed_modules :
                if not os.path.isfile(modules_path + "/" + module + ".c"):
                    print(f"Error : The module {module} couldn't be found")

                all_modules.append(module)

            config_files["arduino"]["module"]["modules"] = all_modules

            
            #definitions
            addToFile(
                plcopen_path + "/definitions.py",
                ["StdTC6Libs","]"],
                f',\n              (_("{name}"), join(sd, "{name}.xml"))'
            )
            

            #ArduinoUploadDialog.py
            #-to Add
            indent = "    "
            if len(all_modules) > 0:
                define_text = f"""\n{2*indent}for block in {all_blocks_names}:\n{3*indent}if (self.plc_program.find(block + ';') > 0):\n"""
                
                for module in all_modules:
                    define_text += 4*"    " + f"define_file += '#define USE_{module.upper()}_BLOCK'\n"

                #-add
                addToFile(
                    path_openplc + "/editor/dialogs/ArduinoUploadDialog.py",
                    ["\n        #Generate Arduino Extension"],
                    define_text
                )


            #arduino_libs.h
            with open(path_openplc + "/editor/arduino/examples/Baremetal/arduino_libs.h", "r+") as arduino_libs:
                for module in all_modules:
                    text = f"""#ifdef USE_{module.upper()}_BLOCK\n#include "modules/{module}.c"\n#endif"""
                    if arduino_libs.read().find(text) == -1:
                        arduino_libs.write(f"\n{text}\n")


            
            #standard_FB.txt
            for folder_path in [arduino_path, matiec_path]:
                addToFile(
                    folder_path + "/standard_FB.txt",
                    ["{enable code generation}"],
                    '{#include "' + name +'.txt" }\n'
                )

            #iec_std_FB.h
            for folder_path in [arduino_path, matiec_path + "/C"]:
                addToFile(
                    folder_path + "/iec_std_FB.h",
                    ["#endif //_IEC_STD_FB_H"],
                    f'#include "{name}.h"\n'
                )


            #Update config
            with open(lib_path + "/config.json", 'w', encoding='utf-8') as f:
                json.dump(config, f, ensure_ascii=False, indent=4)

            if isZip :
                shutil.rmtree(lib_path)
            print(f"The library {name} as been imported successfully")
