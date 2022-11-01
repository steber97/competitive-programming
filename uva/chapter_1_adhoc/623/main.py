import math 

if __name__ == "__main__":

    while True:
        try:
            text = input()
            n = int(text)
            print("{}!".format(n))
            print(math.factorial(n))
        except EOFError:
            break

