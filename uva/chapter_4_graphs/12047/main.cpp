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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef pair<double,double> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare{
    public:
    bool operator() (pair<int, ll> p1, pair<int, ll> p2){
        return p1.second > p2.second;
    }
};

vector<ll> dijkstra(vector<vector<pair<int,ll>>>& graph, int source, int target){
    vector<ll> distances(graph.size(), LONG_LONG_MAX);
    distances[source] = 0;
    priority_queue<pair<int, ll>, vector<pair<int, ll>>, Compare> pq;
    pq.push({source, 0LL});
    while(!pq.empty()){
        int node = pq.top().first;
        ll distance = pq.top().second;
        pq.pop();
        if(node == target)
            break;
        if (distances[node] == distance){
            FOR(j,0,graph[node].size()){
                int neigh = graph[node][j].first;
                ll cost = graph[node][j].second;
                if (distances[neigh] > distance + cost){
                    distances[neigh] = distance + cost;
                    pq.push({neigh, distance + cost});
                }
            }
        }
    }
    return distances;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m,source,target;
        ll p;
        cin >> n >> m >> source >> target >> p;
        source--; target--;
        vector<tuple<int,int,ll>> edges;
        vector<vector<pair<int,ll>>> graph(n, vector<pair<int,ll>>()), graphrev(n, vector<pair<int,ll>>());
        FOR(i,0,m){
            int a,b;
            ll c;
            cin >> a >> b >> c;
            a--;b--;
            edges.push_back({a,b,c});
            graph[a].push_back({b,c});
            graphrev[b].push_back({a,c});
        }

        vector<ll> distances1 = dijkstra(graph, source, target);
        vector<ll> distances2 = dijkstra(graphrev, target, source);

        ll best = -1;
        FOR(i,0,edges.size()){
            int a = get<0>(edges[i]), b = get<1>(edges[i]);
            ll cost = get<2>(edges[i]);
            if ((distances1[a] != LONG_LONG_MAX) && (distances2[b] != LONG_LONG_MAX)){
                if((distances1[a] + distances2[b] + cost) <= p){
                    best = max(best, cost);
                }
            }
        }

        cout << best << endl;
    }
    return 0;
}