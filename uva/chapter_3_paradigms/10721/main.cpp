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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<double>> vvd;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


ll fatina(int n, int k, int m, vvll& dp){
    if (n == 0 && k > 0)    
        return 0;
    if (k == 0 && n > 0)
        return 0;
    if (n == 0 && k == 0)
        return 1;
    if (dp[n][k] != -1)
        return dp[n][k];
    ll res = 0;
    FOR(i,1,m+1){
        if (n - i >= 0)
            res += fatina(n-i, k-1, m, dp);
    }
    dp[n][k] = res;
    return res;
}


int main(){
    int n,k,m;
    while(cin >> n >> k >> m){
        vvll dp(n+1, vll(k+1, -1));
        ll result = 0;
        FOR(i,1,m+1){
            result += fatina(n-i, k-1, m, dp);
        }
        // FOR(i,0,n){
        //     VECT(dp[i]);
        // }
        cout << result << endl;
    }
    return 0;
}