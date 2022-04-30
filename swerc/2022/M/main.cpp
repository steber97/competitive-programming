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
    FOR(t, 0, T)    {
        int n, m;
        cin >> n >> m;
        int maxr = 0, maxw = 0;
        FOR(i,0,m){
            int r, w;
            cin >> r >> w;
            maxr = max(maxr, r);
            maxw = max(maxw, w);
        }
        if (maxr + maxw > n){
            cout << "IMPOSSIBLE" << endl;
        }
        else{
            FOR(i,0,maxr){
                cout << "R";
            }
            FOR(i,0,maxw){
                cout << "W";
            }
            FOR(i,0,n-(maxr+maxw))
                cout << "W";
            cout << endl;
        }
    }
    return 0;
}