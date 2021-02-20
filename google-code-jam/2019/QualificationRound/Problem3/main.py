

"""
This problem performs Euclidean algorithm on very large numbers (10**100).
"""

from pprint import pprint

def MCD(val1, val2):
    v1 = max(val1, val2)
    v2 = min(val1, val2)

    rest = v1 % v2
    if rest == 0:
        return v2
    else:
        return MCD(v2, rest)

# input() reads a string with a line of input, stripping the ' ' (newline) at the end.
# This is all you need for most Code Jam problems.
T = int(input()) # read a line with a single integer
for t in range(1, T + 1):

    # N is the biggest possible prime number
    # m is the length of our string
    N, m = [int(s) for s in input().split(" ")] 
    
    numbers = [int(s) for s in input().split(" ")]

    #print(numbers)

    list_of_prime_numbers = []  # the first prime number will be added later, at the end of the for loop

    # perform MCD on numbers[0] and numbers[1], of course the MCD will be common value y among numbers[0] and numbers[1]
    # in fact they are defined as x*y, y*z for some very very big prime integers x,y,z
    
    first_different_couple = 0
    while numbers[first_different_couple] == numbers[first_different_couple+1]:
        list_of_prime_numbers.append(0)
        first_different_couple += 1
    common_val = MCD(numbers[first_different_couple], numbers[first_different_couple+1])
    list_of_prime_numbers.append(int(numbers[first_different_couple] / common_val))
    list_of_prime_numbers.append(int(common_val))

    #print(first_different_couple)
    print(list_of_prime_numbers)

    for i in range (first_different_couple+1, len(numbers)):
        #print(list_of_prime_numbers[i])    
        list_of_prime_numbers.append(int(numbers[i] / list_of_prime_numbers[i]))

    for i in range(first_different_couple-1, -1, -1):
        list_of_prime_numbers[i] = (int(numbers[i] / list_of_prime_numbers[i+1]))

    duplicate_list_to_sort = [x for x in list_of_prime_numbers]
    duplicate_list_to_sort.sort()

    map_number_to_letter = {duplicate_list_to_sort[0]: 'A'}
    last_char = 'A'
    for i in range (1, len(duplicate_list_to_sort)):
        if duplicate_list_to_sort[i] != duplicate_list_to_sort[i-1]:
            map_number_to_letter[duplicate_list_to_sort[i]] = chr(ord(last_char) + 1)
            last_char = chr(ord(last_char) + 1)

    pprint(map_number_to_letter)
    #print(map_number_to_letter)


    # TODO: Need to be careful when consecutive numbers are equal
    #print(list_of_prime_numbers)

    result = ""
    for el in list_of_prime_numbers:
        result += map_number_to_letter[el]
    print("Case #{}: {}".format(t, result))

  