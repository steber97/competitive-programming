if __name__== "__main__":
    T = int(input())
    for t in range(T):
        n = int(input())
        iter = 0
        while str(n) != "".join([x for x in reversed(str(n))]):
            iter += 1
            n = n + int("".join([x for x in reversed(str(n))]))
        print(iter, n)