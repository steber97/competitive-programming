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


int edmondskarp(vvii& graph, int source, int target) {
    int n = graph.size();
    vvi adjmat(n, vi(n, 0));
    FOR(i,0,n){
        FOR(j,0,graph[i].size()){
            adjmat[i][graph[i][j].first] += graph[i][j].second; 
        }
    }
    
    int f = 0, totflow = 0;
    do {
        f=0;
        queue<int> q;
        q.push(source);
        vi parents(n, -1);
        parents[source] = source;
        while(!q.empty()){
            int node = q.front(); q.pop();
            if (node == target)
                break;
            FOR(j,0,graph[node].size()){
                int nei = graph[node][j].first;
                if ((parents[nei] == -1) && (adjmat[node][nei] > 0)){
                    q.push(nei);
                    parents[nei] = node;
                }
            }
        }
        f = INT32_MAX;
        if(parents[target] != -1){
            int it = target;
            while(parents[it] != it){
                // COUT(it);COUT(endl);
                f = min(f, adjmat[parents[it]][it]);
                it = parents[it];
            }
            // COUT(endl);
            it = target;
            totflow += f;
            while(parents[it] != it){
                adjmat[parents[it]][it] -= f;
                adjmat[it][parents[it]] += f;
                it = parents[it];
            }
        }
        if (f==INT32_MAX)
            f = 0;
    } while(f > 0);

    return totflow;
}


int main(){
    int n,m;
    do{
        cin >> n >> m;
        if (n>0){
            vvii graph(n*2 + m*2 + 2, vii());
            int source = 0;
            int target = n*2 + m*2 + 1;
            VALUE(m);
            VALUE(graph.size());
            VALUE(n);
            FOR(i,0,n-2){
                int a,c; cin >> a >> c;
                graph[a].push_back({a+n, c});
                graph[a+n].push_back({a, 0});
            }

            

            graph[1].push_back({1+n, INT32_MAX});
            graph[1+n].push_back({1, 0});

            graph[n].push_back({n+n, INT32_MAX});
            graph[n+n].push_back({n, 0});
            
            FOR(i,0,m){
                int a,b,c; cin >> a >> b >> c;
                graph[n*2+i+1].push_back({n*2+m+i+1, c});
                graph[n*2+i+m+1].push_back({n*2+i+1, 0});

                graph[a+n].push_back({n*2+i+1, INT32_MAX});
                graph[b+n].push_back({n*2+i+1, INT32_MAX});
                graph[n*2+i+1].push_back({a+n, 0});
                graph[n*2+i+1].push_back({b+n, 0});

                graph[n*2+i+m+1].push_back({a, INT32_MAX});
                graph[n*2+i+m+1].push_back({b, INT32_MAX});
                graph[a].push_back({n*2+i+m+1, 0});
                graph[b].push_back({n*2+i+m+1, 0});
            }

            graph[source].push_back({1, INT32_MAX});
            graph[1].push_back({source, 0});

            graph[n*2].push_back({target, INT32_MAX});
            graph[target].push_back({n*2, 0});

            COUT("Edmondskarp"); COUT(endl);
            int flow = edmondskarp(graph, source, target);
            cout << flow << endl;
        }
    }while(n>0);
    return 0;
}
