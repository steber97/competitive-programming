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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001
#define INF 100


ii compute_diam(vvi& graph, int start, ii taboo, bool secondStep=false) {
    queue<int> q;
    q.push(start);
    vi dist(graph.size(), -1);
    dist[start]=0;
    vi parents(graph.size(), -1);
    parents[start] = start;
    while(!q.empty()) {
        int node = q.front(); q.pop();
        FOR(j,0,graph[node].size()) {
            int nei = graph[node][j];
            if (!(((node == taboo.first) && (nei == taboo.second)) || ((node == taboo.second) && (nei == taboo.first)))) {
                if (dist[nei] == -1){
                    q.push(nei);
                    dist[nei] = dist[node]+1;
                    parents[nei] = node;
                }
            }
        }
    }

    int begin = 0;
    FOR(i,0,graph.size()){
        if (dist[i] > dist[begin]){
            begin = i;
        }
    }

    if (secondStep){
        int res = begin;
        FOR(i,0,dist[begin]/2) {
            res = parents[res];
        }
        return {dist[begin], res};
    }
    return compute_diam(graph,begin,taboo,true);
}


int main(){
    int T; cin >> T;
    FOR(t,1,T+1) {
        int n; cin >> n;
        vvi graph(n,vi());
        vii edges;
        FOR(i,0,n-1){
            int a,b; 
            cin >> a >> b;
            a--;b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
            edges.push_back({a,b});
        }

        int best_res = graph.size()+1;
        ii best_edge_remove; ii best_edge_add;
        
        for (auto edge: edges) {
            auto [len1, root1] = compute_diam(graph, edge.first, edge);
            auto [len2, root2] = compute_diam(graph, edge.second, edge);

            int half1 = ceil(float(len1) / 2.0);
            int half2 = ceil(float(len2) / 2.0);

            if ((best_res > (half1 + half2 + 1)) && 
                ((best_res > len1) && (best_res > len2))) {
                best_res = max(len1, len2);
                best_res = max(best_res, half1 + half2 + 1);
                best_edge_add = {root1, root2};
                best_edge_remove = edge;
            } 

        }
        cout << int(best_res) << endl << best_edge_remove.first + 1 << " " << best_edge_remove.second + 1<< endl << best_edge_add.first + 1 << " " << best_edge_add.second + 1 << endl;
    }
    return 0;
}
