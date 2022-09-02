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


// so far must be empty at the beginning, and remaining must contain the 
// numbers we want to make permutations.
vvi permutations(vi& so_far, unordered_set<int>& remaining){
    if (remaining.size() == 1){
        vi res_v(so_far.size()+1);
        FOR(i,0,so_far.size())
            res_v[i] = so_far[i];
        res_v[so_far.size()] = *(remaining.begin());
        return {res_v};
    }
    else{
        vi rem_v(remaining.size());
        vvi res;
        int i = 0;
        for(int r: remaining){
            rem_v[i] = r;
            i++;
        }
        FOR(j,0,rem_v.size()){
            so_far.push_back(rem_v[j]);
            remaining.erase(rem_v[j]);
            vvi tmp = permutations(so_far, remaining);
            res.insert(res.end(), tmp.begin(), tmp.end());
            so_far.resize(so_far.size()-1);
            remaining.insert(rem_v[j]);
        }
        return res;
    }
}
