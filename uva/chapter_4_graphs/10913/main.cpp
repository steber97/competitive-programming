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
    int n,k;
    int testcase = 1;
    do{
    cin >> n >> k;
    if (n>0){
        vvi grid(n, vi(n));
        vvi neg(n, vi(n, 0));
        FOR(i,0,n){
            FOR(j,0,n){
                int tmp; cin >> tmp;
                grid[i][j] = tmp;
            }
        }

        vvi sumgrid(grid);
        FOR(i,0,n){
            FOR(j,0,n){
                if (j>0)
                    sumgrid[i][j] = sumgrid[i][j-1] + grid[i][j];
                neg[i][j] = (j>0?neg[i][j-1]:0) + (grid[i][j]<0?1:0);
            }
        }

        // FOR(i,0,n){
        //     FOR(j,0,n){
        //         COUT(sumgrid[i][j]);COUT("\t");
        //     }
        //     COUT(endl);
        // }COUT(endl);
        // FOR(i,0,n){
        //     FOR(j,0,n){
        //         COUT(neg[i][j]);COUT("\t");
        //     }
        //     COUT(endl);
        // }COUT(endl);


        vvvi dp(k+1, vvi(n+1, vi(n, -INT32_MAX)));
        dp[0][0][0] = 0;
        FOR(i,0,n){
            FOR(j,0,n){ // start
                FOR(l,0,n){ // end
                    FOR(p,0,k+1){
                        if (dp[p][i][j] > -INT32_MAX){
                            int mi = min(j,l), ma = max(j,l);
                            int ne = neg[i][ma] - (mi > 0 ? neg[i][mi-1] : 0);
                            if ((ne + p) <= k){
                                int diff = sumgrid[i][ma] - (mi>0 ? sumgrid[i][mi-1] : 0);
                                dp[ne+p][i+1][l] = max(dp[ne+p][i+1][l], dp[p][i][j] + diff);
                            }
                            
                        }
                    }
                }
            }
            // FOR(j,0,n){
            //     COUT(dp[0][i+1][j]); COUT("\t");
            // }
            // COUT(endl);
            // break;
        }
        int result = -INT32_MAX;
    
        FOR(p,0,k+1){
            result = max(result, dp[p][n][n-1]);
        }
         
        cout << "Case " << testcase << ": " << (result>-INT32_MAX?to_string(result):"impossible") << endl;
        testcase ++;
    }
    } while(n>0);
    return 0;
}