def mergeSort(a):
    width = 1
    n = len(a)										 

    while (width < n):
        l=0;
        while (l < n): 
            r = min(l+(width*2-1), n-1)		 
            m = min(l+width-1,n-1)
             
            merge(a, l, m, r)
            l += width*2
        width *= 2
    return a

def merge(a, l, m, r): 
    n1 = m - l + 1
    n2 = r - m
    L = [0] * n1
    R = [0] * n2
    for i in range(0, n1): 
        L[i] = a[l + i] 
    for i in range(0, n2): 
        R[i] = a[m + i + 1] 

    i, j, k = 0, 0, l 
    try:
        while True:
            if L[i] <= R[j]: 
                a[k] = L[i] 
                i += 1
            else: 
                a[k] = R[j] 
                j += 1
            k += 1
    except IndexError:
        pass

    for o in range(i, n1):
        a[k] = L[o] 
        k += 1
    for p in range(j, n2):
        a[k] = R[p] 
        k += 1
    


