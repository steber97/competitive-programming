from typing import List
import dataclasses
import numpy as np
import sys
from sklearn import cluster
from sys import stdin


@dataclasses.dataclass
class Point:
    x: int = 0
    y: int = 0


@dataclasses.dataclass
class House:
    speed: int
    latency: int
    position: Point

@dataclasses.dataclass
class Antenna:
    position: Point
    speed: int
    radius: int


Cluster = List[House]


def get_clusters(houses: List[House], n_antennas: int) -> List[Cluster]:
    houses_coordinates_list = list(map(lambda house: [house.position.x, house.position.y], houses))
    houses_coordinates = np.array(houses_coordinates_list)

    kmeans = cluster.MiniBatchKMeans(n_clusters=n_antennas)
    kmeans.fit(houses_coordinates)

    clusters: List[List[House]] = [[] for i in range(n_antennas)]

    for i, label in enumerate(kmeans.labels_):
        clusters[label].append(houses[i])

    return clusters

def get_antennas() -> List[Antenna]:
    return antennas

antennas = []
houses = []

def pos_antennas(clusters: List[List[House]]):
    antennas = get_antennas()
    clusters = first_assignment(clusters)
    tot_negs = 0
    for i_a, c in enumerate(clusters):
        if len(c) == 0:
            antennas[i_a].position = Point(-1, -1)
            tot_negs+=1
            continue
        max_house_to_test = int(1000000/len(c))
        x_bar = round(np.mean([h.position.x for h in c]))
        y_bar = round(np.mean([h.position.y for h in c]))
        max_score = compute_score(c, Point(x = x_bar, y = y_bar), antennas[i_a])
        antennas[i_a].position = Point(x = x_bar, y = y_bar)
        house_to_test = sorted(c, key = lambda h: h.speed - h.latency, reverse=True)[:max_house_to_test]
        for h in house_to_test:
            new_score = compute_score(c, h.position, antennas[i_a])
            if new_score > max_score:
                max_score = new_score
                antennas[i_a].position = h.position
        if max_score < 0:
            tot_negs+=1
    print("Total number of clusters with negative scores: {}".format(tot_negs), file = sys.stderr)
    return antennas, clusters


def first_assignment(clusters: List[List[House]]):
    scores = []
    for i, c in enumerate(clusters):
        score = 0
        for h in c:
            score += h.speed - h.latency
        scores.append((i, score))
    ids = [y[0] for y in sorted(scores, key=lambda x: x[1], reverse=True)]
    return list(np.array(clusters)[ids])


def compute_score(houses: List[House], pos: Point, antenna: Antenna):
    tot_points = 0
    for h in houses:
        dist = (abs(h.position.x - pos.x) + abs(h.position.y - pos.y))
        if dist <= antenna.radius:
            score_h = h.speed * antenna.speed - h.latency * (abs(h.position.x - pos.x) + abs(h.position.y - pos.y))
        else:
            score_h = 0
        tot_points += score_h
    return tot_points

def compute_tot_score(clusters: List[List[House]], antennas: List[Antenna]):
    tot = 0
    for i, a in enumerate(antennas):
        tot += compute_score(clusters[i], a.position, a)
    return tot

def print_out(antennas: List[Antenna], out: str = "test"):
    count_neg = 0
    for a in antennas:
        if a.position.x == -1:
            count_neg +=1
    with open(out, "w") as f:
        print(len(antennas) - count_neg, file = f)
        for i, a in enumerate(antennas):
            if a.position.x != -1:
                print("{id} {x} {y}".format(id = i, x = int(a.position.x), y = int(a.position.y)), file=f)

#def sls(clusters: List[List[House]], antennas: List[Antenna]):


if __name__ == "__main__":
    file_in = sys.argv[1]
    file_out = file_in.split(".")[0] + ".out"
    w, h = map(int, stdin.readline().strip().split(" "))
    n_buildings, n_antennas, r = map(int, stdin.readline().strip().split(" "))

    print(f"n_buildings = {n_buildings}")
    print(f"n_antennas = {n_antennas}")

    for i in range(n_buildings):
        x, y, l, c = map(int, stdin.readline().strip().split(" "))
        houses.append(House(c, l, Point(x, y)))

    for i in range(n_antennas):
        r, c = map(int, stdin.readline().strip().split(" "))
        antennas.append(Antenna(Point(), c, r))

    clusters = get_clusters(houses, n_antennas)
    assert len(clusters) == n_antennas
    antennas, clusters = pos_antennas(clusters)
    print_out(antennas, file_out)
    print("Estimated total:", compute_tot_score(clusters, antennas))

