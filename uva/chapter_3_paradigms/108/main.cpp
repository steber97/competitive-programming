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




int main(){
    int n;
    cin >> n;
    vvi grid(n, vi(n));
    FOR(i,0,n)
        FOR(j,0,n)
            cin >> grid[i][j];
    
    vvi gridsum(grid);

    FOR(i,0,n){
        FOR(j,0,n){
            gridsum[i][j] = grid[i][j];
            if (i>0)
                gridsum[i][j] += gridsum[i-1][j];
            if (j>0)
                gridsum[i][j] += gridsum[i][j-1];
            if (i>0 && j>0)
                gridsum[i][j] -= gridsum[i-1][j-1];
        }
    }
    int maxv = -127 * n * n;
    FOR(i,0,n){
        FOR(j,0,n){
            FOR(k,i,n){
                FOR(l,j,n){
                    int val = gridsum[k][l];
                    if (i>0)
                        val -= gridsum[i-1][l];
                    if (j>0)
                        val -= gridsum[k][j-1];
                    if (i>0 && j>0)
                        val += gridsum[i-1][j-1];
                    maxv = max(maxv, val);
                }
            }
        }
    }
    cout << maxv << endl;
    return 0;
}