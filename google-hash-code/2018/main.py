import pandas as pd
import numpy as np
from ortools.linear_solver import pywraplp
from pprint import pprint
from tqdm import tqdm
import time


def manhattan(p1, p2):
    return abs(p1[0]-p2[0]) + abs(p1[1]-p2[1])


class Ride:
    def __init__(self, sr, sc, er, ec, start, finish,index):
        self.sr = sr
        self.sc=sc
        self.er=er
        self.ec=ec
        self.start=start
        self.finish=finish
        self.index=index
        self.served=False
    def __repr__(self):
        return ("ride {}: ({},{})->({},{}), time ({})->({})".format(
            self.index, self.sr, self.sc, self.er, self.ec, self.start, self.finish
        ))
    def distance(self):
        return manhattan((self.sr, self.sc), (self.er, self.ec))
        
class Vehicle:
    def __init__(self, r,c,index):
        self.r=r
        self.c=c
        self.index=index
        self.time_free=0

    def time_before_ride(self, r: Ride):
        return max(
            self.time_free + manhattan((self.r, self.c), (r.sr, r.sc)),
            r.start
        )

    

def read_input(filename):
    rides = []
    rides_df = []
    vehicles = []
    with open(filename, 'r') as f:
        for i, l in enumerate(f):
            if i == 0:
                R, C, F, N, B, T = [int(x) for x in l.split(" ")]
                for j in range(F):
                    vehicles.append(Vehicle(0,0,j))
            else:
                sr, sc, er, ec, start, finish = [int(x) for x in l.split(" ")]
                rides.append(Ride(sr,sc,er,ec,start,finish,i-1))
                rides_df.append({"start_row": sr, "start_col": sc, "end_row": er, "end_col": ec, "start":start,"finish":finish})
    return rides, vehicles, R,C,F,N,B,T, pd.DataFrame(rides_df)

def time_to_finish_ride(vehicle:Vehicle, ride:Ride):
    start_time = max(
        vehicle.time_free + manhattan((ride.sr, ride.sc), (vehicle.r, vehicle.c)),
        ride.start
    )
    
    start_time += manhattan((ride.sr, ride.sc), (ride.er, ride.ec))
    return start_time

def points_per_ride_and_vehicle(ride: Ride, vehicle: Vehicle, B:int) -> int:
    result = 0
    start_time = max(
        vehicle.time_free + manhattan((ride.sr, ride.sc), (vehicle.r, vehicle.c)),
        ride.start
    )
    if start_time <= ride.start:
        result += B
    if start_time + manhattan((ride.sr, ride.sc), (ride.er, ride.ec)) <= ride.finish:
        result += manhattan((ride.sr, ride.sc), (ride.er, ride.ec))
    return result


