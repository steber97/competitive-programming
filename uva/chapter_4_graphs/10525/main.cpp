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
typedef vector<viii> vviii;
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi floydwarshall(vviii& graph){
    vvi distances(graph.size(), vi(graph.size(), INT32_MAX));
    FOR(i,0,graph.size())
        distances[i][i] = 0;

    FOR(i,0,graph.size()){
        FOR(j,0,graph[i].size()){
            int neigh = get<0>(graph[i][j]);
            int cost = get<1>(graph[i][j]);
            distances[i][neigh] = min(cost, distances[i][neigh]);
        }
    }


    FOR(u,0,graph.size()){
        FOR(i,0,graph.size()){
            FOR(j,0,graph.size()){
                if ((distances[i][u] != INT32_MAX) && (distances[u][j] != INT32_MAX)){
                    distances[i][j] = min(distances[i][j], distances[i][u] + distances[u][j]);
                }
            }
        }
    }

    return distances;
}


vvi findpaths(vviii& graph, vvi& distances, int start, int end) {
    VALUE(start); VALUE(end);
    vvi result;
    if (start == end)
        return vvi({{0}});
    FOR(j,0,graph[start].size()){
        int neigh = get<0>(graph[start][j]);
        int cost = get<1>(graph[start][j]);
        int time = get<2>(graph[start][j]);
        if (cost + distances[neigh][end] == distances[start][end]){
            vvi res2 = findpaths(graph, distances, neigh, end);
            FOR(i,0,res2.size()){
                res2[i].push_back(time);
            }
            result.insert(result.end(), res2.begin(), res2.end());
        }
    }
    
    return result;
}


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        vviii grapht(n, viii());
        FOR(i,0,m){
            int a,b,time,length;
            cin >> a >> b >> time >> length;
            a--;b--;
            grapht[a].push_back({b,time,length});
            grapht[b].push_back({a,time, length});
        }
        vvi distances = floydwarshall(grapht);
        FOR(i,0,distances.size()){
            VECT(distances[i]);
        }

        int Q; cin >> Q;
        FOR(q,0,Q){
            int start, end; cin >> start >> end;
            start--; end--;
            vvi paths = findpaths(grapht, distances, start, end);
            FOR(i,0,paths.size())
                VECT(paths[i]);
            int bestres = INT32_MAX;
            FOR(i,0,paths.size()){
                int res = 0;
                FOR(j,0,paths[i].size()){
                    res += paths[i][j];
                }
                bestres = min(bestres, res);
            }
            if (bestres == INT32_MAX){
                cout << "No Path." << endl;
            }
            else{
                cout << "Distance and time to reach destination is " <<
                        bestres << " & " << distances[start][end] << "." << endl;
            }
        }
        if (t!=T-1)
            cout << endl;
    }
    return 0;
}