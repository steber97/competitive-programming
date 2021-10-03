#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001
#define EPS 0.000001

class UnionFind {
    // OOP style
    private :
        vi p , rank , setSize ;
        // remember : vi is vector < int >
        int numSets ;
    public:
        UnionFind ( int N ) {
        setSize.assign (N , 1) ; 
        numSets = N ; 
        rank.assign (N , 0) ;
        p.assign (N , 0) ; for ( int i = 0; i < N ; i ++) p [ i ] = i ; }
        int findSet ( int i ) { return ( p [ i ] == i ) ? i : ( p [ i ] = findSet ( p [ i ]) ) ; }
        bool isSameSet ( int i , int j ) { return findSet ( i ) == findSet ( j ) ; }
        void unionSet ( int i , int j ) {
            if (! isSameSet (i , j ) ) {
                numSets --;
                int x = findSet ( i ) , y = findSet ( j ) ;
                // rank is used to keep the tree short
                if ( rank [ x ] > rank [ y ]) { 
                    p [ y ] = x ;
                    setSize [ x ] += setSize [ y ];
                }
                else
                {
                    p [ x ] = y ;
                    setSize [ y ] += setSize [ x ];
                    if ( rank [ x ] == rank [ y ]) 
                        rank [ y ]++; 
                } 
            }
        }
        int numDisjointSets () { return numSets ; }
        int sizeOfSet ( int i ) { return setSize [ findSet ( i ) ]; }
};

double distance(pair<double, double> p1, pair<double, double> p2){
	return sqrt(abs(p1.first - p2.first) * abs(p1.first - p2.first) + abs(p1.second - p2.second) * abs(p1.second - p2.second));
}

int main(){
    int X, Y;
    cin >> X >> Y;
    int n;
    cin >> n;
    vector<pair<double, double>> pts(n);
    FOR(i,0,n)
        cin >> pts[i].first >> pts[i].second;
    
    double prev_rad = 0.0;
	double min_rad = 0.0;
	double max_rad = max(double(Y), double(X));
    double rad = (min_rad + max_rad) / 2.0;

	while(abs(prev_rad - rad) > EPS){
		VALUE(rad);
		UnionFind uf(n);
		vector<vector<bool>> touch(n, vector<bool>(4));
		FOR(i,0,n){
			if ((pts[i].first < rad) && abs(pts[i].first - rad) > EPS){
				touch[i][0] = true;
			}
			else {
				touch[i][0] = false;
			}
			if ((pts[i].first + rad > ((double)X)) && abs(pts[i].first + rad - (double(X)) ) > EPS){
				touch[i][2] = true;
			}
			else {
				touch[i][2] = false;
			}
			if ((pts[i].second < rad) && abs(pts[i].second - rad) > EPS){
				touch[i][3] = true;
			}
			else {
				touch[i][3] = false;
			}
			if ((pts[i].second + rad > ((double)Y)) && abs(pts[i].second + rad - (double(Y)) ) > EPS){
				touch[i][1] = true;
			}
			else {
				touch[i][1] = false;
			}
		}
		FOR(i, 0, n){
			FOR(j, 0, n){
				if (i != j){
					if (distance(pts[i], pts[j]) < (rad * (double (2))) && 
						abs(distance(pts[i], pts[j]) - (rad * (double (2.0)))) > EPS){
						vector<bool> touch1 = touch[uf.findSet(i)], touch2 = touch[uf.findSet(j)];
						uf.unionSet(i, j);
						FOR(l,0,4)
							touch[uf.findSet(i)][l] = touch1[l] || touch2[l];
					}
				}
			}
		}

		bool feasible = true;
		FOR(i,0,n){
			if (!feasible)
				break;
			if (touch[uf.findSet(i)][0] && touch[uf.findSet(i)][3])
				feasible = false;
			if (touch[uf.findSet(i)][0] && touch[uf.findSet(i)][2])
				feasible = false;
			if (touch[uf.findSet(i)][1] && touch[uf.findSet(i)][2])
				feasible = false;
			if (touch[uf.findSet(i)][1] && touch[uf.findSet(i)][3])
				feasible = false;
		}
		VALUE(feasible);
		prev_rad = rad;
		if (feasible)
			min_rad = rad;
		else
			max_rad = rad;
		rad = (min_rad + max_rad) / 2.0;
		
    }

	cout << setprecision(10) << fixed << rad << endl;
	return 0;
}