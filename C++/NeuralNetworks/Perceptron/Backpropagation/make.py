import os
import json
import hashlib
import subprocess
from colorama import Fore, Style


def get_rows_and_columns():
    rows, columns = os.popen('stty size', 'r').read().split()
    rows = int(rows)
    columns = int(columns)
    if not rows: rows = 20
    if not columns: columns = 120
    return rows-4, columns-4


def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()


def get_typed_files_in_dir(dir_path, file_type, replace_path=False):
    return_files = []
    for root, dirs, files in os.walk(dir_path):
        for file in files:
            if file.endswith(file_type):
                if replace_path:
                    return_files.append(os.path.join(root, file).replace(dir_path, ""))
                else:
                    return_files.append(os.path.join(root, file))
    return return_files


def run_subprocess(command):
    perfect_text = "[PERFECT]"
    columns = get_rows_and_columns()[1]
    print(command, end="")
    print(" "*(int(columns) - len(command)-len(perfect_text)), end="")
    split_comand = command.split(" ")
    if "" in split_comand:
        split_comand.remove("")
    process = subprocess.Popen(split_comand, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, errors = process.communicate()
    correct = True
    if output.decode():
        print()
        print(Fore.BLUE, output.decode(), Style.RESET_ALL, end="")
        correct = False
    if errors.decode():
        print()
        print(Fore.RED, errors.decode(), Style.RESET_ALL, end="")
        correct = False
        return False
    if correct:
        print(Fore.GREEN, perfect_text, Style.RESET_ALL)
    return True


cxx = "g++"
source_dir = "src/"
build_dir = "build/"
include_dirs = ["include"]
libs = ""

files_hashs = {}
if os.path.exists(".hashs"):
    files_hashs = json.load(open(".hashs", "r"))


files_to_build = get_typed_files_in_dir(source_dir, ".cpp", True)
for file in files_to_build:
    input_file = source_dir+file
    output_file = (build_dir+file).replace(".cpp", ".o")
    file_hash = md5(input_file)
    if files_hashs.get(input_file) == file_hash and os.path.exists(output_file):
        alr_comp_text = "[already compiled]"
        columns = get_rows_and_columns()[1]
        print(input_file, " "*(columns-len(input_file) - len(alr_comp_text)), Fore.GREEN, alr_comp_text, Style.RESET_ALL)
        continue
    output_dir = output_file.split("/")[:len(output_file.split("/"))-1]
    output_dir = "/".join(output_dir)
    if not os.path.exists(output_dir):
        os.mkdir(output_dir)
    command = f"{cxx} -c {input_file} -o {output_file} "
    for include in include_dirs:
        command += f"-I {include} "
    if not run_subprocess(command):
        exit()
    files_hashs[input_file] = file_hash


json.dump(files_hashs, open(".hashs", "w"))

output_files = " ".join(get_typed_files_in_dir(build_dir, ".o"))
result_file = build_dir+"main"


command = f"{cxx} {output_files} -o {result_file} {libs}"
if not run_subprocess(command):
    exit()
