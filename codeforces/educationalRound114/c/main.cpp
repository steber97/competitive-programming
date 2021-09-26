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
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vll heros(n);
    ll sumheros = 0LL;
    FOR(i,0,n){
        cin >> heros[i];
        sumheros += heros[i];
    }
    sort(heros.begin(), heros.end());
    VECT(heros);
    int d; cin >> d;
    ll last = heros[heros.size()-1];
    FOR(i,0,d){
        ll att, def;
        cin >> def >> att;
        VALUE(def); VALUE(att);
        vll::iterator high, low;
        high = upper_bound(heros.begin(), heros.end(), def);
        ll cost = def + att;
        VALUE(cost);
        if (high == heros.end()){
            // no knight greater.
            COUT("NO hero greater\n");
            ll att_missing = def - last;
            ll def_missing = max(0LL, att - (sumheros - last));
            cost = min(cost, att_missing + def_missing);
            
        }
        else{
            ll def_missing = max(0LL, att - (sumheros - *high));
            cost = min(cost, def_missing);
            if (high - heros.begin() > 0){
                ll hero = *prev(high);
                ll sum = 0LL;
                sum += def - hero;
                sum += max(0LL, att - (sumheros - hero));
                cost = min(cost, sum);
            }
        }
        cout << cost << endl;
    }
    

    return 0;
}