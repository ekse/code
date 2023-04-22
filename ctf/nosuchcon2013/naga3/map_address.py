addresses = [
    0x0804A010, # read
    0x0804A014, # printf
    0x0804A030, # puts
    0x0804A03C, # exit
]

BASE     = 0x0804A100
TARGET 	 = addresses[0]


i = 0
n = 0
while i <= 0xFFFFFFFF:
    i=(31580641*n)
    writeaddr = 0
    diff = 0
    
    while True:
        writeaddr = (BASE + (i * 0x88)) & 0xFFFFFFFF
        if writeaddr >=  TARGET:
            diff = writeaddr - TARGET
            if   diff <= 0x88:
                break
            else:
                i -= 1
        else:
            diff = TARGET - writeaddr
            if  diff <= 0x88:
                break
            else:
                i += 1
        
    
    print "i = %08x writeaddr =  %08x diff = %d" % (i, writeaddr, diff)
    n += 1
