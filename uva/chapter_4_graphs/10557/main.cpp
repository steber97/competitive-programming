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
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


bool dfs(int start, int end, vvii& graph, vb& visited){
    if (start == end)
        return true;
    bool res = false;
    FOR(j,0,graph[start].size()){
        int neigh = graph[start][j].first;
        if (!visited[neigh]){
            visited[neigh] = 1;
            res |= dfs(neigh, end, graph, visited);
        }
    }
    return res;
}


int main(){
    while(true){
        int n; cin >> n;
        if(n==-1)
            break;
        vvii graph(n, vii());
        vi weights(n);
        FOR(i,0,n){
            int w; cin >> w;
            weights[i] = w;
            int m; cin >> m;
            FOR(j,0,m){
                int neigh; cin >> neigh; neigh--;
                graph[i].push_back({neigh, -1});
            }
        }
        // Compute weights of the edges.
        FOR(i,0,n){
            FOR(j,0,graph[i].size()){
                graph[i][j].second = weights[graph[i][j].first];
            }
        }

        vi distances(n, 0);
        distances[0] = 100; // initial weight is 100.
        
        FOR(u,0,n){
            FOR(i,0,n){
                if (distances[i]>0){
                    FOR(j,0,graph[i].size()){
                        if (distances[graph[i][j].first] < distances[i] + graph[i][j].second){
                            distances[graph[i][j].first] = distances[i] + graph[i][j].second;
                        }    
                    }
                }
            }
        }
        bool win = false;
        VECT(distances);
        if (distances[n-1]>0){
            win = true;
        }
        else{
            // check for infinite loops.
            vi distances2(distances);
            FOR(u,0,n){
                FOR(i,0,n){
                    if (distances2[i]>0){
                        FOR(j,0,graph[i].size()){
                            if (distances2[graph[i][j].first] < distances2[i] + graph[i][j].second){
                                distances2[graph[i][j].first] = distances2[i] + graph[i][j].second;
                            }    
                        }
                    }
                }
            }
            FOR(i,0,n){
                if (distances[i] < distances2[i]){
                    // part of an infinite loop. try to get to n-1 without considering weights.
                    vb visited(n, false);
                    visited[i] = true;
                    win |= dfs(i, n-1, graph, visited);
                }
            }
        }
        cout << (win ? "winnable" : "hopeless") << endl;
    }
    return 0;
}