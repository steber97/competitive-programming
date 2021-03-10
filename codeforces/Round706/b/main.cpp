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
    FOR(t, 0, T){
        int n,k;
        cin >> n >> k;
        vi v(n);
        FOR(i,0,n){
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        bool mexmax = true;
        FOR(i,0,n){
            if (v[i] != i){
                mexmax = false;
            }
        }
        if (k == 0){
            cout << n << endl;
        }
        else if (mexmax){
            cout << n + k << endl;
        }
        else{
            int max = v[v.size()-1];
            int mex = 0;
            int i = 0;
            while(i < n){
                if (v[i]==i)
                    i++;
                else{
                    mex = i;
                    break;
                }
            }
            int newval = max+mex;
            newval = newval % 2 == 0 ? newval : newval + 1;
            newval /= 2;
            bool found = false;
            FOR(i,0,n){
                if (v[i]==newval){
                    found = true;
                }
            }
            cout << (found?n:n+1) << endl;

        }
    }
}