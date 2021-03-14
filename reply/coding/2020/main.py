import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from string import ascii_lowercase
from PIL import Image
from pprint import pprint
from tqdm import tqdm
import sys

# Read the input
# office has -1 for #
#            -2 for devs
#            -3 for managers
EMPTY = -1
DEV = -2
MANAGER = -3 
def read_input(filename):
    with open(filename, 'r') as f:
        w, h = [int(x) for x in f.readline().split()]
        office_c = []
        for i in range(h):
            office_c.append(f.readline())
        office = []
        for i in range(len(office_c)):
            office.append([])
            for j in range(len(office_c[i])):
                if office_c[i][j] == '#':
                    office[i].append(-1)
                if office_c[i][j] == '_':
                    office[i].append(-2)
                if office_c[i][j] == 'M':
                    office[i].append(-3)
        d = int(f.readline())
        devs = []
        for i in range(d):
            line = f.readline()
            devs.append({
                "company": line.split()[0],
                "bonus": int(line.split()[1]),
                "skills": set([x for x in line.split()[3:]]),
                "id": i
                })
        pm = int(f.readline())
        managers = []
        for i in range(pm):
            line = f.readline()
            managers.append({
                "company": line.split()[0],
                "bonus": int(line.split()[1]),
                "id": i
                })
        return office, devs, managers


def compute_points(x, manager=False):
    if not manager:
        len_inter = len(x.skills_x.intersection(x.skills_y))
        len_union = len(x.skills_x.union(x.skills_y))
    else:
        len_inter = 0
        len_union = 0
    return len_inter * (len_union - len_inter) + x.bonus_x * x.bonus_y


def computeAssignments(office, merged_df, df, deskType, developer=True):
    """
    This function assignes for every desk in the office, if it is of the correct type:
    in case there is a neighbor with same company and good points to be close with, then this neighbor,
    otherwise a random neighbor.
    """
    for i in tqdm(range(len(office))):
        for j in range(len(office[i])):
            if office[i][j] == deskType:
                best_score = 0
                best_dev = None
                for k in range(-1, 2):
                    for l in range(-1, 2):
                        if (k == 0 or l == 0) and (k!=0 or l!=0):
                            if i+k>=0 and i+k<len(office) and j+l>=0 and j+l<len(office[i]):
                                if office[i+k][j+l] >= 0:
                                    # Careful here: developers are stored from [0, df_devs.size[
                                    # While managers from [df_devs.size, ...[ 
                                    if developer and office[i+k][j+l] < len(df):
                                        id_empl = office[i+k][j+l]
                                    elif not developer and office[i+k][j+l] >= len(df_devs):
                                        id_empl = office[i+k][j+l] - len(df_devs)
                                    else:
                                        continue
                                    # There is an employee
                                    tmp = merged_df[
                                        (merged_df['id_x']==id_empl) | 
                                        (merged_df['id_y']==id_empl)].merge(
                                            df, 
                                            left_on='id_x', 
                                            right_on='id', 
                                            suffixes=('_left', '_right')).merge(
                                        df, left_on='id_y', right_on='id', suffixes=('_0', '_1'))
                                    tmp = tmp[(tmp['x_0']==-1) | (tmp['x_1']==-1)]
                                    if len(tmp) > 0:
                                        tmp = tmp.sort_values('points', ascending=False).iloc[0]
                                        p = tmp['points']
                                        dev = tmp['id_x'] if tmp['id_x'] != id_empl else tmp['id_y']
                                        if p > best_score:
                                            best_score = p
                                            best_dev = dev
                if best_dev != None:
                    # Managers are stored counting from df_devs.size()
                    if developer:
                        office[i][j] = best_dev
                    else:
                        office[i][j] = best_dev + len(df_devs)
                    df.loc[best_dev, 'x'] = j
                    df.loc[best_dev, 'y'] = i
                else:
                    if len(df[df['x'] == -1]) == 0:
                        # All employees have been assigned somewhere! Time to stop.
                        return
                    random_row = df[df['x']==-1].sample(1).iloc[0]
                    if developer:
                        office[i][j] = random_row['id']
                    else:
                        office[i][j] = random_row['id'] + len(df_devs)
                    df.loc[random_row['id'], 'x'] = j
                    df.loc[random_row['id'], 'y'] = i
                #pprint(office)


def print_output(df_devs, df_managers, outfile):
    print(df_devs)
    print(df_managers)
    with open(outfile, 'w') as f:
        for i, l in df_devs.iterrows():
            if l.x == -1:
                print("X", file=f)
            else:
                print("{} {}".format(l.x, l.y), file=f)
        for i, l in df_managers.iterrows():
            if l.x == -1:
                print("X", file=f)
            else:
                print("{} {}".format(l.x, l.y), file=f)


filename = sys.argv[1]
office, devs, managers = read_input(filename)
print("Input read!")
df_devs = pd.DataFrame(devs)

df_devs['x'] = np.array([-1 for i in range(len(df_devs))])
df_devs['y'] = np.array([-1 for i in range(len(df_devs))])
df_managers = pd.DataFrame(managers)

df_managers['x'] = np.array([-1 for i in range(len(df_managers))])
df_managers['y'] = np.array([-1 for i in range(len(df_managers))])

df_devs_merged = df_devs.merge(df_devs, left_on='company', right_on='company')
df_devs_merged = df_devs_merged[df_devs_merged.id_x < df_devs_merged.id_y]
df_devs_merged['points'] = df_devs_merged.apply(lambda x: compute_points(x), axis=1)
df_devs_merged = df_devs_merged.drop(columns=['bonus_x', 'company','x_x', 'y_x', 'bonus_y', "x_y", 'y_y'])
print("Merged devs dataset")

df_managers_merged = df_managers.merge(df_managers, left_on='company', right_on='company')
df_managers_merged = df_managers_merged[df_managers_merged.id_x < df_managers_merged.id_y]
print("Merged managers dataset")


# Compute the assignments in a greedy manner
computeAssignments(office, df_devs_merged, df_devs, DEV)

if len(df_managers_merged) > 0:
    df_managers_merged['points'] = df_managers_merged.apply(lambda x: compute_points(x, True), axis=1)
    computeAssignments(office, df_managers_merged, df_managers, MANAGER)

print_output(df_devs, df_managers, "{}.out".format(filename.split('.')[0]))