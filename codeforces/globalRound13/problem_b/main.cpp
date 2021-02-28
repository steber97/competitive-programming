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
    int T;
    cin >> T;
    FOR(t,0,T){
        int n, u, v;
        cin >> n >> u >> v;
        vi a(n);
        bool discard_2 = false;
        bool discard_1 = false;
        FOR(i,0,n){
            cin >> a[i];
            if (i > 0){
                if (abs(a[i] - a[i-1]) > 1 ){
                    discard_2 = true;
                }
                if (abs(a[i] - a[i-1]) > 0){
                    discard_1 = true;
                }
            }
        }

        if (discard_2){
            cout << 0 << endl;
        }
        else if (discard_1){
            cout << min(u, v) << endl;
        }
        else{
            cout << min(u+v, v+v)<< endl;
        }

    }
    return 0;    
}