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
vector<tuple<int, int, int>> min_spanning_tree(vector<tuple<int, int, int>>& edges, int n) {
    sort(edges.begin(), edges.end(), compare);
    vector<tuple<int, int, int>> result;
    UnionFind uf(n);
    FOR(i,0,edges.size()){
        if (!uf.isSameSet(get<0>(edges[i]), get<1>(edges[i]))){
            result.push_back(edges[i]);
            uf.unionSet(get<0>(edges[i]), get<1>(edges[i]));
        }
    }

    return result;
}

int dfs(int start, int end, int parent, vvii& graph, vvi& dp) {
    // COUT(start); COUT(" "); COUT(end); COUT(endl);
    if (start == end)
        return 0;
    if (dp[start][end] != -1)
        return dp[start][end];
    int value = -1;
    FOR(i,0,graph[start].size()){
        if (graph[start][i].first != parent){
            if (graph[start][i].first == end){
                value = graph[start][i].second;
                break;
            }
            int v2 = dfs(graph[start][i].first, end, start, graph, dp);
            if (v2 != -1){
                value = max(v2, graph[start][i].second);
            }
        }
    }
    dp[start][end] = value;
    return value;
}


int main(){
    int c, s, q;
    cin >> c >> s >> q;
    int t = 1;
    while(c!=0){
        if (t!=1)
            cout << endl;
        viii edges;
        FOR(i,0,s){
            int a,b,c;
            cin >> a >> b >> c;
            a--; b--;
            edges.push_back({a, b, c});
        }
        viii edges_sp_tree = min_spanning_tree(edges, c);
        vvii graph(c,vii());
        FOR(i,0,edges_sp_tree.size()){
            graph[get<0>(edges_sp_tree[i])].push_back({get<1>(edges_sp_tree[i]), get<2>(edges_sp_tree[i])});
            graph[get<1>(edges_sp_tree[i])].push_back({get<0>(edges_sp_tree[i]), get<2>(edges_sp_tree[i])});
        }

        cout << "Case #" << t << endl;
        vvi dp(c, vi(c, -1));
        FOR(i,0,q){
            int a,b;
            cin >> a >> b;
            a--; b--;
            if (dp[a][b] == -1){
                dp[a][b] = dfs(a, b, -1, graph, dp);
            }
            if(dp[a][b] == -1){
                cout << "no path" << endl;
            }
            else {
                cout << dp[a][b] << endl;
            }
        }
        cin >> c >> s >> q;
        t++;
    }
    return 0;
}