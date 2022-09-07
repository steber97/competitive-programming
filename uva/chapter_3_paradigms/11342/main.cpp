#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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
    unordered_map<int, tuple<int,int,int>> myset;
    FOR(i,0,225){
        FOR(j,i,225){
            if (i*i + j*j > 50000)
                break;
            FOR(k,j,225){
                if (i*i + j*j + k*k > 50000)
                    break;
                if (myset.find(i*i + j*j + k*k) == myset.end())
                    myset[i*i + j*j + k*k] = {i, j, k};
            }
        }
    }
    
    int n;
    cin >> n;
    FOR(i,0,n){
        int t;
        cin >> t;
        if (myset.find(t) != myset.end()){
            cout << get<0>(myset[t]) << " " << get<1>(myset[t]) << " " << get<2>(myset[t]) << endl;
        }
        else{
            cout << -1 << endl;
        }
    }
    return 0;
}