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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<iii> viii;
typedef pair<double,double> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int leftMcbc(int i, vvi& graph, vb& taken, vi& match){
    if (taken[i])
        return 0;
    taken[i] = 1;
    FOR(j,0,graph[i].size()) {
        if ((match[graph[i][j]] == -1) || leftMcbc(match[graph[i][j]], graph, taken, match)) {
            match[graph[i][j]] = i;
            return 1;
        }
    }
    return 0;
}


int mcbc(vvi& graph, int leftsize) {
    vi match(graph.size(), -1);
    int result = 0;
    FOR(i,0,leftsize) {
        vb taken(leftsize, false);
        result += leftMcbc(i, graph, taken, match);
    }
    return result;
}

int main(){
    int T ; cin >> T;
    FOR(t,0,T){
        int n; cin >> n;
        vi v1(n);
        FOR(i,0,n) {
            cin >> v1[i];
        }
        int m; cin >> m;
        vi v2(m);
        FOR(i,0,m) {
            cin >> v2[i];
        }
        vvi graph(n+m, vi());
        FOR(i,0,n){
            FOR(j,0,m){
                if ((v2[j]==0) || ((v1[i] != 0) && (v2[j] % v1[i]) == 0)) {
                    graph[i].push_back(j+n);
                    graph[j+n].push_back(i);
                }
            }
        }
        int result = mcbc(graph, n);
        cout << "Case " << t+1 << ": " << result << endl;
    }
    return 0;
}