#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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
typedef vector<vvi> vvvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<pair<int,ll>> vill;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<pair<ll,ll>> vllll;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<vector<pair<int,ll>>> vvill;
typedef vector<vllll> vvllll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int fatina(vector<string>& grid, int i, int j, vvi& dp){
    int n = grid.size();
    if (i==0)
        return 1;
    if (dp[i][j]!=-1)
        return dp[i][j];
    int res = 0;
    vii pos= {{i-1,j-1}, {i-1,j+1}};
    vii pos2 = {{i-2,j-2}, {i-2, j+2}};

    FOR(k,0, pos.size()){
        if((pos[k].first >=0) && (pos[k].first <n)){
            if ((pos[k].second >= 0) && (pos[k].second < n)) {
                if (grid[pos[k].first][pos[k].second] == '.'){
                    int tmp = fatina(grid, pos[k].first, pos[k].second, dp);
                    res += tmp; res %= 1000007;
                }
            }
        }
    }

    FOR(k,0,2){
        if ((pos2[k].first >= 0) && (pos2[k].first < n)){
            if((pos2[k].second >= 0) && (pos2[k].second < n)){
                if((grid[pos2[k].first][pos2[k].second] == '.') && (grid[pos[k].first][pos[k].second] == 'B')){
                    int tmp = fatina(grid, pos2[k].first, pos2[k].second, dp);
                    res += tmp; res %= 1000007;
                }
            }
        }
    }

    dp[i][j] = res;
    return res;
}


int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        int n; cin >> n;
        vector<string> grid(n);
        FOR(i,0,n)
            cin >> grid[i];
        ii start;
        FOR(i,0,n){
            FOR(j,0,n){
                if (grid[i][j] == 'W'){
                    start = {i,j};
                }
            }
        }

        vvi dp(n, vi(n, -1));
        int result = fatina(grid, start.first, start.second, dp);
        cout << "Case " << t << ": " << result << endl;
    }
    return 0;
}