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

#define IMP INT32_MAX-1
#define MAX INT32_MAX

ii fatina(int i, int s, vi& coins, vvii& dp){
    if (i >= coins.size())
        return (s <= 0 ? make_pair(s,0) : make_pair(IMP, IMP));

    if (s <= 0)
        return make_pair(s,0);
    
    if (dp[i][s] != make_pair(MAX, MAX)){
        return dp[i][s];
    }
    ii res1 = fatina(i+1, s, coins, dp);
    ii res2 = fatina(i+1, s-coins[i], coins, dp);
    res2.second += 1;
    ii res({0,0});
    if (res1.first <= 0 && res2.first <=0){
        if (res1.first > res2.first)
            res = res1;
        else if (res1.first < res2.first)
            res = res2;
        else{
            res.first = res1.first;
            res.second = min(res1.second, res2.second);
        }
    }
    else if (res1.first <= 0 && res2.first > 0){
        res = res1;
    }   
    else if (res1.first > 0 && res2.first <= 0){
        res = res2;
    }   
    else{
        res = {IMP, IMP};
    }
    dp[i][s] = res;
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int s,m;
        cin >> s >> m;
        vi coins(m);
        FOR(i,0,m){
            cin >> coins[i];
        }
        vvii dp(m, vii(s+1, {MAX,MAX}));
        ii res = fatina(0, s, coins, dp);
        cout << s - res.first << " " << res.second << endl;
    }
    return 0;
}

// # import numpy as np

// # def fatina(i: int, s: int, coins, dp):
    
// #     if i>=len(coins):
// #         return (s, 0) if s <= 0 else (IMP, IMP)
// #     if s <= 0:
// #         return (s, 0)
// #     if dp[i][s] != (MAX, MAX):
// #         return dp[i][s]
    
// #     res1 = fatina(i+1, s, coins, dp)
// #     res2 = fatina(i+1, s - coins[i], coins, dp)
// #     res = (0, 0)
// #     if res1[0] <= 0 and res2[0] <= 0:
// #         e1 = res1[0] if res1[0] > res2[0] else res2[0]
// #         if res1[0] > res2[0]:
// #             e2 = res1[1]
// #         elif res1[0] < res2[0]:
// #             e2 = res2[1]+1
// #         else:
// #             e2 = min(res1[1], res2[1] + 1)
// #         res = (e1, e2)
// #     elif res1[0] > 0 and res2[0] <= 0:
// #         res = (res2[0], res2[1]+1)
// #     elif res2[0] > 0 and res1[0] <= 0:
// #         res = res1
// #     else:
// #         res = (IMP, IMP)
// #     dp[i][s] = res
// #     return res

// # if __name__ == "__main__":
// #     MAX = 10002
// #     IMP = 10001
// #     T = int(input())
// #     for t in range(T):
// #         s = int(input()) 
// #         n = int(input())
// #         coins = []
// #         for i in range(n):
// #             coins.append(int(input()))
// #         dp = [[(MAX, MAX) for j in range(s+1)] for i in range(n)] 
// #         res = fatina(0, s, coins, dp)
// #         print("{} {}".format(s - res[0], res[1]))