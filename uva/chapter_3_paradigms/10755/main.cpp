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

ll sum_grid(int sa, int sb, int sc, int ea, int eb, int ec, const vvvll& grid){
    
    ll res = grid[ea][eb][ec];
    #ifdef TESTING
    if (sa==1 && sb==1&& sc==0 && ea==1 && eb==1&&ec==1){
        cout << res << endl;
    }
    #endif
    if (sc > 0){
        res -= grid[ea][eb][sc-1];
    }
    #ifdef TESTING
    if (sa==1 && sb==1&& sc==0 && ea==1 && eb==1&&ec==1){
        cout << res << endl;
    }
    #endif
    if (sa > 0){
        res -= grid[sa-1][eb][ec];
        if (sc > 0)
            res += grid[sa-1][eb][sc-1];
    }
    
    #ifdef TESTING
    if (sa==1 && sb==1&& sc==0 && ea==1 && eb==1&&ec==1){
        cout << res << endl;
    }
    #endif

    if (sb > 0){
        res -= grid[ea][sb-1][ec];
        if (sc > 0)
            res += grid[ea][sb-1][sc-1];
    }


    #ifdef TESTING
    if (sa==1 && sb==1&& sc==0 && ea==1 && eb==1&&ec==1){
        cout << res << endl;
    }
    #endif
    
    if (sb>0 && sa>0){
        res += grid[sa-1][sb-1][ec];
        if (sc>0){
            res -= grid[sa-1][sb-1][sc-1];
        }
    }
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        if (t!=0)
            cout << endl;
        int a,b,c;
        cin >> a >> b >> c;

        vvvll grid(a, vvll(b, vll(c)));
        FOR(i,0,a)
            FOR(j, 0, b)
                FOR(k,0,c)
                    cin >> grid[i][j][k];
        
        vvvll sumgrid(grid);
        FOR(i,0,a){
            FOR(j,0,b){
                FOR(k,0,c){
                    sumgrid[i][j][k] = grid[i][j][k];
                    if (k > 0){
                        sumgrid[i][j][k] += sumgrid[i][j][k-1];
                    }
                    if (i>0){
                        sumgrid[i][j][k] += sumgrid[i-1][j][k];
                        if (k>0)
                            sumgrid[i][j][k] -= sumgrid[i-1][j][k-1];
                    }
                    if (j>0){
                        sumgrid[i][j][k] += sumgrid[i][j-1][k];
                        if (k>0)
                            sumgrid[i][j][k] -= sumgrid[i][j-1][k-1];
                        if (i>0){
                            sumgrid[i][j][k] -= (sumgrid[i-1][j-1][k]);
                            if (k>0){
                                sumgrid[i][j][k] += sumgrid[i-1][j-1][k-1];
                            }
                        }
                    }

                }
            }
        }
                    
        ll best = -a*b*c*2147483649;
        FOR(si,0,a){
            FOR(sj,0,b){
                FOR(sk,0,c){
                    FOR(ei,si,a){
                        FOR(ej,sj,b){
                            FOR(ek,sk,c){
                                ll newval = sum_grid(si,sj,sk,ei,ej,ek,sumgrid);
                                if (best < newval){
                                    // cout << sumgrid[ei][ej][ek] << " " << newval << " " << si << " " << sj << " " << sk << " " << ei << " " << ej << " " << ek << endl;
                                    best = newval;
                                }
                            }
                        }
                    }
                }
            }
        }
        // cout << sum_grid(1,1,0,1,1,1,sumgrid) << endl;
        cout << best << endl;
    }
    return 0;
}