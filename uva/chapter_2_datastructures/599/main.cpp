#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

#define len 65538LL
// #define len 12LL

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


int main(){

    int T;
    cin >> T;
    FOR(t,0,T){
        string s;
        vector<pair<char,char>> edges;
        while(true){
            cin >> s;
            if (s.find('*') != s.npos)
                break;
            char a,b;
            a = s[1];
            b = s[3];
            edges.push_back({a,b});
        }
        unordered_map<char, int> vertices_map;
        vector<char> vertices;
        cin >> s;
        int iter = 0;
        FOR(i,0,s.size()){
            if (s[i] != ',' && s[i] >= 'A' && s[i] <= 'Z'){
                vertices_map[s[i]] = iter;
                vertices.push_back(s[i]);
                iter++;
            }
        }
        UnionFind uf(vertices.size());
        FOR(i,0,edges.size()){
            uf.unionSet(vertices_map[edges[i].first], vertices_map[edges[i].second]);
        }
        unordered_map<int,int> counter;
        for(pair<char,int> p: vertices_map){
            // cout << p.first << " " << uf.findSet(vertices_map[p.first]) << endl;
            if (counter.find(uf.findSet(vertices_map[p.first])) == counter.end()){
                counter[uf.findSet(vertices_map[p.first])] = 0;
            }
            counter[uf.findSet(vertices_map[p.first])]++;
        }
        int acorns=0, trees=0;
        VALUE(counter.size());
        for (pair<int,int> p: counter){
            PAIR(p);    
            if (p.second == 1)
                acorns++;
            else
                trees++;
        }
        cout << "There are " << trees << " tree(s) and " << acorns << " acorn(s)." << endl;
    }
    return 0;
}