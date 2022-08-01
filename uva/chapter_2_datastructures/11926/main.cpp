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

#define N 1000001
int main(){
    int n, m;
    while(true){
        cin >> n >> m;
        if (n==0 && m == 0){
            break;
        }
        bool conflict = false;
        vb time(N, false);
        FOR(i,0,n){
            int s, e;
            cin >> s >> e;
            FOR(j,s,e){
                if (time[j])
                    conflict = true;
                time[j] = true;
            }
        }
        FOR(i,0,m){
            int s, e, r;
            cin >> s >> e >> r;
            FOR(j,0,N){
                bool stop = false;
                FOR(k, s, e){
                    if (((j*r) + k) >= N){
                        stop = true;
                        break;
                    }
                    if (time[(j*r) + k])
                        conflict = true;
                    time[(j*r) + k] = true; 
                }
                if (stop)
                    break;
            }
        }
        cout << (!conflict ? "NO CONFLICT" : "CONFLICT") << endl;
    }    
    return 0;    
}