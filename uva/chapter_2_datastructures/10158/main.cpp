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

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};


int main(){
    int n;
    cin >> n;
    UnionFind uf(n+1);
    unordered_set<ii, pair_hash> enemies, enem2;

    while(true){
        int a,b,c;
        cin >> a >> b >> c;
        if (a==0)
            break;
        
        if (a==1){
            // make friends
            bool are_enemies = ((enemies.find({uf.findSet(c), uf.findSet(b)}) != enemies.end()) || 
                                (enemies.find({uf.findSet(b), uf.findSet(c)}) != enemies.end()));
            
            if (are_enemies){
                cout << -1 << endl;
            }
            else{
                // Merge enemies;
                     
                int prev1 = uf.findSet(b), prev2 = uf.findSet(c);
                uf.unionSet(b, c);
                for (ii p: enemies){
                    if (uf.findSet(p.first) == prev1 || uf.findSet(p.first) == prev2){
                        enemies.insert({uf.findSet(b), uf.findSet(p.second)});
                    }
                    if (uf.findSet(p.second) == prev1 || uf.findSet(p.second) == prev2){
                        enemies.insert({uf.findSet(p.first), uf.findSet(b)});
                    }
                }
                
                vector<int> friends;
                for(ii p: enemies){
                    if (uf.findSet(p.first) == uf.findSet(prev1) || uf.findSet(p.first) == uf.findSet(prev2))
                        friends.push_back(p.second);
                    else if (uf.findSet(p.second) == uf.findSet(prev1) || uf.findSet(p.second) == uf.findSet(prev2))
                        friends.push_back(p.first);
                }
                for (int i = 1; i<friends.size(); i++){
                    uf.unionSet(friends[0], friends[i]);
                }
            }
        }
        if (a==2){
            // make enemies
            if (uf.findSet(b) == uf.findSet(c)){
                cout << -1 << endl;
            }
            else{
                enemies.insert({uf.findSet(b), uf.findSet(c)});

                vector<int> merge;
                for(ii e: enemies){
                    if (uf.findSet(e.first) == uf.findSet(b))
                        merge.push_back(e.second);
                    else if (uf.findSet(e.second) == uf.findSet(b))
                        merge.push_back(e.first);
                }
                FOR(i,1,merge.size()){
                    uf.unionSet(merge[0], merge[i]);
                }
                merge.clear();

                for(ii e: enemies){
                    if (uf.findSet(e.first) == uf.findSet(c))
                        merge.push_back(e.second);
                    else if (uf.findSet(e.second) == uf.findSet(c))
                        merge.push_back(e.first);
                }
                
                FOR(i,1,merge.size()){
                    uf.unionSet(merge[0], merge[i]);
                }
            }
        }
        if (a==3){
            // are they friends?
            if (uf.findSet(b) == uf.findSet(c)){
                cout << 1 << endl;
            }
            else {
                cout << 0 << endl;
            }
        }
        if (a==4){
            // are they enemies?
            if(enemies.find({uf.findSet(b), uf.findSet(c)}) != enemies.end() || 
               enemies.find({uf.findSet(c), uf.findSet(b)}) != enemies.end()) {
                cout << 1 << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
        enem2.clear();
        for(ii p: enemies){
            enem2.insert({uf.findSet(p.first), uf.findSet(p.second)});
        }
        enemies.clear();
        enemies = enem2;
        FOR(i,0,n+1){
            COUT(uf.findSet(i)); COUT(" ");
        }
        COUT(endl);
        for(ii p: enemies){
            COUT("{"); COUT(p.first); COUT(" "); COUT(p.second); COUT("}");
        }
        COUT(endl);

    }
    return 0;    
}