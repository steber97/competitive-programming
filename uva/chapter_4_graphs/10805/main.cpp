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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001
#define INF 100




int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        int n,m;
        cin >> n >> m;
        vvi graph(n+m, vi(n+m, INF));
        FOR(i,0,m+n)
            graph[i][i] = 0;
        FOR(i,0,m) {
            int a,b; cin >> a >> b;
            graph[a][i+n] = 1;
            graph[i+n][a] = 1;
            graph[b][i+n] = 1;
            graph[i+n][b] = 1;
        }

        FOR(l,0,n+m) 
            FOR(i,0,n+m)
                FOR(j,0,n+m)
                    graph[i][j] = min(graph[i][j], graph[i][l]+graph[l][j]);
        
        int res = INF;
        FOR(i,0,n+m){
            res = min(res, *max_element(graph[i].begin(), graph[i].begin()+n));
        }
        cout << "Case #" << t << ":" << endl << res << endl << endl;
    }
    return 0;
}
