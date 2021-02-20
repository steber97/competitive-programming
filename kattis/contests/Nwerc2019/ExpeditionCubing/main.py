from math import sin, cos, pi, acos, sqrt, asin, atan2

a = input()

t = float(input())


v = [float(x) for x in a.split(" ")]

v.sort()


if ((v[0] + v[1] + v[2]) > (t + t + t )) and (abs(v[0] + v[1] + v[2] - t-t-t) > 0.0001):
    print("impossible")


elif ((v[1] + v[2] + v[3]) < (t + t + t)) or (abs(v[1] + v[2] + v[3] - t-t-t) < 0.0001):
    print("infinite")

else:
    steps = [float(i/100) for i in range(0, 2001)]
    for i in range(len(steps)-1, 0, -1):
        j = steps[i]
        if ((v[1] + v[2] + j) < (t + t + t)) or (abs(v[1] + v[2] + j - t - t - t) < 0.00001 ):
            print("{:.2f}".format(j))
            exit(0)
        
    

exit(0)