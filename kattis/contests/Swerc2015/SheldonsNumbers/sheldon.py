from math import sin, cos, pi, acos, sqrt, asin, atan2


DEBUG = False


def debug(name, x):
    if DEBUG:
        print("{}: {}".format(name, x))


X, Y = [int(x) for x in input().split()]

result = 0

values = set()

for i in range(1, 64):   # Number of ones
    for j in range(1, 64):    # Number of zeros
        tempval = 0  # this is the minumum
        repetitions_ones = 0
        repetitions_zeros = 0
        add_zero = False
        while ((repetitions_ones * i) + (repetitions_zeros * j)) <= 64:
            if tempval != 0:
                if tempval >= X and tempval <= Y and tempval not in values:
                    result += 1
                    debug("tempval", tempval)
                    values.add(tempval)
            if add_zero:
                repetitions_zeros += 1
                add_zero = False
                tempval *= 2**j
            else:
                repetitions_ones += 1
                add_zero = True
                tempval = tempval * (2**i) + (2**i - 1)

print(result)