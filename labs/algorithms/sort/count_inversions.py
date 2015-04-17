def __sortAndCountInversions(x):
    if len(x) <= 1:
        return(0, x)
    elif len(x) == 2:
        inv = 0
        if x[0] > x[1]:
            inv = 1
            temp = x[0]
            x[0] = x[1]
            x[1] = temp
        return(inv, x)
    else:
        raise Exception("array larger than size 2")

def __mergeAndCountInversions(a, b):
    m = list()
    i = 0
    ai = 0
    bi = 0
    inv = 0
    while i < len(a+b):
        # check if we reached the end of either the a or b array
        if ai >= len(a):
            # copy the rest of b
            m += b[bi:]
            break
        if bi >= len(b):
            # copy the rest of a
            m += a[ai:]
            n = len(a) - ai
            inv += (n * (n-1)) // 2
            break

        # pick the next smallest element from a or b.
        if a[ai] <= b[bi]:
            m.append(a[ai])
            ai += 1
        else:
            inv += len(a) - ai
            m.append(b[bi])
            bi += 1
        i += 1

    return(inv, m)

# counts the number of inversions in an array. this function is based on the
# MergeSort algorithm.

# returns a tuple (int nbinv, list sorted_x) 
def CountInversions(x):
    if len(x) <= 2:
        inv, sorted_x = __sortAndCountInversions(x)
        return(inv, sorted_x)
    else:
        # divide the array in 2 and mergesort both parts
        mid = len(x)//2
        inva, a = CountInversions(x[:mid])
        invb, b = CountInversions(x[mid:])
        invc, c = __mergeAndCountInversions(a, b)
        return(inva + invb + invc, c)