def solve(rides, vehicles, R, C, F, N, B, T):
    assignments = [[] for i in range(len(vehicles))]
    current_time = 0
    RIDES_PER_ITER = len(vehicles)
    assignment_set = set()

    tot_objective = 0
    limit_rides_to_take = 1000

    neigh_per_ride = {}
    for r in tqdm(rides):
        neigh_per_ride[r.index] = sorted([r2 for r2 in rides if r2.index != r.index], key=lambda x:
            manhattan((r.er, r.ec), (x.sr, x.sc))
            )[:100]

    while current_time < T and np.sum([not x.served for x in rides]) > 0:
        start = time.time_ns()
        prev_assigned = len(assignment_set)
        j = 0
        rides_to_serve = []
        first_ride = True
        max_time = -1
        if np.sum([not x.served for x in rides[first_ride:]]) == 0:
            break

        rides_to_serve = [r for r in rides if not r.served]
        rides_per_vehicle = {}
        ride_map_to_variable = {}
        rides_set = set()
        for r in rides_to_serve:
            ride_map_to_variable[r.index] = []
        for v in vehicles:
            v: Vehicle
            neighbors = sorted([r for r in rides_to_serve if time_to_finish_ride(v, r) <= r.finish], key=lambda x: v.time_before_ride(x))
            rides_per_vehicle[v.index] = neighbors[:50] if len(neighbors) > 0 else []
            for r in rides_per_vehicle[v.index]:
                rides_set.add(r)
            for j, r in enumerate(rides_per_vehicle[v.index]):
                ride_map_to_variable[r.index].append((v.index, j))
        # print(len(rides_set))
        if len(rides_to_serve) > 0:
            # print("Rides to serve:", len(rides_to_serve), "interval:", rides_to_serve[0].start, np.max([x.finish for x in rides_to_serve]))
            
            solver = pywraplp.Solver.CreateSolver('SCIP')
            variables = {}
            for v in vehicles:
                variables[v.index] = [solver.BoolVar("{}-{}".format(v.index, r.index)) for r in rides_per_vehicle[v.index]]
               
            # Objective:
            coefficients_objective = []
            for i in range(len(vehicles)):
                coefficients_objective.append([])
                for j in range(len(rides_per_vehicle[i])):
                    coefficients_objective[i].append(0)
            
            for i, v in enumerate(vehicles):
                for j, r in enumerate(rides_per_vehicle[v.index]):
                    points = points_per_ride_and_vehicle(r, v, B)
                    time_to_finish = time_to_finish_ride(v, r)
                    earliest_time = r.distance() + r.start
                    if time_to_finish > r.finish:
                        coefficients_objective[i][j] = -1
                    else:
                        future_waste = [max(
                                manhattan((r.er, r.ec), (r2.sr, r2.sc)) + time_to_finish_ride(v, r),
                                r2.start) - time_to_finish_ride(v, r) for r2 in neigh_per_ride[r.index] if not r2.served]
                        future_waste = 0 if len(future_waste) ==0 else np.min(future_waste)
                        coefficients_objective[i][j] = T + 1 - (v.time_before_ride(r) - v.time_free) * 0.1 - (
                            future_waste) * 0.01
            objective = solver.Objective()
            for i, v in enumerate(vehicles):
                for j, r in enumerate(rides_per_vehicle[v.index]):
                    objective.SetCoefficient(variables[i][j],  coefficients_objective[i][j])
            objective.SetMaximization()

            #Constraints:

            for j in range(len(rides_to_serve)):
                if len(ride_map_to_variable[rides_to_serve[j].index]) > 0:
                    constraint_expr = [variables[i][l] for (i,l) in ride_map_to_variable[rides_to_serve[j].index]]
                    solver.Add(sum(constraint_expr) <= 1)

            for i, v in enumerate(vehicles):
                constraint_expr = [variables[i][j] * 1 for j in range(len(rides_per_vehicle[i]))]
                solver.Add(sum(constraint_expr) <= 1)

            start_solver = time.time_ns()
            status = solver.Solve()
            end_solver = time.time_ns()
            if status == pywraplp.Solver.OPTIMAL:
                # tot_objective += solver.Objective().Value()
                current_time_tmp = T
                for i, v in enumerate(vehicles):
                    for j, r in enumerate(rides_per_vehicle[v.index]):  
                        if (variables[i][j].solution_value() > 0):
                            assert points_per_ride_and_vehicle(r, vehicles[i], B) > 0
                            tot_objective += points_per_ride_and_vehicle(r, vehicles[i], B)
                            vehicles[i].time_free = time_to_finish_ride(vehicles[i], r)
                            vehicles[i].c = r.ec
                            vehicles[i].r = r.er
                            r.served = True
                            assignments[i].append(r.index)
                    current_time_tmp = min(current_time_tmp, vehicles[i].time_free)
            else:
                print("something went wrong")
    
        assignment_set = set()
        for a in assignments:
            for act in a:
                assert act not in assignment_set
                assignment_set.add(act)
        end = time.time_ns()
        print("activities served", len(assignment_set), "current time", current_time, "tot_obj", 
              tot_objective, "exec time", end-start, "solver: ", end_solver-start_solver)
        if len(assignment_set) == prev_assigned:
            break
    print("Total objective: ", tot_objective)
    return assignments


if __name__=="__main__":
    test_case = 3
    files_in = ['input/a_example.in', 'input/b_should_be_easy.in', 'input/c_no_hurry.in', 'input/d_metropolis.in', 'input/e_high_bonus.in']
    files_out = ['output/output_a', 'output/output_b', 'output/output_c', 'output/output_d', 'output/output_e']
    rides, vehicles, R,C,F,N,B,T, rides_df = read_input(files_in[test_case])
    print(np.sum([x.distance() for x in rides]))
    rides = sorted(rides, key=lambda x: (x.start, x.finish))

    assignments = solve(rides, vehicles, R, C, F, N, B, T)

    with open(files_out[test_case], 'w') as f:
        for a in assignments:
            print('{} {}'.format(len(a), " ".join([str(x) for x in a])), file=f)