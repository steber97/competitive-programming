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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    int T; cin >> T;
    FOR(t,0,T){
        string name; int n,m; cin >> name >> n >> m;
        vvi grid(n, vi(m));
        vvii posbyheight(101, vii());
        FOR(i,0,n){
            FOR(j,0,m){
                cin >> grid[i][j];
                posbyheight[grid[i][j]].push_back({i,j});
            }
        }
        vvi result(n,vi(m, 0));
        int maxres = 0;
        FOR(h,0,posbyheight.size()){
            FOR(k,0,posbyheight[h].size()){
                int i=posbyheight[h][k].first, j=posbyheight[h][k].second;
                result[i][j]=1;
                FOR(l,-1,2){
                    FOR(p,-1,2){
                        if (((l==0) || (p==0)) && ((l!=0) || (p!=0))){
                            if ((((i+l)>=0) && ((i+l)<n)) && (((j+p)>=0) && ((j+p)<m))){
                                if (grid[i][j] > grid[i+l][j+p])
                                    result[i][j] = max(result[i][j], result[i+l][j+p]+1);
                            }
                        }
                    }
                }
                maxres =max(maxres, result[i][j]);
            }
        }
        cout << name << ": " << maxres  << endl;
    }
    return 0;
}
