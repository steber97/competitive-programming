#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<pair<int,ll>> vill;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<pair<ll,ll>> vllll;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<vector<pair<int,ll>>> vvill;
typedef vector<vllll> vvllll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


// Return the min-cut: at the last iteration, compute V = (A, B) bipartition
// by running the bfs and checking which vertices we can reach. All edges crossing
// this A,B bipartition are part of the min cut.
vii edmondskarp(vvill& graph, int source, int target) {
    int n = graph.size();
    vvll adjmat(n, vll(n, 0));
    vii result;
    FOR(i,0,n){
        FOR(j,0,graph[i].size()){
            adjmat[i][graph[i][j].first] += graph[i][j].second; 
        }
    }
    
    ll f = 0, totflow = 0;
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
        f = LONG_LONG_MAX;
        if(parents[target] != -1){
            int it = target;
            while(parents[it] != it){
                COUT(it);COUT(endl);
                if (f > adjmat[parents[it]][it]){
                    f = adjmat[parents[it]][it];
                }
                f = min(f, adjmat[parents[it]][it]);
                it = parents[it];
            }
            COUT(endl);
            it = target;
            totflow += f;
            while(parents[it] != it){
                adjmat[parents[it]][it] -= f;
                adjmat[it][parents[it]] += f;
                it = parents[it];
            }
        }
        else{
            unordered_set<int> bipartition;
            FOR(i,0,graph.size()){
                if (parents[i]!=-1)
                    bipartition.insert(i);
            }
            FOR(i,0,graph.size()){
                FOR(j,0,graph[i].size()){
                    if (bipartition.find(i)!=bipartition.end() && bipartition.find(graph[i][j].first) == bipartition.end() && graph[i][j].second > 0)
                        result.push_back({i,graph[i][j].first});
                }
            }

        }
        if (f==LONG_LONG_MAX)
            f = 0;
    } while(f > 0);

    return result;
}


int main(){
    
    int n,m;
    do{
        cin >> n >> m;
        if (n!=0){
            vvill graph(n, vill());
            FOR(i,0,m){
                int a,b; ll c; cin >> a >> b >> c;
                a--;b--;
                graph[a].push_back({b,c});
                graph[b].push_back({a,c});
            }
            vii result = edmondskarp(graph, 0, 1);
            FOR(i,0,result.size()){
                cout << result[i].first + 1 << " " << result[i].second + 1 << endl;
            }
            cout << endl;
            
        }
    } while(n!=0);
    return 0;
}