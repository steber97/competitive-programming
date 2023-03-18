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


int get_cost(int node, vvi& graph, vi& parents, const float T) {
    if (graph[node].size() == 0)
        return 1;
    
    vi costs(graph[node].size());
    FOR(i,0,graph[node].size()){
        costs[i] = get_cost(graph[node][i], graph, parents, T);
    }
    sort(costs.begin(), costs.end());
    int result = 0;
    FOR(i,0,graph[node].size()){
        result += costs[i];
        if ((float(i+1) / float(graph[node].size()) - (T/100.)) >= -DELTA){
            break;
        }
    }
    return result;
}

int main(){
    while(!cin.eof()) {
        int n; float T;
        cin >> n >> T;
        if (n==0)
            break;
        vi parents(n+1);
        vvi graph(n+1, vi());
        FOR(i,0,n){
            int p; cin >> p;
            parents[i+1] = p;
            graph[p].push_back(i+1);
        }

        cout << get_cost(0, graph, parents, T) << endl;
    }
    return 0;
}
