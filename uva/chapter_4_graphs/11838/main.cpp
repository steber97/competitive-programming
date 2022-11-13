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


vector<vector<int>*> scc(int i, vvi& graph, vi& dfs_num, vi& dfs_low, vb& visited, stack<int>& s, int& count){
    /*
        Graph needs to be directed.
        dfs_low and dfs_num are set to -1.
        visited is set to false.
        parents is set to -1. 
        The root node (usually 0) must have itself as parent (usually parents[0] = 0).
    */
    vector<vector<int>*> res;
    dfs_num[i] = dfs_low[i] = count++;
    visited[i] = true;
    s.push(i);

    FOR(j,0,graph[i].size()){
        if (dfs_num[graph[i][j]] == -1){
            // Unvisited
            vector<vector<int>*> tmp = scc(graph[i][j], graph, dfs_num, dfs_low, visited, s, count);
            res.insert(res.end(), tmp.begin(), tmp.end());
        }

        if (visited[graph[i][j]]){
            dfs_low[i] = min(dfs_low[i], dfs_low[graph[i][j]]);
        }
    }
    if(dfs_num[i] == dfs_low[i]) {
        // it is the root of an scc
        vi* scc_tmp = new vi();
        while(!s.empty()){
            int t = s.top(); s.pop();
            scc_tmp->push_back(t);
            visited[t] = false;
            if (t == i)
                break;
        }
        res.push_back(scc_tmp);
    }
    return res;

}


int main(){
    int n,m;
    cin >> n >> m;
    while(n!=0){
        vvi graph(n, vi());
        FOR(i,0,m){
            int a,b,c;
            cin >> a >> b >> c;
            a--; b--;
            graph[a].push_back(b);
            if (c==2)
                graph[b].push_back(a);
        }
        vi dfs_num(n,-1), dfs_low(n,-1);
        vb visited(n,false);
        stack<int> s;
        int count = 0;
        vector<vi*> sccs = scc(0, graph, dfs_num, dfs_low, visited, s, count);

        if (sccs.size()==1 && sccs[0]->size() == n)
            cout << 1 << endl;
        else
            cout << 0 << endl;

        for(vi* v: sccs)
            delete(v);
        cin >> n >> m;
    }
    return 0;
}