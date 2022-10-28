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

#define IMP INT32_MAX-1
#define MAX INT32_MAX


double dist(ii p1, ii p2){
   return pow((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second), 0.5);
}

pair<double, vi> fatina(int i, bitset<16> visited, vvd& dp, vvvi& dp2, vii& comp){
    if (visited.count() == dp.size()){
        return {0.0, {i}};
    }
    else if (dp[i][visited.to_ulong()] > -10.0){
        return {dp[i][visited.to_ulong()], dp2[i][visited.to_ulong()]};
    }
    pair<double, vi> res({MAX, {}});
    FOR(j, 0, dp.size()){
        if (!visited[j]){
            visited[j] = 1;
            pair<double, vi> res2 = fatina(j,visited,dp,dp2,comp);
            if (res2.first + dist(comp[i], comp[j]) < res.first){
                res = {res2.first + dist(comp[i], comp[j]), res2.second};
                res.second.push_back(i);
            }
            visited[j] = 0;
        }
    }
    dp[i][visited.to_ulong()] = res.first;
    dp2[i][visited.to_ulong()] = res.second;
    return res;
}



int main(){
    int n;
    cin >> n;
    int t=1;
    while(n!=0){
        vii comp(n);
        FOR(i,0,n)
            cin >> comp[i].first >> comp[i].second;
        
        bitset<16> visited(0);
        pair<double, vi> res = {MAX, {}};

        vvd dp(n, vd(65536, -11.0));
        vvvi dp2(n, vvi(65536));
        FOR(i,0,n){
            visited[i] = 1;
            pair<double, vi> res1 = fatina(i, visited, dp, dp2, comp);
            if (res1.first < res.first)
                res = res1;
            visited[i] = 0;
        }

        reverse(res.second.begin(), res.second.end());
        double totlen = 0.0;
        cout << "**********************************************************" << endl;
        cout << "Network #" << t << endl;
        FOR(i,0,n-1){
            cout << "Cable requirement to connect (" << comp[res.second[i]].first << "," << comp[res.second[i]].second << ") to (" << 
                comp[res.second[i+1]].first << "," << comp[res.second[i+1]].second << ") is ";
            double len = dist(comp[res.second[i]], comp[res.second[i+1]]) + 16.0;
            cout << fixed << setprecision(2) << len;
            totlen += len;
            cout << " feet." << endl;
        }
        cout << "Number of feet of cable required is " ;
        cout << fixed << setprecision(2) << totlen << "." << endl;

        cin >> n;
        t++;
    }
    return 0;
}