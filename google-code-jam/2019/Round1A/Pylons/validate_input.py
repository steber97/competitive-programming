
f_out = open('output')
f_in = open('input_big2')

for i, line in enumerate(f_in):
    print(line)
    if i == 0:
        # first line, with test cases.
        #print("pass")
        pass
    else:
        numbers = line.split(" ")
        n = int(numbers[0])
        m = int(numbers[1])
        mat_passed = [ [False for j in range (0, m)] for i in range (0,n) ]
        res = f_out.readline()
        #print(res)
        if res.find("IMPOSSIBLE") != -1:
            pass
            #print("impossible")
        else:
            prev_x = -1
            prev_y = -2
            for j in range(n * m):
                coord = f_out.readline()
                # print(coord)
                x = int(coord.split()[0])
                y = int(coord.split()[1])
                if mat_passed[x-1][y-1] is True:
                    print("Found error already passed {}, {}".format(x, y))
                if x == prev_x or y == prev_y or x - y == prev_x - prev_y or x + y == prev_x + prev_y:
                    print("found error {}".format(line))
                mat_passed[x-1][y-1] = True
                prev_y = y
                prev_x = x
                


