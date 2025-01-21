import subprocess
import os
import platform

def compile_c(st_program, openplc_folder):
    compiled_program = ''
    matiec_bin = 'iec2c'
    matiec_folder = os.path.join(openplc_folder, 'matiec')

    # Write temp st
    st_file = open(os.path.join(matiec_folder, "temp.st"), "w")
    st_file.write(st_program)
    st_file.close()

    # Call matiec
    if platform.system() == 'Windows':
        matiec_bin = 'iec2c.exe'
    elif platform.system() == 'Darwin':
        matiec_bin = 'iec2c_mac'
    
    result = subprocess.run([os.path.join(matiec_folder, matiec_bin), '-p', '-l', '-s', '-n', '-r', '-R', '-a', '-i', '-b', 'temp.st'], cwd=matiec_folder, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    print(result.stdout.decode('utf-8'))
    print(result.stderr.decode('utf-8'))

    if result.returncode != 0:
        print("Error generating C files")
        exit(-1)

    c_file = open(os.path.join(matiec_folder, "POUS.h"), "r")
    compiled_program += c_file.read()
    c_file.close()
    c_file = open(os.path.join(matiec_folder, "POUS.c"), "r")
    compiled_program += c_file.read()
    c_file.close()

    # Strip the first 5 lines and append "static" to every function
    line_count = 0
    lines = compiled_program.splitlines()
    compiled_program = ''
    for line in lines:
        if line_count < 5:
            line_count += 1
            continue

        if not line.startswith(" ")\
           and not line.startswith("\t")\
           and not line.startswith("static")\
           and not line.startswith("//")\
           and not line.startswith("}")\
           and not line.startswith("{")\
           and not line.startswith("_")\
           and not line.startswith("typedef")\
           and line != '':
            line = 'static ' + line
        
        if not '#endif //__POUS_H' in line:
            compiled_program += line + '\n'

    return compiled_program

def update_lib(c_filename, data):
    lines = data.split('\n')
    return_str = ''
    for line in lines:
        if c_filename in line:
            # Lib file already includes st_filename
            return data
        if '#endif //_IEC_STD_FB_H' in line:
            # Last line of lib file... must include st_filename
            return_str += '#include "' + c_filename + '"\n#endif //_IEC_STD_FB_H'
        else:
            return_str += line + '\n'
    
    return return_str
