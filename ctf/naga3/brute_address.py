import sys
BASE = 0x0804A100

addresses = [
    0x0804A010, # read
    0x0804A014, # printf
    0x0804A030, # puts
    0x0804A03C, # exit
]

i = 0
while (i <= 0xFFFFFFFF):
    if i % 100000 == 0 :
        print("Trying i = {0}...".format(hex(i)))
    
    writeAddr = (BASE + (i * 0x88)) & 0xFFFFFFFF
    for addr in addresses:
        if addr == writeAddr or (addr > writeAddr and addr - writeAddr <= 8):
            print("FOUND : writeAddr {0} i = {1}".format(hex(writeAddr), i))
            sys.exit()
    i += 1
        

