#!/usr/bin/env python2
import sys
import marshal
import imp

f = open(sys.argv[1], 'rb')
f.seek(17) # Skip the header, you have to know the header size beforehand
ob=marshal.load(f)
for i in range(0, len(ob)):
    filename = str(i) + ".pyc"
    print("writing {}...".format(filename))
    open(filename, 'wb').write(imp.get_magic() + '\0'*4 + marshal.dumps(ob[i]))
f.close()
