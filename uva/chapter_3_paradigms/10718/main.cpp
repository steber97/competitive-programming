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




int main(){
    
    unsigned int n,l,u;
    while(cin >> n >> l >> u){
        int len = 33;
        bitset<33> nb(n), lb(l), ub(u), x(n^((1<<(32)) - 1));
        // cout << nb << endl << x << endl << lb << endl << ub << endl;
        unsigned int res=0;
        bool greater = false;
        for(int i=31; i>=0; i--){
            if (!greater){
                if (lb[i]){
                    res |= 1<<i;
                }
                else{
                    if (x[i]){
                        if ((res | (1<<i)) <= u){
                            res |= (1<<i);
                            greater = true;
                        }
                    }
                }
            }
            else{
                if (x[i]){
                   if ((res | (1<<i)) <= u){
                        res |= (1<<i);
                    } 
                }
            }
        }
        cout << res << endl;
    }
    
    return 0;
}