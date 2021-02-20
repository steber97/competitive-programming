from math import sin, cos, pi, acos, sqrt, asin, atan2


DEBUG = False


radius = 6370   # in km


def debug(name, x):
    if DEBUG:
        print("{}: {}".format(name, x))

class Vertex:
    def __init__(self, latitude, longitude):
        self.latitude = float(latitude)
        self.longitude = float(longitude)
    def __str__(self):
        return str(self.latitude) + " " + str(self.longitude)

class Continent:
    def __init__(self):
        # Be careful, there is even the edge from the last vertex to the first one. Every continent is a closed polygon.
        self.vertices = []
    def __str__(self):
        res= ""
        for el in self.vertices:
            res += str(el) + "\n"
        return res

    
class Path:
    def __init__(self):
        self.vertices = []
    def __str__(self):
        res = ""
        for el in self.vertices:
            res += "{} {},".format(el.latitude, el.longitude)
        return res

def cross(v1, v2):
    return [
        v1[1]*v2[2] - v1[2]*v2[1],
        v1[2]*v2[0] - v1[0]*v2[2],
        v1[0]*v2[1] - v1[1]*v2[0]
    ]

def dot(a,b):
    res = 0
    for i in range(len(a)):
        res += a[i]*b[i]
    return res

def convert_to_radians(angle):
    return 2.0 * pi * angle / 360.0


def samesing(s1,s2,s3,s4):
    if s1 <= 0 and s2 <= 0 and s3 <= 0 and s4 <= 0:
        return True
    if s1 >= 0 and s2 >= 0 and s3 >= 0 and s4 >= 0:
        return True
    return False

def magnitude(v):
    res = 0
    for el in v:
        res += el ** 2
    return  sqrt(res)

def compare(i1):

    angle = sin(i1[0].latitude) * sin(i1[1].latitude) +\
                                        cos(i1[0].latitude) * cos(i1[1].latitude) * cos(abs(i1[0].longitude - i1[1].longitude))
    
    # Normalize, as acos needs values in -1 <= x <= 1, and sometimes 1 is 1.0000000000000000001 whish is invalid
    angle = angle if angle <= 1 else 1
 
    angle = angle if angle >= -1 else -1
    
    degree_included_vertex1 = acos(angle)
    dist1 = radius* degree_included_vertex1
    
    return dist1

def compute_len(v1, v2):
    lon1 = v1.longitude - pi
    lat1 = v1.latitude

    lon2 = v2.longitude - pi
    lat2 = v2.latitude

    degree_included_vertex1 = acos(sin(lat1) * sin(lat2) +
                                        cos(lat1) * cos(lat2) * cos(abs(lon1 - lon2)))  
    dist = radius* degree_included_vertex1
    
    return dist
    
def compute_intersections(v1, v2, v3, v4):
    # Compute the points of intersection among 2 lines (v1-v2 and v3-v4)

    glat1 = float(v1.latitude)
    glon1 = float(v1.longitude) - pi
    glat2 = float(v2.latitude)
    glon2 = float(v2.longitude) - pi

    cglat1 = float(v3.latitude)
    cglon1 = float(v3.longitude) - pi
    cglat2 = float(v4.latitude)
    cglon2 = float(v4.longitude) - pi

    x1 = cos(glat1) * cos(glon1)
    y1 = cos(glat1) * sin(glon1)
    z1 = sin(glat1)

    x2 = cos(glat2) * cos(glon2)
    y2 = cos(glat2) * sin(glon2)
    z2 = sin(glat2)


    cx1 = cos(cglat1) * cos(cglon1)
    cy1 = cos(cglat1) * sin(cglon1)
    cz1 = sin(cglat1)

    cx2 = cos(cglat2) * cos(cglon2)
    cy2 = cos(cglat2) * sin(cglon2)
    cz2 = sin(cglat2)


    # 2. Get normal to planes containing great circles.
    #    It's the cross product of vector to each point from the origin.

    N1 = cross([x1, y1, z1], [x2, y2, z2])
    N2 = cross([cx1, cy1, cz1], [cx2, cy2, cz2])


    # 3. Find line of intersection between two planes.
    #    It is normal to the poles of each plane.

    L = cross(N1, N2) 
    L_normalized = [x / magnitude(L) for x in L]   

    s1 = dot(cross([x1,y1,z1], [N1[0], N1[1], N1[2]]), L_normalized)
    s2 = dot(cross([x2,y2,z2], [N1[0], N1[1], N1[2]]), L_normalized)
    s3 = dot(cross([cx1,cy1,cz1], [N2[0], N2[1], N2[2]]), L_normalized)
    s4 = dot(cross([cx2,cy2,cz2], [N2[0], N2[1], N2[2]]), L_normalized)

    if samesing(-s1,s2,-s3,s4):
        # 4. Find intersection points.
        if -s1<0:
            # negative
            x = -L_normalized[0]
            y = -L_normalized[1]
            z = -L_normalized[2]
        else:
            # positive
            x = L_normalized[0]
            y = L_normalized[1]
            z = L_normalized[2]
        ilat = atan2(z, sqrt(x**2 + y**2))
        ilon = atan2(y, x)
        # debug("intersection", str(ilat) + " " + str(ilon))
        return ilat, ilon + pi
    else:
        return None, None


