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
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

class Compare{
    public:
    bool operator() (ii a, ii b) {
        return a.second > b.second;
    }
};

int main(){
    int T;
    cin >>T;
    FOR(t,1,T+1){
        int n,m,s,e;
        cin >> n >> m >> s >> e;
        vvii graph(n, vii());
        vi distances(n, INT32_MAX);
        distances[s] = 0;
        FOR(i,0,m){
            int a,b,w;
            cin >> a >> b >> w;
            graph[a].push_back({b, w});
            graph[b].push_back({a, w});
        }

        priority_queue<ii, vii, Compare> pq;
        pq.push({s,0});
        while(!pq.empty()){
            int node=pq.top().first, cost = pq.top().second; 
            VALUE(node);
            pq.pop();
            if (node == e){
                break;
            }
            if (cost == distances[node]){
                VALUE(graph[node].size());
                FOR(j,0,graph[node].size()){
                    int ne = graph[node][j].first;  // neigh
                    int cn = graph[node][j].second;  // cost neigh
                    if (distances[ne] > cost + cn){
                        distances[ne] = cost + cn;
                        pq.push({ne, distances[ne]});
                    }
                }
            }
        }
        cout << "Case #" << t << ": ";
        if (distances[e] != INT32_MAX){
            cout << distances[e] << endl;
        }
        else {
            cout << "unreachable" << endl;
        }
    }
    return 0;
}