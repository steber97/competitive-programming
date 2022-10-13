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
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


ll fatina(int i, int remaining, int mod, const ll d, const vll& l, vector<vvll>& dp){
    mod = mod < 0 ? mod+d : mod;
    if (i==l.size()-1){
        if (remaining>1){
            return 0;
        }
        if (remaining == 1){
            if (((mod + l[i]) % d) == 0)
                return 1;
            return 0;
        }
        if (remaining==0){
            if (mod==0)
                return 1;
            return 0;
        }
    }
    if (remaining==0){
        if (mod==0)
            return 1;
        return 0;
    }
    if (dp[i][remaining][mod] != -1)
        return dp[i][remaining][mod];
    else{
        ll res = 0;
        res += fatina(i+1, remaining, mod, d, l, dp);
        res += fatina(i+1, remaining-1, (mod+l[i])%d, d, l, dp);
        dp[i][remaining][mod] = res;
        return res;
    }
}


int main(){
    int n,Q;
    cin >> n >> Q;
    int t=1;
    while(n!=0 || Q!=0){
        cout << "SET " << t << ":" << endl;
        vll l(n);
        FOR(i,0,n)
            cin >> l[i];
        FOR(q,0,Q){
            ll m, d;
            cin >> d >> m;
            vector<vvll> dp(n, vvll(m+1, vll(d, -1)));
            ll res = fatina(0, m, 0, d, l, dp);
            cout << "QUERY " << q+1 << ": " << res << endl;
        }
        cin >> n >> Q;
        t++;
    }
    return 0;
}