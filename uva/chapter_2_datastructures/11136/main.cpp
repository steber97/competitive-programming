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

#define len 65538LL
// #define len 12LL

int main(){
    while (true) {
        int n;
        cin >> n;
        multiset<ll> tree;
        ll res = 0;
        if (n==0)
            break;
        FOR(i,0,n){
            ll t;
            cin >> t;
            FOR(j,0,t){
                ll a;
                cin >>a;
                tree.insert(a);
            }
            res += *prev(tree.end()) - *(tree.begin());
            tree.erase(tree.equal_range(*tree.begin()).first);
            tree.erase(tree.equal_range(*prev(tree.end())).first);
        }
        cout << res << endl;
    }
    return 0;    
}