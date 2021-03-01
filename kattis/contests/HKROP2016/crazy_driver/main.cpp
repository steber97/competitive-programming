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
    int n;
    cin >> n;
    vll c(n-1);
    vi t(n);
    FOR(i,0,n-1)
        cin >> c[i];
    FOR(i,0,n)
        cin >> t[i];

    int T = 0;
    ll cost = ((ll)0);
    ll best = LONG_LONG_MAX;
    FOR(i,0,n-1){
        best = min(best, c[i]);
        T += 1;
        cost += c[i];
        int wait = (((t[i+1]-T) % 2) == 0 ? t[i+1]-T : t[i+1] - T + 1);
        if (wait > 0){
            cost += best * (ll(wait));
            T += wait;
        }
    }
    cout << cost << endl;
    
    return 0;    
}