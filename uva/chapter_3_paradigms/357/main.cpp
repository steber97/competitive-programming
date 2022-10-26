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

ll fatina(int i, ll val, vvll& dp, const vll& cents){
    if (i==5){
        if (val == 0)
            return 1;
        return 0;
    }
    if (val == 0){
        return 1;
    }
    if (dp[i][val] != -1)
        return dp[i][val];
    ll res = 0;
    int j = 0;
    while(val - (j * cents[i]) >= 0){
        res += fatina(i+1, val-(j*cents[i]), dp, cents);
        j++;
    }
    dp[i][val] = res;
    return res;
}


int main(){
    vll cents = {50, 25, 10, 5, 1};
    ll n;
    vvll dp(5, vll(31000, -1));
    while(cin >> n){
        ll res = fatina(0, n, dp, cents);
        if (res == 1){
            cout << "There is only 1 way to produce " << n << " cents change." << endl;
        }
        else{
            cout << "There are " << res << " ways to produce " << n << " cents change." << endl;
        }
    }
    return 0;
}