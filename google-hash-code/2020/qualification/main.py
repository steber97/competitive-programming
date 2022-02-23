from audioop import reverse
import numpy as np
import pandas as pd
from typing import List, Set, Dict, Tuple, Optional

class Book:
    def __init__(self, score, id):
        self.score = score
        self.id = id


class Library:
    def __init__(self, books_n, signup, ship, books, id):
        self.books_n = books_n
        self.signup = signup
        self.ship = ship
        self.books = books
        self.id = id
    
    def get_most_convenient_books(self, books_remaining, day, D):
        books_intersection = list(set(self.books).intersection(books_remaining))
        sorted(books_intersection, key=lambda x: x.score, reverse=True)
        # Cap only books that can actually be shipped
        return books_intersection[:(D - day) * self.ship]  

class Solution:
    def __init__(self):
        self.libraries_sorted = []
        self.books_per_library = []
    
    def __str__(self):
        res = ""
        res += "{}\n".format((len(self.libraries_sorted)))
        for l, books_per_library in zip(self.libraries_sorted, self.books_per_library):
            res += "{} {}\n".format(l.id, len(books_per_library))
            for b in books_per_library:
                res += "{} ".format(b.id)
            res += "\n"
        return res


        

def get_input():
    bld = input()
    B, L, D = bld.split(" ")
    B, L, D = int(B), int(L), int(D)
    scores = input().split(" ")
    scores = [int(s) for s in scores]
    books = {}
    for i, s in enumerate(scores):
        books[i] = Book(s, i)
    
    libraries = []
    for l in range(L):
        books_n, signup, ship = input().split(" ")
        books_n, signup, ship = int(books_n), int(signup), int(ship)
        books_in_library = input().split(" ")
        libraries.append(Library(books, signup, ship, [books[int(b)] for b in books_in_library], l))
    
    return books, libraries, D


def evaluate_solution(solution: Solution, books: List[Book], libraries: List[Library]):
    day = 0
    points = 0
    for lib, books in zip(solution.libraries_sorted, solution.books_per_library):
        books_set = set(b.id for b in books)
        day += lib.signup
        for b in books:
            b: Book
            lib: Library
            assert b.id in books_set
        points += np.array([b.score for b in books[: (D - day) * lib.ship]]).sum()
    return points


if __name__ == "__main__":
    books, libraries, D = get_input()
    libraries_sorted = sorted(libraries, key=lambda x: x.signup) # TODO: need to change this!
    
    solution = Solution()
    books_remaining = set(books)
    day = 0
    for l in libraries_sorted:
        l: Library
        day += l.signup
        books_convenient = l.get_most_convenient_books(set([books[b] for b in books_remaining]), day, D)
        solution.libraries_sorted.append(l)
        solution.books_per_library.append(books_convenient)
        books_remaining = books_remaining.difference(set([b.id for b in books_convenient]))

    # print(solution)
    points = evaluate_solution(solution, books, libraries)
    print(points)
