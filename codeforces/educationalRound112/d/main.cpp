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
    int n, m;
    cin >> n >> m;
    string s; cin >> s;
    vii queries(m);
    FOR(i,0,m)
        cin >> queries[i].first >> queries[i].second;
    
    vector<string> patterns = {"abc", "acb", "bac", "bca", "cab", "cba"};
    vvi pattern_diff(6, vi(n+1, 0));

    FOR (i,0,6){
        FOR(j,0,n){
            if (patterns[i][j % 3] != s[j]){
                pattern_diff[i][j+1] = pattern_diff[i][j] + 1;
            }
            else{
                pattern_diff[i][j+1] = pattern_diff[i][j];
            }
        }
    }   

    FOR (q, 0, m){
        int best = n + 1;
        FOR(i,0,6){
            best = min(best, pattern_diff[i][queries[q].second] - pattern_diff[i][queries[q].first - 1]);
        }
        cout << best << endl;
    }
    return 0;
}