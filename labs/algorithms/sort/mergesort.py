# merges 2 sorted lists.
def _merge(a, b):
    m = list()
    while len(a) > 0 and len(b) > 0:
        # pick the next smallest element from a or b.
        if a[0] <= b[0]:
            m.append(a.pop(0))
        else:
            m.append(b.pop(0))
    m.extend(a)
    m.extend(b)
    return(m)

# mergesort uses the divide and conquer strategy to sort an array.
# It recursively divides an array in 2 parts and sorts the arrays when
# they contain 2 or less elements. It then merges the sorted arrays by 
# traversing them from right to left and adding the smallest element to the
# sorted array.
#
def mergesort(x):
    if len(x) <= 1:
       return(x)
    else:
        # divide the array in 2 and mergesort both parts
        mid = len(x)//2
        a = mergesort(x[:mid])
        b = mergesort(x[mid:])
        return(_merge(a,b))
