import sys
import struct

from gdb import Gdb
from ptrace.debugger import PtraceDebugger, ProcessSignal, ProcessExit

pid = sys.argv[1]
gdb = Gdb()
gdb.debugger = PtraceDebugger()
gdb.process  = None

gdb.attachProcess(pid)
print("[!] attached to {0}".format(pid))

#gdb.breakpoint("0x80487e0")
gdb.breakpoint("0x080487d6")
gdb.breakpoint("0x08048802")
while(True):

    try:
        gdb.cont()
        eip = gdb.process.getreg("eip")
        print("EIP: {0}".format(hex(eip)))

        #if eip == 0x80487e0:
        #    print("pipe descriptor: {0}".format(hex(gdb.process.getreg("eax"))))

        # WRITE WHERE
        if eip == 0x80487d6:
            eax = gdb.process.getreg("eax")
            i = gdb.process.readBytes(eax, 4)
            print("Current id loc: {0} value : {1}".format(hex(eax), struct.unpack("<I",i)))
            print("Changing data location for write of id...")
            gdb.process.writeBytes(0x0804a060, struct.pack("<I",63161282))
            gdb.process.setreg("eax", 0x0804a060)

        # WRITE WHAT
        if eip == 0x08048802:
            gdb.process.writeBytes(0x0804a060, struct.pack("<I", 0x08048828) + "\xFF\xF1\xF2\xF3")
            gdb.process.setreg("eax", 0x0804a060)



    except ProcessSignal, event:
        print("[!] Event {0}".format(event))
        continue
    except ProcessExit, event:
        print(event)
    except Exception, event:
        print("Unhandled exception : {0}".format(event))
        break
