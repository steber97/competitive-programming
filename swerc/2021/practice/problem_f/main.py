import math
n = int(input())
res = 0
for t in range(n):
    temp = 0
    b = int(input())
    edges = []
    for node in range(b):
        x, y = [int(el) for el in input().split()]
        edges.append((x, y))
    for i in range(b):
        temp += (edges[i][0] * edges[(i+1)% b][1] - edges[i][1] * edges[(i+1)% b][0])
    temp /= 2
    temp = abs(temp)
    res += temp
res = math.floor(res)
print(res)
    

