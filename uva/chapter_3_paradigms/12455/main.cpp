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


vi subsets(int so_far, const vector<int>& remaining, int pos){
    if (pos == remaining.size()){
        return {so_far};
    }
    else{
        int a = remaining[pos];
        // remaining.erase(a);
        vi res = subsets(so_far, remaining, pos+1);
        so_far += a;
        vi res2 = subsets(so_far, remaining, pos+1);
        res.insert(res.end(), res2.begin(), res2.end());
        return res;
    }
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int l; cin >> l;
        int p; cin >> p;
        vi remaining;
        FOR(i,0,p){
            int tmp; cin >> tmp;
            remaining.push_back(tmp);
        }
            
        vi s = subsets(0, remaining, 0);
        bool count = false;
        FOR(i,0,s.size()){
            if (s[i] == l)
                count = 1;
        }
        if (count)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

    }
    return 0;
}