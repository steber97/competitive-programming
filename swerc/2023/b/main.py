import numpy as np

# Problem available at https://swerc.eu/2022/problems/

if __name__ == "__main__":
    a = input()
    n, m = a.split()
    n = int(n)
    m = int(m)

    a = input()
    S = [int(x) for x in a.split()]

    P = np.zeros((n, n, n))
    for i in range(n):
        for j in range(n):
            P[0][i][j] = 1/(n-i-1) if i < j else 0
    for k in range(1, n):
        P[k] = P[k-1] @ P[0]

    p = np.zeros(m)
    for i in range(m):
        for k in range(1, n-S[i]+1):
            prod = 1
            for q in range(m):
                if q != i:
                    prod *= 1 if k == 1 else np.sum(P[k-2][S[q]-1][S[q]:n-1])
            p[i] += P[k-1][S[i]-1][n-1] * prod
    print(" ".join([str(x) for x in p]))
    
    


    