#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << " "; cout << endl
#define MAT(x) for (int u = 0; u < x.size(); u++) { for (int o = 0; o<x[u].size(); o++) cout << x[u][o] << " "; cout << endl;} cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define MAT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

bool compare(tuple<int, int, int> t1, tuple<int, int, int> t2){
    return get<2>(t1) < get<2>(t2);
}

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


/**
 * Opposite of min-spanning-tree: namely, return all edges that are not part
 * of the min spanning tree.
 */
vector<tuple<int, int, int>> opposite_spanning_tree(vector<tuple<int, int, int>>& edges, int n) {
    sort(edges.begin(), edges.end(), compare);
    vector<tuple<int, int, int>> result;
    UnionFind uf(n);
    FOR(i,0,edges.size()){
        if (!uf.isSameSet(get<0>(edges[i]), get<1>(edges[i]))){
            uf.unionSet(get<0>(edges[i]), get<1>(edges[i]));
        }
        else{
            // Append the edge only if it makes a cycle.
            // Namely, when it is not an edge that makes the spanning tree.
            result.push_back(edges[i]);
        }
    }

    return result;
}

int main(){
    int n,m;
    int t = 0;
    cin >> n >> m;
    while (n!=0) {
        vector<tuple<int, int, int>> edges;
        int totlen = 0;
        FOR(i,0,m) {
            int a,b,c;
            cin >> a >> b >> c;
            edges.push_back({a,b,c});
        }

        int span_tree_size = 0;
        vector<tuple<int, int, int>> result = opposite_spanning_tree(edges, n);
        FOR(i,0,result.size()){
            cout << get<2>(result[i]) << ((i != result.size()-1) ? " " : "");
        }
        if (result.size() == 0)
            cout << "forest";
        cout << endl;
        cin >> n >> m;
        t++;
    }
    return 0;
}