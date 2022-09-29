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
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


ll sum_grid(int si, int sj, int ei, int ej, vvll& grid){
    ll res = grid[ei][ej];
    if (si > 0)
        res -= grid[si-1][ej];
    if (sj > 0)
        res -= grid[ei][sj-1];
    if(si>0 && sj>0)    
        res += grid[si-1][sj-1];
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        ll k;
        cin >> n >> m >> k;
        vvll grid(n, vll(m));
        FOR(i,0,n)
            FOR(j,0,m)
                cin >> grid[i][j];
        vvll sumgrid(grid);

        FOR(i,0,n){
            FOR(j,0,m){
                sumgrid[i][j] = grid[i][j];
                if (i>0)
                    sumgrid[i][j] += sumgrid[i-1][j];
                if (j>0)
                    sumgrid[i][j] += sumgrid[i][j-1];
                if (i>0 && j>0)
                    sumgrid[i][j] -= sumgrid[i-1][j-1];
            }
        }
        int best_area = 0;
        ll bestval = ((ll)(n*m))*1000001;
        FOR(i,0,n){
            FOR(j,0,m){
                FOR(ei,i,n){
                    FOR(ej,j,m){
                        ll s = sum_grid(i,j,ei,ej,sumgrid);
                        int area = (ei-i+1) * (ej-j+1);
                        if (s <= k && (area > best_area || (area == best_area && s < bestval))){
                            best_area = area;
                            bestval = s;
                        }
                    }
                }

            }
        }

        if (bestval == ((ll)(n*m))*1000001)
            bestval = 0;
        cout << "Case #" << t+1 << ": " << best_area << " " << bestval<< endl;


    }   
    return 0;
}