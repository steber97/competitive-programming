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


void print_topsort(int n, vvi& graph, vb& visited, int& missing){
    visited[n] = true;
    if (missing==0)
        return;
    FOR(i,0,graph[n].size()){
        if(!visited[graph[n][i]]){
            print_topsort(graph[n][i], graph, visited, missing);
        }
    }
    cout << n+1;
    missing--;
    if(missing>0)
        cout << " ";
}


int main(){
    
    int n,m;
    while(true) {
        cin >> n >> m;
        if (n==0)
            break;
        vvi graph(n, vi());
        FOR(i,0,m){
            int a,b; cin >> a >> b;
            a--; b--;
            graph[b].push_back(a);
        }
        vb visited(n, false);
        int missing = n;
        FOR(i,0,n){
            if (!visited[i])
                print_topsort(i, graph, visited, missing);
        }
        cout << endl;
    }    
    return 0;
}