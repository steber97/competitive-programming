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


bool bipcheck(int i, vvi& graph, vi& bicoloring) {
    bool res = true;
    FOR(j,0,graph[i].size()){
        if (bicoloring[graph[i][j]] == bicoloring[i])
            return false;
        else if (bicoloring[graph[i][j]] == -1){
            bicoloring[graph[i][j]] = (bicoloring[i] + 1) % 2;
            res &= bipcheck(graph[i][j], graph, bicoloring);
        }
    }
    return res;
}


int main(){
    int n;
    while(true){
        cin >> n;
        if (n == 0)
            break;
        vvi graph(n, vi());
        int a,b;
        while(true){
            cin >> a >> b;
            if (a == 0)
                break;
            a--; b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vi bicoloring(n, -1);
        bool isbip = true;
        FOR(i,0,n){
            if (bicoloring[i] == -1){
                bicoloring[i] = 1;
                isbip &= bipcheck(i, graph, bicoloring);
            }
        }
        cout << (isbip ? "YES" : "NO") << endl;
    }
    return 0;
}