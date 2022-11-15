#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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
typedef vector<tuple<int, int, int>> viii;
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
 * @brief Implementation of Kruskal algorithm for finding the min spanning tree.
 * 
 * @param edges list of edges in the format of a tuple: (start, end, cost)
 * @param n: number of vertices in the graph.
 * @return vector<tuple<int, int, int>> list of edges being part of the spanning tree.
 */
vector<tuple<int, int, ll, int>> min_spanning_tree(vector<tuple<int, int, ll, int>>& edges, int n, int taboo = -1) {
    
    vector<tuple<int, int, ll, int>> result;
    UnionFind uf(n);
    FOR(i,0,edges.size()){
        if (i != taboo){
            if (!uf.isSameSet(get<0>(edges[i]), get<1>(edges[i]))){
                result.push_back(edges[i]);
                uf.unionSet(get<0>(edges[i]), get<1>(edges[i]));
            }
        }
    }

    return result;
}

ll dist_squared(pair<ll,ll> p1, pair<ll,ll> p2){
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}


int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int v,e;
        cin >> v >> e;
        vector<tuple<int, int, ll>> edges(e);
        FOR(i,0,e){
            cin >> get<0>(edges[i]) >> get<1>(edges[i]) >> get<2>(edges[i]) ;
            get<0>(edges[i])--; get<1>(edges[i])--;
        }
        sort(edges.begin(), edges.end(), compare);
        vector<tuple<int, int, ll, int>> edgeswithpos(e);
        FOR(i,0,edges.size())
            edgeswithpos[i] = {get<0>(edges[i]), get<1>(edges[i]), get<2>(edges[i]), i};
        
        vector<tuple<int, int, ll, int>> result = min_spanning_tree(edgeswithpos, v, -1);
        ll bestcost = LONG_LONG_MAX;
        cout << "Case #" << t << " : ";
        if (result.size() != (v-1)) {
            cout << "No way"<< endl;
        }
        else{
            FOR(i,0,result.size()){
                vector<tuple<int, int, ll, int>> result2 = min_spanning_tree(edgeswithpos, v, get<3>(result[i]));
                if (result2.size() == (v-1)){
                    ll tot = 0;
                    FOR(j,0,result2.size())
                        tot += get<2>(result2[j]);
                    if (tot < bestcost)
                        bestcost = tot;
                }
            }
            if (bestcost == LONG_LONG_MAX){
                cout << "No second way" << endl;
            }
            else{
                cout << bestcost << endl;
            }
        }

    }
    return 0;
}