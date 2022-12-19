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


int countlives(vvi& graph, int node, vi& dp){
    if (dp[node]!=-1)
        return dp[node];
    if(graph[node].size()==0)
        return 1;
    int res = 0;
    FOR(j,0,graph[node].size()){
        res += countlives(graph, graph[node][j], dp);
    }
    dp[node] = res;
    return res;
}


int main(){
    int n = -1;
    int testcase = 0;
    while(!cin.eof()){
        cin >> n;
        if (cin.eof())
            break;
        if (testcase != 0)
            cout << endl;
        testcase ++;
        vvi graph(n, vi());
        FOR(i,0,n){
            int k;cin >> k;
            FOR(j,0,k){
                int tmp; cin >> tmp;
                graph[i].push_back(tmp);
            }
        }
        vi dp(n, -1);
        int lives = countlives(graph, 0, dp);
        cout<< lives << endl;
    }
    return 0;
}
