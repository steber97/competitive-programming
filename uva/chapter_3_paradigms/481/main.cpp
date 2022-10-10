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
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << " "; cout << endl
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
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    vi vec;
    int tmp;
    while(cin >> tmp){
        vec.push_back(tmp);
    }

    vi d(vec.size(), INT32_MAX);
    d[0] = -INT32_MAX;
    vi p(vec.size(), -1);
    vi dpos(vec.size(), -1);
    dpos[0] = -1;

    FOR(i,0,vec.size()){
        int j = upper_bound(d.begin(), d.end(), vec[i]) - d.begin();
        if(d[j-1] != vec[i]){
            d[j] = vec[i];
            dpos[j] = i;
            p[i] = dpos[j-1];
        }
    }

    int res = 0;
    FOR(i,0,vec.size()){
        if (d[i] < INT32_MAX)
            res = i;
    }
    cout << res << endl << "-" << endl;
    int i = dpos[res];
    vi lis;
    while(i != -1){
        lis.push_back(vec[i]);
        i = p[i];
    }
    reverse(lis.begin(), lis.end());
    FOR(i,0,lis.size()){
        cout << lis[i] << endl;
    }
    return 0;
}