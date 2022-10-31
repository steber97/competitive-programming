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

ll fatina(int i, int k, vll& v, ll m, vvll& dp){
    if (i==v.size()){
        if (k==0)
            return 1;
        return 0;
    }
    if (k==0){
        return 1;
    }
    if (dp[i][k]!=-1)
        return dp[i][k];

    ll res = 0;
    res = v[i] * fatina(i+1, k-1, v, m, dp);
    res %= m;
    if(v.size() - (i+1) >= k)
        res += fatina(i+1, k, v, m, dp);
    res %= m;
    dp[i][k] = res;
    return res;
}


int main(){
    ll n,m;
    do{
        cin >> n >> m;
        if (n!=0){
            unordered_set<ll> distinct;
            vll v(n);
            FOR(i,0,n){
                cin >> v[i];
            }
            vvll dp(v.size(), vll(n+1, -1));
            ll result = 0;
            FOR(k,1,n+1){
                ll res = fatina(0, k, v, m, dp) % m;
                result = max(res, result);
            }
            cout << result << endl;
        }
    }while(n!=0);

    return 0;
}