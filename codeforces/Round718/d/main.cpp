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
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
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
    int n, m, k;
    cin >> n >> m >> k;
    vvi edges_h(n, vi(m-1)), edges_v(n-1, vi(m));
    FOR(i,0,n){
        FOR(j,0,m-1){
            cin >> edges_h[i][j];
        }
    }
    FOR(i,0,n-1){
        FOR(j,0,m){
            cin >> edges_v[i][j];
        }
    }

    if (k % 2 != 0){
        FOR(i,0,n){
            FOR(j,0,m){
                cout << -1 << " ";
            }
            cout << endl;
        }
    }
    else{
        vvi dp(n,vi(m, 0));
        vvi dp2(n, vi(m, 0));
        FOR(t,0,k/2){
            FOR(i,0,n){
                FOR(j,0,m){
                    dp2[i][j] = INT_MAX;
                    if (i > 0){
                        dp2[i][j] = min(
                            dp2[i][j],
                            dp[i-1][j] + 2 * edges_v[i-1][j]
                        );
                    }
                    if (i < n-1){
                        dp2[i][j] = min(
                            dp2[i][j],
                            dp[i+1][j] + 2 * edges_v[i][j]
                        );
                    }
                    if (j > 0){
                        dp2[i][j] = min(
                            dp2[i][j],
                            dp[i][j-1] + 2 * edges_h[i][j-1]
                        );
                    }
                    if (j < m-1){
                        dp2[i][j] = min(
                            dp2[i][j],
                            dp[i][j+1] + 2 * edges_h[i][j]
                        );
                    }
                }
            }
            FOR(i,0,n){
                FOR(j,0,m){
                    dp[i][j] = dp2[i][j];
                }
            }
        }
        FOR(i,0,n){
            FOR(j,0,m){
                cout << dp[i][j] << " ";
            }
            cout<< endl;
        }
    }
    return 0;
}