t = int(input())

for T in range(t):
    s1 = input()
    s2 = input()

    b1s = len(s1) - len(s1.replace("B", ""))
    b2s = len(s2) - len(s2.replace("B", ""))
    if b1s % 2 == b2s % 2:
        s1 = s1.replace("B", "")
        s2 = s2.replace("B", "")
        
        stop1 = False
        while not stop1 and len(s1) > 0:
            tmp = s1.replace("AA", "").replace("CC", "")
            if len(tmp) < len(s1):
                s1 = tmp
            else:
                stop1 = True
        stop2 = False
        while not stop2 and len(s2) > 0:
            tmp = s2.replace("AA", "").replace("CC", "")
            if len(tmp) < len(s2):
                s2 = tmp
            else:
                stop2 = True
        print("{}".format("YES" if s1 == s2 else "NO"))
    else:
        print("NO")
