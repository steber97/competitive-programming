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


int fatina(int n, int k, vvi& dp){
    if (n == 0){
        if (k >= 0)
            return 1;
        else{
            return 0;
        }
    }
    if (k == 0)
        return 0;
    if (dp[n][k] != -1)
        return dp[n][k];
    int res = 0;
    FOR(i,0,n+1){
        if (n-i >= 0)
            res += fatina(n-i, k-1, dp);
            res %= 1000000;
    }
    dp[n][k] = res % 1000000;
    return res % 1000000;
}


int main(){
    int n,k;
    cin >> n >> k;
    vvi dp(101, vi(101, -1));
    while(n!=0){
        cout << fatina(n, k, dp) <<  endl;
        cin >> n >> k;
    }
    return 0;
}