continents_number = int(input())

continents = [Continent() for i in range(0, continents_number)]

for i, continent in enumerate(continents):
    line = input()
    number_of_vertices = int(line.split(' ')[0])
    for j in range(1, number_of_vertices*2, 2):
        latitude = convert_to_radians(int(line.split(" ")[j]))
        longitude = convert_to_radians(int(line.split(" ")[j+1]))
        continents[i].vertices.append(Vertex(latitude, longitude))
    
    continent.vertices.append(continent.vertices[0])  # Add the last segment
    debug("continent", continent)

line = input()
len_of_path = int(line.split(" ")[0])
debug("len of path", len_of_path)
path = Path()

for i in range (1, len_of_path* 2, 2):
    latitude = convert_to_radians(int(line.split(" ")[i]))
    longitude = convert_to_radians(int(line.split(" ")[i+1]))
    debug("latitude, longitude", (latitude, longitude))
    path.vertices.append(Vertex(latitude, longitude))

debug("path", path)
total_len_of_path = 0.0
for i in range(0, len(path.vertices[:-1])):
    # Only until the penultimate vertex.
    degree_included_vertex = acos(sin(path.vertices[i].latitude) * sin(path.vertices[i+1].latitude) +
                                        cos(path.vertices[i].latitude) * cos(path.vertices[i+1].latitude) * cos(abs(path.vertices[i].longitude - path.vertices[i+1].longitude)))
                                        
    total_len_of_path += radius* degree_included_vertex

# Now compute the intersections:

on_earth = True
len_on_earth = 0
len_on_water = 0
for k in range(0, len(path.vertices)-1):
    intersections = [[path.vertices[k], path.vertices[k]], [path.vertices[k+1], path.vertices[k]]]
    for c in continents:
        for j,v in enumerate(c.vertices):
            if j < len(c.vertices)-1:
                lat,lon = compute_intersections(c.vertices[j], c.vertices[j+1], path.vertices[k], path.vertices[k+1])
                debug("lat-lon", str(lat) +  " " + str(lon))
                if lat is not None and lon is not None:
                    debug("found intersection", str(lat)+" "+str(lon))
                    intersections.append([Vertex(lat,lon), path.vertices[k] ])
    
    intersections = sorted(intersections, key=compare)

    debug("path", path.vertices[k])
    for i in range(len(intersections)):
        debug("intersection at", str(intersections[i][0]))

    for i in range(len(intersections)-1):
        if on_earth:
            len_on_earth += compute_len(intersections[i][0], intersections[i+1][0])
        else:
            len_on_water += compute_len(intersections[i][0], intersections[i+1][0])
        if i != len(intersections)-2:
            on_earth = not on_earth   # Toggle status of on_earth


debug("total", total_len_of_path)
debug("earth", len_on_earth)
debug("water", len_on_water)
debug("sum", len_on_earth + len_on_water)

print("{} {}".format(total_len_of_path, len_on_water/total_len_of_path * 100))