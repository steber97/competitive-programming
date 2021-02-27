import sys
import numpy as np

from typing import Dict, Tuple


from typing import List

def cross_schedule(streets_points: Dict[str, int], cross: List[str]) -> Dict[str, int]:
    
    schedule = {}
    min_points = float("inf")
    max_points = 0

    for street in cross:
        street_points = streets_points[street]
        if street_points == 0:
            continue
        
        min_points = min(min_points, street_points)
        schedule[street] = street_points

    if schedule:
        max_points = max(schedule.values())

    for street in schedule:
        schedule[street] //= min_points
        schedule[street] = min(schedule[street], 2)

    schedule = {k: v for k, v in sorted(schedule.items(), key=lambda item: -item[1])}
    return schedule, max_points

def get_all_schedules(streets_points: Dict[str, int], crosses: List[List[str]]) -> Tuple[List[Dict[str, int]], int]:
    
    schedules = []
    nonempty_schedules = 0
    max_max_points = 0

    for cross in crosses:
        schedule, max_points = cross_schedule(streets_points, cross)
        max_max_points = max(max_max_points, max_points)
        if schedule:
            nonempty_schedules += 1
        
        schedules.append(schedule)

    eprint(max_max_points)

    return schedules, nonempty_schedules

def write_output(schedules: List[Dict[str, int]], nonempty_schedules: int) -> None:
    print(nonempty_schedules)

    for i, schedule in enumerate(schedules):
        if not schedule:
            continue

        print(i)
        print(len(schedule))
        for street, seconds in schedule.items():
            print(f"{street} {seconds}")

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs) 

def points_per_street(): #-> Dict[str, int]:
    return points_per_strt

def streets_per_crosses(): #-> List[List[str]]:
    """Streets that enter each cross"""
    return street_incoming

intersections = []
streets = []
street_incoming = []
cars = []
street_len = {}
car_points = []
points_per_strt = {}

(D, I, S, V, F) = (0, 0, 0, 0, 0)

with sys.stdin as f:
    for i, l in enumerate(f):
        if i == 0:
            D, I, S, V, F = [int(x) for x in l.split()]
            street_incoming = [[] for j in range(I)]
        elif i <= S:
            # order: start point, end point, name, weight
            streets.append((int(l.split()[0]), int(l.split()[1]), l.split()[2], int(l.split()[3])))
            street_len[l.split()[2]] = int(l.split()[3])

            street_incoming[int(l.split()[1])].append(l.split()[2])

            points_per_strt[l.split()[2]] = 0
        else:
            cars.append(l.split()[1:])

            if D - np.array([street_len[x] for x in l.split()[1:]]).sum() > 0:
                car_points.append(F + D - np.array([street_len[x] for x in l.split()[1:]]).sum())
            else:
                 car_points.append(0)
            
            for e in cars[-1]:
                points_per_strt[e] += car_points[-1]

    """
    eprint("duration {}".format(D))
    eprint("intersections {}".format(I))
    eprint("streets {}".format(S))
    eprint("cars {}".format(V))
    eprint("f {}".format(F))
    eprint('-----')
    eprint('car popints', car_points)
    eprint('street in: ', street_incoming)
    eprint('steet points: ', points_per_strt)
    """

    #--------- 
    streets_points = points_per_street()

    crosses = streets_per_crosses()

    schedules, nonempty_schedules = get_all_schedules(streets_points, crosses)
    write_output(schedules, nonempty_schedules)
