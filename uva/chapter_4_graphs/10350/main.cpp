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


int main(){
    while(!cin.eof()){
        string name; cin >> name;
        VALUE(name);
        if (name.size()==0)
            break;
        int n,m; cin >> n >> m;
        vvvi costs(n-1, vvi(m,vi(m)));
        FOR(i,0,n-1){
            FOR(j,0,m){
                FOR(k,0,m){
                    cin >> costs[i][j][k];
                }
            }
        }

        vvi result(n, vi(m, INT32_MAX));
        FOR(j,0,m)  
            result[0][j] = 0;
        
        FOR(i,0,n-1){
            FOR(j,0,m){
                FOR(k,0,m){
                    result[i+1][k] = min(result[i+1][k], costs[i][j][k] + result[i][j]);
                }
            }
        }
        int res = INT32_MAX;
        FOR(j,0,m){
            res = min(res, result[n-1][j] + 2*(n-1));
        }
        cout << name << endl << res << endl;

    }
    return 0;
}