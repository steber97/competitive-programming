
import random

number_of_nodes = 300
number_of_edges = 8266


# Number of test cases
print(1)

print(number_of_nodes)   # From 1 to 500, ignore all other vertices

#Print start, number of people, edges number
print("1 10 100")

print(10)

print(10)
print(100)
print(25)
print(42)
print(289)
print(167)
print(86)
print(240)
print(102)
print(200)

# Number of edges
print(number_of_edges)

f = open('big_input', 'r')
for line in f:
    node1 = int(line.split(" ")[0]) + 1
    node2 = int(line.split(" ")[1]) + 1
    if node1 <= number_of_nodes and node2 <= number_of_nodes:
        line_to_print = ""
        line_to_print += str(node1) + " " + str(node2) + " "
        people = random.randint(1,5)
        time = random.randint(1,10)
        print(line_to_print + str(people) + " " + str(time) )
