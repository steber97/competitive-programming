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


int ways(int n, int lastcoin, vector<vll>&dp, vll& coins){
    if (n < 0)
        return 0;
    if (n==0)
        return 1;
    if (dp[n][lastcoin] != -1){
        return dp[n][lastcoin];
    }
    ll result = 0;
    for(int i=lastcoin; i>=0; i--){
        if (coins[i] <= n){
            result += ways(n-coins[i], i, dp, coins);
        }
    }
    dp[n][lastcoin] = result;
    return result;
}


int main(){
    int n;
    vector<vector<long long>> dp(7500, vll(5, -1));
    vll coins = {50,25,10,5,1};
    while(cin >> n){
        cout << ways(n, 4, dp, coins) << endl;
    }
    return 0;
}