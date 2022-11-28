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
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare{
    public:
    bool operator() (iii p1, iii p2){
        return get<1>(p1) > get<1>(p2);
    }
};


int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        cout << "Scenario #" << t << endl;
        int n; cin >> n;
        unordered_map<string,int> mapcity;
        FOR(i,0,n){
            string s; cin >> s;
            mapcity[s] = i;
        }

        string start = "Calgary";
        string end = "Fredericton";

        vvii graph(n, vii());

        int m; cin >> m;
        FOR(i,0,m){
            string s1,s2; cin >> s1 >> s2;
            int cost; cin >> cost;
            graph[mapcity[s1]].push_back({mapcity[s2], cost});
        }

        vvi distances(n, vi(n, INT32_MAX));
        distances[mapcity[start]][0] = 0;

        priority_queue<iii, viii, Compare> pq;
        pq.push({mapcity[start], 0, 0});

        while(!pq.empty()){
            int node = get<0>(pq.top());
            int cost = get<1>(pq.top());
            int steps = get<2>(pq.top());
            pq.pop();

            if (distances[node][steps] == cost){
                FOR(j,0,graph[node].size()){
                    int neigh = graph[node][j].first;
                    int dist = graph[node][j].second;
                    if (distances[neigh][steps+1] > cost + dist){
                        distances[neigh][steps+1] = cost + dist;
                        pq.push({neigh, cost+dist, steps+1});
                    }
                }
            }
        }

        int q; cin >> q;
        FOR(i,0,q){
            int steps; cin >> steps;
            int res = INT32_MAX;
            FOR(j,0,min(steps+2, n)){
                if (res > distances[mapcity[end]][j])
                    res = distances[mapcity[end]][j];
            }
            if (res < INT32_MAX){
                cout << "Total cost of flight(s) is $" << res << endl;
            }
            else{
                cout << "No satisfactory flights" << endl;
            }
        }

        if(t!=T)
            cout << endl;
    }
    return 0;
}