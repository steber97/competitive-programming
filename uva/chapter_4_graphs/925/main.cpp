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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

vi topsortrec(int i, vvi& graph, vb& visited){
    vi result;
    visited[i] = true;
    FOR(j,0,graph[i].size()){
        int nei = graph[i][j];
        if (!visited[nei]){
            vi tmp = topsortrec(nei, graph, visited);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }
    result.push_back(i);
    return result;
}


vi topsort(vvi& graph){
    vb visited(graph.size(), false);
    vi result;
    FOR(i,0,graph.size()){
        if (!visited[i]){
            vi tmp = topsortrec(i, graph, visited);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }
    return result;
}


int main(){
    int T; cin >> T;
    FOR(t,0,T){
        int n; cin >> n;
        unordered_map<string, int> map;
        vector<string> revmap;
        FOR(i,0,n){
            string s; cin >> s;
            map[s] = i;
            revmap.push_back(s);
        }
        int m; cin >> m;
        vvi graph(n, vi());
        vvb adjmat(n, vb(n, false));
        FOR(i,0,m){
            string s; cin >> s;
            int k; cin >> k;
            FOR(j,0,k){
                string r; cin >> r;
                graph[map[s]].push_back(map[r]);
                adjmat[map[s]][map[r]] = 1;
            }
        }
        vector<string> revmapcopy(revmap);
        vi topsorted = topsort(graph);
        
        vvi dep(n, vi());
        FOR(i,0,topsorted.size()){
            int node = topsorted[i];
            vb directdep = adjmat[node];
            FOR(j,0,graph[node].size()){
                int start = graph[node][j];
                vb visited(n, false);
                visited[start] = true;
                queue<int> q;
                q.push(start);
                while(!q.empty()){
                    int cur = q.front(); q.pop();
                    if (cur != start){
                        directdep[cur] = false;
                    }
                    FOR(k,0,graph[cur].size()){
                        int nei = graph[cur][k];
                        if (!visited[nei]){
                            visited[nei] = true;
                            q.push(nei);
                        }
                    }
                }
            }
            FOR(j,0,n){
                if (directdep[j]){
                    dep[node].push_back(j);
                }
            }
        }

        sort(revmapcopy.begin(), revmapcopy.end());
        FOR(i,0,revmapcopy.size()){
            string actual = revmapcopy[i];
            int node = map[actual];
            if (dep[node].size()>0){
                cout << actual << " " << dep[node].size();
                vector<string> deps;
                FOR(j,0,dep[node].size()){
                    deps.push_back(revmap[dep[node][j]]);
                }
                sort(deps.begin(), deps.end());
                FOR(j,0,deps.size()){
                    cout << " " << deps[j];
                }
                cout << endl;
            }
        }
        
    }

    return 0;
}