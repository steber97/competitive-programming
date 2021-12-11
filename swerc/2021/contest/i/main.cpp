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
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << ", "; cout << endl
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
    int n, m;
    cin >> n >> m;
    vvi graph(n, vi());
    FOR(i,0,m){
        int a,b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    FOR(i,0,n){
        COUT(i); COUT(": "); VECT(graph[i]);
    }
    vi distances(n, -1);
    queue<int> q;
    q.push(0);
    distances[0] = 0;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for (int neigh : graph[node]){
            if (distances[neigh] == -1){
                q.push(neigh);
                distances[neigh] = distances[node] + 1;
            }
        }
    }

    int max_dist = 0;
    int max_dist_node = -1;
    for (int i = 0; i < distances.size(); i++){
        if (max_dist_node == -1 || distances[i] > max_dist){
            max_dist_node = i;
        }
        if (distances[i] > max_dist){
            max_dist = distances[i];
        }
        if (distances[i] == -1){
            cout << -1 << endl;
            return 0;
        }
    }

    COUT("Farthest node ");COUT(max_dist_node); COUT(" at dist "); COUT(max_dist); COUT(endl);
    q = queue<int>();
    q.push(max_dist_node);
    FOR(i,0,distances.size())
        distances[i] = -1;
    distances[max_dist_node] = 0;
    VECT(distances);
    while(!q.empty()){
        int node = q.front();
        COUT("Visited "); COUT(node); COUT(endl);
        q.pop();
        for (int neigh : graph[node]){
            COUT("Neighbour: "); COUT(neigh); COUT(endl);
            if (distances[neigh] == -1){
                q.push(neigh);
                distances[neigh] = distances[node] + 1;
            }
        }
    }

    max_dist = 0;
    for (int i = 0; i < distances.size(); i++){
        if (distances[i] > max_dist){
            max_dist = distances[i];
        }
    }
    COUT ("Max dist: "); COUT(max_dist); COUT(endl);
    cout << ceil(log2(max_dist)) << endl;
    
    return 0;
}