
import sys 

"""
Pretti complicated solution: 
It is based on the fact that every question g gives results in the form 
a1 * 2**g + a2 * 2**(g/2) + a3 * 2**(g/3) ... a6 * 2**(g/6)

So, if the first guess g is big enough (last three terms g/6, g/5, g/4 are separated by at least 7, which is 128>100) and g/4 < 2**63 we can guess 
the last three rings by doing result % 2**(g/(i+1)) / 2**(g/i).
"""

T_W = input()
T = int(T_W.split(" ")[0])
W = int(T_W.split(" ")[1])

for t in range (1, T+1):
    
    print(210, flush=True)
    res1 = int(input())

    # First try to compute last 3 rings of Odin
    ring6 = int(((res1 % (2**42)) / 2**35))
    ring5 = int(((res1 - ring6* (2 ** 35)) % (2**52)) / 2**42)
    ring4 = int(((res1 - ring6 * (2 ** 35) - ring5 * (2 ** 42)) % (2**70)) / 2**52)
    
    print(54, flush=True)
    
    res2 = int(input())

    total_partial = (2**9) * ring6 + (2**10) * ring5 + (2**13) * ring4

    res2 -= total_partial

    #sys.stderr.write(str(res2) + "\n")
    #sys.stderr.write(str(total_partial) + "\n")
    
    ring1 = int(res2 / (2**54))
    
    ring2 = int((res2 - (ring1*(2**54))) / 2**27)

    ring3 = int ( ( res2 - (ring1* (2**54) ) - (ring2*(2**27)) ) / 2**18 )


    print("{} {} {} {} {} {}".format(ring1, ring2, ring3, ring4, ring5, ring6), flush=True)

    response = int(input())
    if response == -1:
        exit(1)
    

