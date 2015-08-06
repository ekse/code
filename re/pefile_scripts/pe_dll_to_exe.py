# This script converts a DLL to a standard executable.

import sys
import pefile

if len(sys.argv) < 1:
    print("usage : pe_dll_to_exe.py <filename> [<output_filename>]")
    sys.exit(0)

dll_filename = sys.argv[1]

exe_filename = "default.exe"
if len(sys.argv) == 3:
    exe_filename = sys.argv[2]
elif dll_filename.endswith(".dll"):
    exe_filename = dll_filename.replace(".dll", ".exe")
else:
    exe_filename = dll_filename + ".exe"

pe = pefile.PE(dll_filename)

# check that the file has the dll flag
if not (pe.FILE_HEADER.Characteristics & pefile.IMAGE_CHARACTERISTICS["IMAGE_FILE_DLL"]):
    print("This file is not a DLL")
    sys.exit()

# remove the DLL flag
pe.FILE_HEADER.Characteristics = pe.FILE_HEADER.Characteristics ^ pefile.IMAGE_CHARACTERISTICS["IMAGE_FILE_DLL"]
pe.write(filename=exe_filename)
print("Wrote executable to {0}".format(exe_filename))
