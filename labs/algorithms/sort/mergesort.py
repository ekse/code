def __sort(x):
    if len(x) <= 1:
        return(x)
    elif len(x) == 2:
        if x[0] > x[1]:
            temp = x[0]
            x[0] = x[1]
            x[1] = temp
        return(x)
    else:
        raise Exception("array larger than size 2")

def __merge(a, b):
    m = list()
    i = 0
    ai = 0
    bi = 0
    while i < len(a+b):
        # check if we reached the end of either the a or b array
        if ai >= len(a):
            # copy the rest of b
            m += b[bi:]
            break
        if bi >= len(b):
            # copy the rest of a
            m += a[ai:]
            break

        # pick the next smallest element from a or b.
        if a[ai] <= b[bi]:
            m.append(a[ai])
            ai += 1
        else:
            m.append(b[bi])
            bi += 1
        i += 1

    return(m)

# mergesort uses the divide and conquer strategy to sort an array.
# It recursively divides an array in 2 parts and sorts the arrays when
# they contain 2 or less elements. It then merges the sorted arrays by 
# traversing them from right to left and adding the smallest element to the
# sorted array.
def mergesort(x):
    if len(x) <= 2:
        __sort(x)
        return(x)
    else:
        # divide the array in 2 and mergesort both parts
        mid = len(x)//2
        a = mergesort(x[:mid])
        b = mergesort(x[mid:])
        return(__merge(a,b))
