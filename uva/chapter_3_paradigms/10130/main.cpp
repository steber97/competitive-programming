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




int ks(int w, vii& objs, int i, vvi& dp){
    if (i==objs.size()){
        return 0;
    }
    if (dp[i][w] != -1){
        return dp[i][w];
    }
    int bestval = 0;
    if (objs[i].second <= w){
        bestval = max(bestval, objs[i].first + ks(w-objs[i].second, objs, i+1, dp));
    }
    bestval = max(bestval, ks(w, objs, i+1, dp));
    dp[i][w] = bestval;
    return bestval;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n; cin >> n;
        vii objs(n);
        FOR(i,0,n){
            cin >> objs[i].first>> objs[i].second;
        }

        int g; cin >> g;
        int res=0;
        vvi dp(n, vi(31, -1));
        FOR(i,0,g){
            int w; cin >> w;
            res += ks(w, objs, 0, dp);
        }
        cout << res << endl;
    }
    return 0;
}