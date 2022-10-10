#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
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
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int lis(int i, int j, vi& l, vvi& dp, bool up, int n){
    if (i == n)
        return 0;
    int res = 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    if  (((up==1) && (l[i] > l[j])) || ((up==0) and (l[i]<l[j]))){
        res = 1 + lis(i+1, i, l, dp, up, n);
    }
        
    res = max(res, lis(i+1, j, l, dp, up, n));
    dp[i][j] = res;
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vi l(n);
        FOR(i,0,n){
            cin >> l[i];
        }
        vvi dpup(n, vi(n, -1));
        vvi dpdown(n, vi(n, -1));
        int maxl = 0;
        FOR(i,0,n){
            maxl = max(maxl, lis(i, i, l, dpup, true, n) + lis(i, i, l, dpdown, false, n) + 1);
        }
        cout << maxl << endl;

    }
    
    return 0;
}