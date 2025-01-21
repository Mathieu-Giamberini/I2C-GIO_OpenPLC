from st_writer import FunctionBlock, Variable, generate_st
from h_writer import generate_h
import os

def wirte_missing(text:str, path:str):
    if not os.path.isfile(path):
        with open(path, "w") as file:
            file.write(text)

def generate(lib_path:str, config:dict, all_blocks:list[FunctionBlock]):
    st_str = generate_st(all_blocks)
    h_str = generate_h(all_blocks)
    name = config["name"]

    for part in ["arduino", "matiec"]:
        path = f"{lib_path}/{config["files"][part]["path"]}/{name}"
        wirte_missing(st_str, f"{path}.txt")
        wirte_missing(h_str, f"{path}.h")

        

