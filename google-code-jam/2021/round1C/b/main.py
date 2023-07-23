DEBUG = False
def debug(description, value):
    if DEBUG:
        print("{}: {}".format(description, value))

def next_roaring(num, j):
    if (j >= len(str(num))):
        return 10**40
    improved = False
    val = int(str(num)[:j]) - 1
    step = 0
    i = 0
    while i < len(str(num)):
        val += 1
        debug("val", val)
        debug("i", i)
        num_str = str(num)[i:i+len(str(val))]
        debug("num_str", num_str)
        if int(num_str) == val:
            # Do nothing, value not improved but still OK!
            pass
        elif int(num_str) < val:
            improved = True
        else:
            val = int(num_str)
            improved = True
        step += 1
        i += len(str(val))
    
    res = ""
    if not improved:
        val += 1
        if len(str(val)) > j:
            best = 10**40
            for l in range(1, 18):
                best = min(best, next_roaring(int("1" + "".join(
                    ['0' for i in range(len(str(num)))])), l))
            return best
    for i in range(0, step):
        res += str(val - step + i + 1)
    debug("res", res)
    return int (res)

if __name__ == '__main__':
    n = int(input())
    for i in range(1, n+1):
        num = int(input())
        if len(str(num)) == 1:
            best = 12
        else:
            debug("num", num)
            best = 10**40
            for j in range(1, 18):
                best = min(best, next_roaring(num, j))
        print("Case #{}: {}".format(i, best))