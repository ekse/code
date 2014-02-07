import sys
import os

import pefile

extensions = ['.exe', '.dll', '.sys']

pe =  pefile.PE(sys.argv[1], fast_load=True)
overlay_offset = pe.get_overlay_data_start_offset()
if overlay_offset:
    print("Overlay at {0}".format(hex(overlay_offset)))
    new_pe = pe.trim()
    filename = os.path.basename(sys.argv[1])
    dirname = os.path.dirname(sys.argv[1])
    
    no_ext = True
    for ext in extensions:
        if filename.endswith(".exe"):
            filename = filename.replace(".exe", "-noverlay.exe")
            no_ext = False
            break
    if no_ext:
        filename = filename + ".noverlay"
    
    f = open(os.path.join(dirname,filename), "wb")
    f.write(new_pe)
    f.close()
    
    print("Wrote PE without overlay to {0}".format(filename))
    
else:
    print("No overlay")