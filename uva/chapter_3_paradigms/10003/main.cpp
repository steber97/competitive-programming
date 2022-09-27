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


int fatina(int start, int end, vvi& dp, vi& cuts){
    if (start + 1 >= end){
        dp[start][end] = 0;
        return 0;
    }
    if (start + 2 == end){
        dp[start][end] = cuts[end] - cuts[start];
        return cuts[end] - cuts[start];
    }
    if (dp[start][end] != -1)
        return dp[start][end];
    
    int best = (end-start) * 1000;
    FOR(i,start+1, end){
        best = min(best, 
                   fatina(start, i, dp, cuts) + fatina(i, end, dp, cuts) + 
                   cuts[end] - cuts[start]);
    }
    dp[start][end] = best;
    return best;

}


int main(){
    int l; cin >> l;
    while(l != 0){
        int n; cin >> n;
        int best = l*n;
        if (n == 0)
            best =  0;
        else{
            vi cuts(n+2);
            cuts[0] = 0;
            FOR(i,0,n)
                cin >> cuts[i+1];
            cuts[n+1] = l;
            sort(cuts.begin(), cuts.end());

            VECT(cuts);
            vvi dp(n+2, vi(n+2, -1));
            FOR(i,1,n+1){
                best = min(best, 
                    fatina(0, i, dp, cuts) + fatina(i,n+1, dp, cuts) + l
                );
            }

            VALUE(dp[1][4]);
            VALUE(dp[1][3]);
        }
        cout << "The minimum cutting is " << best << "." << endl;
        cin >> l;
    }
    return 0;
}