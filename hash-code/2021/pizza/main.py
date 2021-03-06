import numpy as np
import pandas as pd
from tqdm import tqdm
from sys import stdin, stderr


def eprint(*args, **kwargs):
    print(*args, file=stderr, **kwargs)


class Node: 
   
    # Function to initialize the node object 
    def __init__(self, id, hashList): 
        self.id = id  
        self.hashList = hashList
        self.next = None
        self.prev = None
   

# Linked List class 
class LinkedList:  
     
    # Function to initialize the Linked  
    # List object 
    def __init__(self):  
        self.head = None
        self.tail = None
    
    def append(self, node):
        if self.head == None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            node.prev = self.tail
            self.tail = node
    
    def remove(self, node):
        if node == self.head:
            self.head = node.next
        if node == self.tail:
            self.tail = node.prev
        if node.prev != None: 
            node.prev.next = node.next
        if node.next != None:
            node.next.prev = node.prev

    def __iter__(self):
        self.i = self.head
        return self

    def __next__(self):
        if self.i != None:
            result = self.i
            self.i = self.i.next
            return result
        else:
            raise StopIteration
    
    def __len__(self):
        _len = 0
        self.j = self.head
        while self.j != None:
            _len += 1
            self.j = self.j.next
        return _len


def makeAssignments(lledoList, t2, t3, t4, maxNumConflicts=0):
    """
    ordered by #ingredients per pizza
    edoList: (index, list[hash1, hash2, ...])
             (index, list[hash1, hash2, ...])
             (index, list[hash1, hash2, ...])
             (index, list[hash1, hash2, ...])
    """

    teams = [t4, t3, t2]
    members = [4, 3, 2]
    result = []
    remainingPizzas = len(lledoList)
    teamsServed = [0, 0, 0]
    indicesToDrop = []
    # Repeat for the teams (t4, t3, t2)
    for j, (t, m) in enumerate(zip(teams, members)):
        # For every team
        for i in range(t):
            if remainingPizzas == 0:
                # Stop in advance
                break
            pizzasTaken = []
            # For every pizza
            for p in lledoList:
                # Check for no conflicts
                hasConflicts = False
                for t in pizzasTaken:
                    conflicts = 0   
                    for h1, h2 in zip(t.hashList, p.hashList):
                        if h2 == h1:
                            conflicts += 1
                            if conflicts > maxNumConflicts:
                                hasConflicts = True
                                break
                if not hasConflicts:
                    pizzasTaken.append(p)
                    lledoList.remove(p)
                    remainingPizzas -= 1
                if len(pizzasTaken) == m:
                    break
            if len(pizzasTaken) == m:
                result.append([x.id for x in pizzasTaken])
                teamsServed[j] += 1
                indicesToDrop += [x.id for x in pizzasTaken]

    eprint("The number of unserved pizzas is: {}".format(len(lledoList)))

    return result, indicesToDrop, t2 - teamsServed[2], t3 - teamsServed[1], t4 - teamsServed[0]


def printRes(result):
    """
    result has format: 
    # lines
    # members, pizza1, pizza2 ...
    # members, pizza1, pizza2 ...
    """
    print(len(result))
    for el in result:
        print("{} {}".format(
            len(el),
            " ".join([str(x) for x in el])))


def parse_input():
    n_pizzas, teams_2, teams_3, teams_4 = map(int, stdin.readline().strip().split(" "))
    pizzas_sets = {}
    pizzas = []

    for i, _ in enumerate(range(n_pizzas)):
        _, *ingredients = stdin.readline().strip().split(" ")
        pizzas.append("|".join(ingredients))
        pizzas_sets[i] = set(ingredients)
    df = pd.Series(pizzas).str.get_dummies()
    
    return df, teams_2, teams_3, teams_4, pizzas_sets


def min_hash(df: pd.DataFrame):
    permuted_columns = np.random.permutation(df.columns)
    permuted_df = df[permuted_columns]
    
    # print(permuted_df)
    # print(permuted_df.to_numpy().argmax(axis=1))

    return permuted_df.to_numpy().argmax(axis=1)


def parse_input_build_hashes(df, numHashes):
    # np.random.seed(0)
    df['sum'] = df.sum(axis=1)
    sorted_df = df.sort_values(by='sum', ascending=False).drop(['sum'], axis=1, )

    # The constant controls the number of hashes taken
    min_hashes_list = np.array([min_hash(sorted_df) for x in range(numHashes)]).T

    return zip(sorted_df.index, min_hashes_list)


def changePizzaInTeams(i, j, result, pizzas_sets):
    set1 = set()
    set2 = set()
    for el in result[i]:
        set1 = set1.union(pizzas_sets[el])
    for el in result[j]:
        set2 = set2.union(pizzas_sets[el])
    best_points = len(set1)**2 + len(set2)**2
    best_team1 = result[i]
    best_team2 = result[j]
    improved = 0
    for k in range(len(result[i])):
        for l in range(len(result[j])):
            # Invert
            result[i][k], result[j][l] = result[j][l], result[i][k]
            set1 = set()
            set2 = set()
            for el in result[i]:
                set1 = set1.union(pizzas_sets[el])
            for el in result[j]:
                set2 = set2.union(pizzas_sets[el])
            points = len(set1)**2 + len(set2)**2
            if points > best_points:
                # eprint("improved")
                best_points = points
                best_team1 = result[i].copy()
                best_team2 = result[j].copy()
                improved = 1 
            # Re-invert back
            result[i][k], result[j][l] = result[j][l], result[i][k]
    result[i] = best_team1
    result[j] = best_team2
    return improved
            

def compute_points(totalRes, pizzas_sets):
    points = 0
    for pizzas in totalRes:
        myset = set()
        for p in pizzas:
            myset = myset.union(pizzas_sets[p])
        points += len(myset)**2
    return points


if __name__=="__main__":
    df, t2, t3, t4, pizzas_sets = parse_input()
    # eprint(pizzas_sets)
    numHashes = 50
    maxNumConflicts = 0
    totalRes = []
    indicesRemaining = [i for i in range(len(df))]   # Initially all indices are remaining
    
    while maxNumConflicts < numHashes and (t2 > 0 or t3 > 0 or t4 > 0):
        edoList = parse_input_build_hashes(df, numHashes)
        lledoList = LinkedList()
        for i, hashList in edoList:
            lledoList.append(Node(i, hashList))
        eprint("len of lledolist {}".format(len(lledoList)))
        result, indicesToDrop, t2, t3, t4 = makeAssignments(lledoList, t2, t3, t4, maxNumConflicts)
        df = df.drop(indicesToDrop)
        totalRes += result
        maxNumConflicts += 1
    eprint("points before local improvement {}".format(compute_points(totalRes, pizzas_sets)))
    improvements = 0
    for i in tqdm(range(1000000)):
        j, k = np.random.randint(0, len(totalRes)), np.random.randint(0, len(totalRes))
        improvements += changePizzaInTeams(j, k, totalRes, pizzas_sets)
    eprint("points after local improvement {}".format(compute_points(totalRes, pizzas_sets)))
    eprint("Number of improvements {}".format(improvements))
    printRes(totalRes)
    

