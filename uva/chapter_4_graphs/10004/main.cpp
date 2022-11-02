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

bool dfs(int i, vvi& graph, vi& colors){
    bool res = true;
    FOR(j,0,graph[i].size()){
        int neigh = graph[i][j];
        if (colors[neigh]==-1){
            colors[neigh] = (colors[i] + 1) % 2;
            res &= dfs(neigh, graph, colors);
        }
        else if (colors[neigh]==colors[i])
            res = false;
    }
    return res;
}

int main(){
    
    int n;
    while(cin >> n){
        if (n==0)
            break;
        int l;
        cin >> l;
        vvi graph(n, vi());
        FOR(i,0,l){        
            int a,b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);    
        }
        vi colors(n, -1);
        colors[0] = 1;
        bool res = dfs(0, graph, colors);
        if (res)
            cout << "BICOLORABLE." << endl;
        else 
            cout << "NOT BICOLORABLE." << endl;
    }
    return 0;
}