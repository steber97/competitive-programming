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
typedef pair<int, int> ii;
typedef vector<vector<ii>> vvii;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

ii fatina(int tot, int spent, int i, const vii& items, vvii& dp){
    if (i==items.size()){
        return {0,0};
    }    
    if (dp[spent][i].first!=-1)
        return dp[spent][i];
    ii res = fatina(tot, spent, i+1, items, dp);
    if(spent+items[i].first<=tot){
        ii res2 = fatina(tot, spent+items[i].first, i+1, items, dp);
        if (res2.first + items[i].second > res.first){
            res.first = res2.first + items[i].second;
            res.second = res2.second + items[i].first;
        }
        else if (res2.first + items[i].second == res.first)
            res.second = max(res.second, res2.second + items[i].first);
    }
    dp[spent][i] = res;
    return res;
}

int main(){
    int n,m;
    while(cin >> m >> n){
        vii items(n);
        FOR(i,0,n){
            cin >> items[i].first >> items[i].second;
        }
        vvii dp1(m+1, vii(n,{-1,-1}));
        vvii dp2(m+201, vii(n,{-1,-1}));

        ii res1 = fatina(m, 0, 0, items, dp1);
        ii res2 = fatina(m+200, 0, 0, items, dp2);

        if (res1.first >= res2.first)
            cout << res1.first << endl;
        else {
            if (res2.second > 2000)
                cout << res2.first << endl;
            else
                cout << res1.first << endl;
        }
    }
    return 0;
}