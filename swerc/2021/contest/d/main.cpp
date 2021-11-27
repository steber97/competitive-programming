#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001




int main(){
    int I, S, m, M;
    cin >> I >> S >> m >> M;
    vector<vector<ii>> graph(I, vector<ii>());
    vii streets(S);
    FOR(i, 0, S){
        int i1, i2, l;
        cin >> i1 >> i2 >> l;
        graph[i1].push_back({i2, l});
        graph[i2].push_back({i1, l});
        streets[i] = {i1, i2};
    }

    priority_queue<ii> q;
    q.push({0, 0});
    vi distances(I, -1);
    vb visited(I, false);
    vi parents(I, -1);
    parents[0] = 0;
    distances[0] = 0;
    visited[0] = true;

    while(!q.empty()){
        ii n = q.top();
        q.pop();
        if (distances[n.first] == n.second){
            distances[n.first] = n.second;
            FOR(i,0,graph[n.first].size()){
                if(distances[graph[n.first][i].first] == -1 || distances[graph[n.first][i].first] > graph[n.first][i].second + distances[n.first]){
                    q.push({graph[n.first][i].first, graph[n.first][i].second + distances[n.first]});
                    distances[graph[n.first][i].first] = graph[n.first][i].second + distances[n.first];
                }
            }
        }
    }

    int result = 0;
    vi dist_s(S);
    FOR(i,0,S){
        dist_s[i] = min(distances[streets[i].first], distances[streets[i].second]);
        if (dist_s[i] < (M % 2 == 0 ? M / 2 : M/2 + 1))
            result++;
    }
    cout << result << endl;
    return 0;
}