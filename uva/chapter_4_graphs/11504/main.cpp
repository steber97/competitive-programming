#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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

vvi result;

void scc(int i, vvi& graph, vi& dfs_num, vi& dfs_low, vb& visited, stack<int>& s, int& count){
    /*
        Graph needs to be directed.
        dfs_low and dfs_num are set to -1.
        visited is set to false.
        parents is set to -1. 
        The root node (usually 0) must have itself as parent (usually parents[0] = 0).
    */
    
    dfs_num[i] = dfs_low[i] = count++;
    visited[i] = true;
    s.push(i);

    FOR(j,0,graph[i].size()){
        if (dfs_num[graph[i][j]] == -1){
            // Unvisited
            scc(graph[i][j], graph, dfs_num, dfs_low, visited, s, count);
        }

        if (visited[graph[i][j]]){
            dfs_low[i] = min(dfs_low[i], dfs_low[graph[i][j]]);
        }
    }
    if(dfs_num[i] == dfs_low[i]) {
        // it is the root of an scc
        vi scc_tmp;
        while(!s.empty()){
            int t = s.top(); s.pop();
            scc_tmp.push_back(t);
            visited[t] = false;
            if (t == i)
                break;
        }
        result.push_back(scc_tmp);
    }

}


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        vvi graph(n, vi());
        FOR(i,0,m){
            int a,b;
            cin >> a >> b;
            a--; b--;
            graph[a].push_back(b);
        }

        int count = 0;
        vi dfs_num(n, -1), dfs_low(n, -1);
        vb visited(n, false);
        stack<int> s;
        result.resize(0);
        FOR(i,0,n){
            if (dfs_num[i] == -1){
                scc(i, graph, dfs_num, dfs_low, visited, s, count);
            }
        }

        vi indeg(result.size(), 0);
        vi map_scc(n);
        FOR(i,0,result.size()){
            FOR(j,0,result[i].size()){
                map_scc[result[i][j]] = i;
            }
        }
        FOR(i,0,graph.size()){
            FOR(j,0,graph[i].size()){
                if (map_scc[graph[i][j]] != map_scc[i]){
                    indeg[map_scc[graph[i][j]]] ++;
                }
            }
        }

        int count_res = 0;
        FOR(i,0,indeg.size())
            if (indeg[i]==0)
                count_res++;
        cout << count_res << endl;
    }
    return 0;
}