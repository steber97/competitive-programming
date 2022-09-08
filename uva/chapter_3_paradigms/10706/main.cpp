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

bool compare(pair<ll,ll> p1, pair<ll,ll> p2){
    return p1.first < p2.first;
}

int main(){
    int T;
    cin >> T;
    // Generate groups
    // ith group, {total sum, len of ith group}
    vector<pair<ll,ll>> sk({{0,0}});
    ll i=1;
    ll end = 2147483647;
    
    ll count=0; 
    while((*(sk.end()-1)).first < ll(2147483647)){
        sk.push_back({(*(sk.end()-1)).first + (*(sk.end()-1)).second + to_string(i).size(), 
                      (*(sk.end()-1)).second + to_string(i).size()});
        i++;
        count += i;
    }
    FOR(t,0,T){
        pair<ll,ll> q;
        cin >> q.first;
        vector<pair<ll,ll>>::iterator up = lower_bound(sk.begin(), sk.end(), q, [](const pair<ll,ll>& a, const pair<ll,ll>& b){return a.first < b.first;});
        int pos = up - sk.begin() - 1;
        // cout << pos << " " << sk[pos].first << " " << sk[pos].second << endl;
        int count = 1;
        int steps = q.first - sk[pos].first;
        
        while(steps > 0){
            // cout << count << " " << steps << endl;
            if (steps > to_string(count).size()){
                steps -= to_string(count).size();
            }
            else{
                cout << to_string(count)[steps-1] << endl;
                steps = -1;
            }
            count ++;
        }
    }
    return 0;    
}