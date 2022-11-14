#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second
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
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vector<pair<ll, ll>> cities;


ll dist_squared(pair<ll,ll> p1, pair<ll,ll> p2){
    return (p1.first-p2.first) * (p1.first - p2.first) + 
        (p1.second - p2.second) * (p1.second - p2.second);
}

class Compare{
public:
    bool operator() (ii p1, ii p2)
    {
        return dist_squared(cities[p1.first], cities[p1.second]) > 
                dist_squared(cities[p2.first], cities[p2.second]);
    }
};


int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n;
        double r;
        cin >> n >> r;
        cities.resize(n);
        FOR(i,0,n)
            cin >> cities[i].first >> cities[i].second;
        
        int a = 0;
        vb used(n, false);
        vector<pair<int, int>> result;

        priority_queue<ii, vector<ii>, Compare> pq;
        
        FOR(i,0,n-1){
            used[a] = true;
            FOR(j,0,n){
                if(!used[j]){
                    pq.push({a, j});
                }
            }
            ii p = pq.top(); pq.pop();
            while(used[p.second]){
                p = pq.top(); pq.pop();
            }
            result.push_back(p);
            a = p.second;
        }

        double rails=0, roads=0;
        int states = 1;
        FOR(i,0,n-1){
            double tmp = pow(dist_squared(cities[result[i].first], cities[result[i].second]),0.5);
            if (tmp > r){
                rails += tmp;
                states ++;
            }
            else{
                roads += tmp;
            }
        }
        cout << "Case #" << t << ": ";
        cout << states << " " << round(roads) << " " << round(rails) << endl;

    }
    return 0;
}