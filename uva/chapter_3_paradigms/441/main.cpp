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
    int t = 0;
    while(true){
        int n;
        cin >> n;
        if (!n)
            break;
        if (t)
            cout << endl;
        t++;
        vi num(n);
        FOR(i,0,n)
            cin >> num[i];
        
        FOR(i,0,n-5){
            FOR(j,i+1,n-4){
                FOR(k, j+1, n-3){
                    FOR(l, k+1, n-2){
                        FOR(m, l+1, n-1){
                            FOR(o, m+1, n){
                                cout << num[i] << " " << num[j] << " " << num[k] << " " << num[l] << " " << num[m] << " " << num[o] << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}