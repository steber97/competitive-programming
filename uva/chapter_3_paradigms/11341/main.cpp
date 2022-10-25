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


int fatina(int i, int remaining, vi& hours_per_sub, vvvi& dp, vvi& hours){
    int n = hours_per_sub.size();
    if (i==n)
        return 0;
    if (dp[i][remaining][hours_per_sub[i]] != -1)
        return dp[i][remaining][hours_per_sub[i]];
    
    int res = 0;
    FOR(j, 0, remaining+1){
        int tmp = hours_per_sub[i];
        hours_per_sub[i] = tmp+j;
        res = max(res, hours[i][tmp+j] + fatina(i+1, remaining-j, hours_per_sub, dp, hours));
        hours_per_sub[i] -= j;
    }
    dp[i][remaining][hours_per_sub[i]] = res;
    return res;
}


int main(){
    int T;
    cin >> T;
    std::cout << std::setprecision(2) << std::fixed;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        vvi hours(n,vi(m));
        FOR(i,0,n){
            FOR(j,0,m){
                cin >> hours[i][j];
            }
        }

        vi hours_per_sub(n);
        int counter =0;
        FOR(i,0,n){
            FOR(j,0,m){
                if (hours[i][j]>=5){
                    hours_per_sub[i] = j;
                    counter += j+1;
                    break;
                }
            }
        }
        if (counter <= m){
            vvvi dp(n, vvi(m+1, vi(m+1, -1)));
            int res = fatina(0, m-counter, hours_per_sub, dp, hours);
            double resd = res;
            resd /= n;
            cout << "Maximal possible average mark - ";
            cout << resd + DELTA;
            
            cout << "." << endl;
        }
        else{
            cout << "Peter, you shouldn't have played billiard that much." << endl;
        }
        

    }
   
    return 0;
}