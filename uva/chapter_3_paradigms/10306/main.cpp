#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//  #define TESTING

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

int fatina(int i, int s, int x, int y, vvvi& dp, vii& coins){
    if (i==coins.size())
        return s*s==(x*x + y*y) ? 0 : INT32_MAX-1;
    if (x*x+y*y > s*s)
        return INT32_MAX-1;
    if (dp[i][x][y]!=INT32_MAX)
        return dp[i][x][y];
    int res = fatina(i+1, s, x, y, dp, coins);

    int res2 = fatina(i, s, x+coins[i].first, y+coins[i].second, dp, coins);
    if ((res < (INT32_MAX-1)) && (res2 < (INT32_MAX-1)))
        res = min(res, res2+1);
    else{
        if ((res == (INT32_MAX-1)) && (res2 != (INT32_MAX-1)))
            res = res2+1;
        else if ((res != (INT32_MAX-1)) && (res2 == (INT32_MAX-1)))
            res = res;
        else 
            res = INT32_MAX-1;
    }
    dp[i][x][y] = res;
    COUT(i); COUT(" "); COUT(s); COUT(" "); COUT(res); COUT(endl);
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int m,s;
        cin >> m >> s;
        vii coins(m);
        FOR(i,0,m)
            cin >> coins[i].first >> coins[i].second;
        
        vvvi dp(m, vvi(s+1, vi(s+1, INT32_MAX)));
        
        int res = fatina(0, s, 0, 0, dp, coins);
        if (res != INT32_MAX-1)
            cout << res << endl;
        else 
            cout << "not possible" << endl;
    }    
    return 0;
}