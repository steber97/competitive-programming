import math

DEBUG = False
EPS = 0.0000001

def debug(x):
    if DEBUG:
        print(x)

def point_in_polygon(p, polygon, strict):
    for i in range(len(polygon)):
        p1 = polygon[i]
        p2 = polygon[(i+1) % len(polygon)]
        min_p_x = p1 if p1[0] < p2[0] else p2
        max_p_x = p2 if p1[0] < p2[0] else p1
        if p[0] <= max_p_x[0] and p[0] >= min_p_x[0]:
            m = (min_p_x[1] - max_p_x[1]) / (min_p_x[0] - max_p_x[0])
            y_intersect = min_p_x[1] + m * (p[0] - min_p_x[0])

            y_high = abs(y_intersect)
            y_low = -abs(y_intersect)
            
            if strict:
                if (p[1] < y_high) and (abs(p[1] - y_high) > EPS) and \
                    (p[1] > y_low) and (abs(p[1] - y_low) > EPS):
                    return True
                else:
                    return False
            else:
                if (p[1] <= y_high or  (abs(p[1] - y_high) < EPS))  and \
                    (p[1] >= y_low or  abs(p[1] - y_low) < EPS):
                    return True
                else:
                    return False
    # Default case, nothing had happened, hence the point is outside.
    return False

def build_polygon(radius, k):
    points = []
    for i in range(k):
        points.append(
            (math.cos(2*math.pi * i/k) * radius,
            math.sin(2*math.pi * i/k) * radius)
        )
    return points

def find_smaller(k, points):
    """
    Returns the area: once the radius is found,
    it is easy since it is simply a matter of taking k equal triangles
    """
    high = 10e6
    low = 0
    
    finish = False
    while not finish:
        radius = (high + low) / 2
        # This must be a list of consecutive points.
        polygon = build_polygon(radius, k)
        #debug(polygon)
        done = True
        for p in points:
            if point_in_polygon(p, polygon, strict=True):
                done = False
                break
        if done:
            low = radius
        else:
            high = radius
        if abs(high - low) < 10e-8:
            finish = True
    
    area = k * (radius**2) * math.cos(math.pi / k) * math.sin(math.pi / k)
    return area



def find_larger(k, points):
    """
    Returns the area: once the radius is found,
    it is easy since it is simply a matter of taking k equal triangles
    """
    high = 10e6
    low = 0
    
    finish = False
    while not finish:
        radius = (high + low) / 2
        # This must be a list of consecutive points.
        polygon = build_polygon(radius, k)
        #debug(polygon)
        done = True
        for p in points:
            if not point_in_polygon(p, polygon, strict=False):
                done = False
                break
        if done:
            high = radius
        else:
            low = radius
        if abs(high - low) < 10e-8:
            finish = True
    debug(radius)
    area = k * (radius**2) * math.cos(math.pi / k) * math.sin(math.pi / k)
    return area



if __name__ == "__main__":
    n = int(input())
    points = []
    for i in range(n):
        x,y = [int(j) for j in input().split()]
        points.append((x,y))
    
    best = 0
    best_k = 0
    for k in range(3,9):
        area_small = find_smaller(k, points)
        area_large = find_larger(k, points)
        debug(area_small/area_large)
        if (area_small / area_large >= best) or (best_k == 0):
            best = area_small / area_large 
            best_k = k
    print("{} {:.9f}".format(best_k, best))