#!/usr/bin/python3

import sys
import platform
import os
import xml_writer
import st_writer
import c_writer
import function_block

def print_usage():
    print("Usage: import_tool.py <filename>")


def main(argc, argv):
    print('\nOpenPLC Import Tool - create XML projects or library blocks for OpenPLC Editor\nCopyright 2023 OpenPLC\n----------\n')

    if argc < 2:
        print("Error: You must provide a Structured Text file with the FunctionBlocks to be added")
        print_usage()
        exit(-1)
    
    st_file = argv[1]

    print("Parsing ST file...")

    try:
        with open(st_file, "r") as file:
            data = file.read()

    except FileNotFoundError:
        print(f"Error: File '{st_file}' not found. You must provide a Structured Text file with the FunctionBlocks to be added")
        exit(-1)
    except IOError:
        print(f"Error: Could not read file '{st_file}'. You must provide a valid Structured Text file with the FunctionBlocks to be added")
        exit(-1)

    function_blocks = function_block.parse_structured_text(data)

    if len(function_blocks) < 1:
        print(f"Error: No FunctionBlocks detected in file '{st_file}'")
        exit(-1)

    print("\nPlease select which POU you would like to add:")
    counter = 1
    for fb in function_blocks:
        print(f"'{counter}'. '{fb.name}'")
        counter += 1
    if counter > 2:
        print(f"'{counter}'. All of them")
    option = 0
    while option < 1 or option > counter:
        user_input = input("")
        if user_input.isdigit():
            option = int(user_input)
        if option < 1 or option > counter:
            print("Invalid option")
    
    if option != counter: #user chose to add only a specific block
        fb_selected = function_blocks[option - 1]
        function_blocks = []
        function_blocks.append(fb_selected)

    print("\nPlease choose how you would like to proceed:")
    print("1. Create a new XML program with the selected POUs")
    print("2. Import selected POUs to OpenPLC Library")
    option = 0
    while option < 1 or option > 2:
        user_input = input("")
        if user_input.isdigit():
            option = int(user_input)
        if option < 1 or option > 2:
            print("Invalid option")

    if option == 1: #Create XML program
        folder_created = False
        while folder_created is not True:
            print("Type the project name: ")
            proj_name = input("")
            try:
                os.mkdir(proj_name)
                folder_created = True
            except OSError as error:
                print(error)
                folder_created = False
        
        beremiz_file, plc_file = xml_writer.generate_plc_project(proj_name, function_blocks)

        beremiz_xml = os.path.join(proj_name, 'beremiz.xml')
        with open(beremiz_xml, 'w') as file:
            file.write(beremiz_file)
        
        plc_xml = os.path.join(proj_name, 'plc.xml')
        with open(plc_xml, 'w') as file:
            file.write(plc_file)

        project_folder = os.path.join(os.getcwd(), proj_name)
        print("PLC Project generated at folder: " + project_folder)

    elif option == 2: #Import POUs to OpenPLC Library
        print("Detecting OpenPLC Editor installation...")
        openplc_folder = os.getcwd()
        if not (os.path.isfile(os.path.join(openplc_folder, 'editor', 'Beremiz.py'))):
            if platform.system() == 'Windows':
                openplc_folder = os.path.expanduser('~') + '\\OpenPLC_Editor'
            elif platform.system() == 'Darwin':
                openplc_folder = '/Applications/OpenPLC Editor.app/Contents/Resources'

            #Try again
            while not (os.path.isfile(os.path.join(openplc_folder, 'editor', 'Beremiz.py'))):
                print(f"Could not detect OpenPLC Editor installation at '{openplc_folder}'. Please type the folder where OpenPLC Editor was installed on your computer. Type 'exit' to exit")
                openplc_folder = input("Folder: ")
                if openplc_folder == 'exit':
                    exit(-1)
        
        print("Type the lib name: ")
        lib_name = input("")

        # Update definitions.py file
        def_file = os.path.join(openplc_folder, 'editor', 'plcopen', 'definitions.py')
        try:
            with open(def_file, "r") as file:
                data = file.read()

        except FileNotFoundError:
            print(f"Error: File '{def_file}' not found. Your OpenPLC installation might be corrupted")
            exit(-1)
        except IOError:
            print(f"Error: Could not read file '{def_file}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        data = xml_writer.update_definitions(lib_name, data)
        with open(def_file, 'w') as file:
            file.write(data)

        # Create XML file with the custom POUs
        xml_filename = lib_name.replace(' ', '_') + '.xml'
        xml_file = os.path.join(openplc_folder, 'editor', 'plcopen', xml_filename)
        try:
            with open(xml_file, "r") as file:
                data = file.read()

        except FileNotFoundError:
            data = None
        except IOError:
            print(f"Error: Could not read file '{xml_file}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        xml_data = xml_writer.generate_xml(lib_name, function_blocks, data)

        xml_lib_file = open(xml_file, 'w+')
        xml_lib_file.write(xml_data)
        xml_lib_file.close()


        # Create ST/TXT file with the custom POUs
        st_filename = lib_name.replace(' ', '_') + '.txt'
        c_filename = lib_name.replace(' ', '_') + '.h'
        st_file_system = os.path.join(openplc_folder, 'matiec', 'lib', st_filename)
        c_file_system = os.path.join(openplc_folder, 'matiec', 'lib', 'C', c_filename)
        st_file_arduino = os.path.join(openplc_folder, 'editor', 'arduino', 'src', 'lib', st_filename)
        c_file_arduino = os.path.join(openplc_folder, 'editor', 'arduino', 'src', 'lib', c_filename)
        try:
            with open(st_file_system, "r") as file:
                data = file.read()

        except FileNotFoundError:
            data = None
        except IOError:
            print(f"Error: Could not read file '{st_file_system}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        st_prog = st_writer.generate_st(function_blocks, data)
        c_prog = c_writer.compile_c(st_prog, openplc_folder)

        # Write system lib
        st_file = open(st_file_system, 'w+')
        st_file.write(st_prog)
        st_file.close()
        c_file = open(c_file_system, 'w+')
        c_file.write(c_prog)
        c_file.close()
        # Write arduino lib
        st_file = open(st_file_arduino, 'w+')
        st_file.write(st_prog)
        st_file.close()
        c_file = open(c_file_arduino, 'w+')
        c_file.write(c_prog)
        c_file.close()

        # Update system matiec txt lib
        matiec_lib = os.path.join(openplc_folder, 'matiec', 'lib', 'standard_FB.txt')
        try:
            with open(matiec_lib, "r") as file:
                data = file.read()

        except FileNotFoundError:
            print(f"Error: Could not open file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        except IOError:
            print(f"Error: Could not read file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        lib_data = st_writer.update_lib(st_filename, data)
        lib_file = open(matiec_lib, 'w+')
        lib_file.write(lib_data)
        lib_file.close()

        # Update system matiec C lib
        matiec_lib = os.path.join(openplc_folder, 'matiec', 'lib', 'C', 'iec_std_FB.h')
        try:
            with open(matiec_lib, "r") as file:
                data = file.read()

        except FileNotFoundError:
            print(f"Error: Could not open file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        except IOError:
            print(f"Error: Could not read file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        lib_data = c_writer.update_lib(c_filename, data)
        lib_file = open(matiec_lib, 'w+')
        lib_file.write(lib_data)
        lib_file.close()

        # Update arduino matiec txt lib
        matiec_lib = os.path.join(openplc_folder, 'editor', 'arduino', 'src', 'lib', 'standard_FB.txt')
        try:
            with open(matiec_lib, "r") as file:
                data = file.read()

        except FileNotFoundError:
            print(f"Error: Could not open file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        except IOError:
            print(f"Error: Could not read file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        lib_data = st_writer.update_lib(st_filename, data)
        lib_file = open(matiec_lib, 'w+')
        lib_file.write(lib_data)
        lib_file.close()

        # Update arduino matiec C lib
        matiec_lib = os.path.join(openplc_folder, 'editor', 'arduino', 'src', 'lib', 'iec_std_FB.h')
        try:
            with open(matiec_lib, "r") as file:
                data = file.read()

        except FileNotFoundError:
            print(f"Error: Could not open file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        except IOError:
            print(f"Error: Could not read file '{matiec_lib}'. Your OpenPLC installation might be corrupted")
            exit(-1)
        
        lib_data = c_writer.update_lib(c_filename, data)
        lib_file = open(matiec_lib, 'w+')
        lib_file.write(lib_data)
        lib_file.close()

    

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)


