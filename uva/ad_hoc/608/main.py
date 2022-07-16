if __name__ == "__main__":
    letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L']
    N = int(input())
    for n in range(N):
        lines = []
        for i in range(3):
            lines.append(input())
        
        for i in letters:
            for w in ['heavy', 'light']:
                map_res = {}
                for j in letters:
                    map_res[j] = 1
                map_res[i] = 0 if w == 'light' else 2
                count = 0
                for l in lines:
                    l1, l2, val = l.split()
                    sum1 = sum([map_res[x] for x in l1])
                    sum2 = sum([map_res[x] for x in l2])
                    count += 1 if (sum1 < sum2 and val == 'down') or \
                        (sum1 > sum2 and val == 'up') or \
                            (sum1 == sum2 and val == 'even') else 0
                if count == 3:
                    print("{} is the counterfeit coin and it is {}.".format(
                        i, w
                    ))