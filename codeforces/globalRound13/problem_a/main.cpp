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
    int n, q;
    cin >> n >> q;
    vi v(n);
    int count_ones = 0;
    FOR(i,0,n){
        cin >> v[i];
        count_ones += (v[i]==1?1:0);
    }

    FOR(j,0,q){
        int c,p;
        cin >> c >> p;
        if (c==1){
            count_ones += (v[p-1] == 0 ? 1 : -1);
            v[p-1] = 1 - v[p-1];
        }
        if (c==2){
            cout << (count_ones >= p ? 1 : 0) << endl;
        }
    }

    return 0;    
}