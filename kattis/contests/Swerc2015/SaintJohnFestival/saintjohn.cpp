// Much of the code is taken from https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
#include <iostream> 
#include <vector>
#include <stack> 
#include <stdlib.h> 
#include <cassert>

using namespace std; 
  
typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)

// Define Infinite (Using INT_MAX caused overflow problems) 
#define INF 1073741830 

#define DEBUG 0


  
struct Point 
{ 
    ll x; 
    ll y; 
    Point(){

    }
    Point(ll x_, ll y_){
        this->x = x_;
        this->y = y_;
    }
}; 

void debugpoint(Point& p){
    if (DEBUG)
        cout << p.x << " " << p.y << endl;
}
void debugstring(string s){
    if(DEBUG)
        cout << s << endl;
}
  
// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    ll val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(vector<Point>* polygon, Point p) 
{ 
    int n = polygon->size();
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, p.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 

    debugstring("intersections: ");
    debugpoint(p);
    do
    { 
        int next = (i+1)%n; 
        int nextnext = (i+2)%n;
        int prev = (i-1)%n;

        if (prev < 0)
            prev += n;
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon->at(i), polygon->at(next), p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon->at(i), p, polygon->at(next)) == 0) 
               return onSegment(polygon->at(i), p, polygon->at(next));   // THIS WORKS ONLY WHEN THE POLYGON IS CONVEX!!
            debugpoint(polygon->at(i));
            debugstring("|");
            debugpoint(polygon->at(next));

            if (p.y == polygon->at(i).y || p.y == polygon->at(next).y){
                if (p.y == polygon->at(i).y){
                    if (((polygon->at(next).y > polygon->at(i).y) and (polygon->at(prev).y < polygon->at(i).y)) or 
                                    ((polygon->at(next).y < polygon->at(i).y) and (polygon->at(prev).y > polygon->at(i).y)) ){
                        count ++;   // it will be counted twice!
                    }
                }
                else{
                    if (((polygon->at(i).y > polygon->at(next).y) and (polygon->at(nextnext).y < polygon->at(next).y)) or 
                                    ((polygon->at(i).y < polygon->at(next).y) and (polygon->at(nextnext).y > polygon->at(next).y))){
                        count ++;   // it will be counted twice!
                    }
                }
                
            }
            else {
                count+=2; 
            }
        } 
        i = next; 
    } while (i != 0); 
    debugstring(to_string(count));
  
    // Return true if count is odd, false otherwise 
    count = count >> 1; // it is always an even number!
    return count & 1;  // Same as (count%2 == 1) 
} 


// THIS INSTEAD IS CONVEX HULL, taken from https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/

// A global point needed for  sorting points with reference 
// to  the first point Used in compare function of qsort() 
Point p0; 
  
// A utility function to find next to top in a stack 
Point nextToTop(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 
  
// A utility function to swap two points 
void swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
// A utility function to return square of distance 
// between p1 and p2 
ll distSq(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
          (p1.y - p2.y)*(p1.y - p2.y); 
} 

  
// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 
  
// Prints convex hull of a set of n points. 
vector<Point>* convexHull(vector<Point>& points)  { 
   // Find the bottommost point 
   int n = points.size();
   ll ymin = points[0].y, min = 0LL; 
   for (int i = 1; i < n; i++) 
   { 
     ll y = points[i].y; 
  
     // Pick the bottom-most or chose the left 
     // most point in case of tie 
     if ((y < ymin) || (ymin == y && 
         points[i].x < points[min].x)) 
        ymin = points[i].y, min = i; 
   } 
  
   // Place the bottom-most point at first position 
   swap(points[0], points[min]); 
  
   // Sort n-1 points with respect to the first point. 
   // A point p1 comes before p2 in sorted output if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 
  
   // If two or more points make same angle with p0, 
   // Remove all but the one that is farthest from p0 
   // Remember that, in above sorting, our criteria was 
   // to keep the farthest point at the end when more than 
   // one points have same angle. 
   int m = 1; // Initialize size of modified array 
   for (int i=1; i<n; i++) 
   { 
       // Keep removing i while angle of i and i+1 is same 
       // with respect to p0 
       while (i < n-1 && orientation(p0, points[i], 
                                    points[i+1]) == 0) 
          i++; 
  
  
       points[m] = points[i]; 
       m++;  // Update size of modified array 
   } 
  
   // Create an empty stack and push first three points 
   // to it. 
   stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 
  
   // Process remaining n-3 points 
   for (int i = 3; i < m; i++) 
   { 
      // Keep removing top while the angle formed by 
      // points next-to-top, top, and points[i] makes 
      // a non-left turn 
      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 
  
   // Now stack has the output points, put them in the result vector.
   vector<Point>* result = new vector<Point>();
   debugstring("Convex Hull");
   while (!S.empty()) 
   { 
       Point p = S.top();
       result->push_back(p);
       debugpoint(p);
       S.pop(); 
   } 
   debugstring("End Convex Hull");
   
   return result;
} 

int main(){

    int L;
    cin >> L;

    vector<Point> large_lanterns(L);
    for (int i = 0; i<L; i++){
        cin >> large_lanterns[i].x >> large_lanterns[i].y;
    }

    vector<Point>* convex_polygon = convexHull(large_lanterns);

    int S;
    cin >> S;
    int result = 0;
    for (int i = 0; i<S; i++){
        ll x,y;
        cin >> x >> y;
        Point p(x,y);
        if (isInside(convex_polygon, p)){
            debugpoint(p);
            result ++;
        }
    }

    cout << result << endl;

    return 0;
}