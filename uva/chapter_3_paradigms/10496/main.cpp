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


int tsp(int p, bitset<10> remaining, vvi& dp, vii& pos, int starty, int startx){
    if(remaining == 0){
        return abs(pos[p].first - starty) + abs(pos[p].second - startx);
    }
    if(dp[p][remaining.to_ulong()] != -1)
        return dp[p][remaining.to_ulong()];
    int res = (20+20) * (10+1);
    FOR(i,0,10){
        if (remaining[i]){
            remaining[i] = 0;
            res = min(res, abs(pos[p].first - pos[i].first) + abs(pos[p].second - pos[i].second) + tsp(i, remaining, dp, pos, starty, startx));
            remaining[i] = 1;
        }
    }
    dp[p][remaining.to_ulong()] = res;
    return res;
}


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        int startx,starty; cin >> starty >> startx;
        int q;
        cin >> q;
        vii pos(q);
        FOR(i,0,q){
            cin >> pos[i].first >> pos[i].second;
        }

        int res = (20+20) * (q+1);
        bitset<10> remaining = 0;
        vvi dp(q, vi(1025, -1));
        FOR(i,0,q)
            remaining[i] = 1;
        FOR(i,0,q){
            remaining[i] = 0; 
            res = min(res, abs(pos[i].first - starty) + abs(pos[i].second - startx) + tsp(i, remaining, dp, pos, starty, startx));
            remaining[i] = 1;
        }
        cout << "The shortest path has length " << res << endl;
    }
    return 0;
}