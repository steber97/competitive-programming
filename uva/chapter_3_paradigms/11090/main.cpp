#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

float best_avg = 10000001;

#define MAXINT 10000001

float cycles(vector<vii>& graph, vb& visited, int start, int node, float sum_so_far, int visited_so_far){
    float best = MAXINT;
    FOR(i,0,graph[node].size()){
        if (graph[node][i].first == start){
            //end of cycle.
            // COUT("FOUND CYCLE "); COUT((sum_so_far + graph[node][i].second) / visited_so_far); COUT(endl);
            best = min(best, (sum_so_far + graph[node][i].second) / visited_so_far);
            best_avg = min(best_avg, best);
        }
        else if (!visited[graph[node][i].first]){
            if (((sum_so_far+graph[node][i].second) / visited_so_far) < best_avg){
                visited[graph[node][i].first] = 1;
                best = min(best, cycles(graph, visited, start, graph[node][i].first, sum_so_far+graph[node][i].second, visited_so_far+1));
                best_avg = min(best_avg, best); 
                visited[graph[node][i].first] = 0;
            }
        }
    }
    return best;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        best_avg = MAXINT;
        int n,m;
        cin >> n >> m;
        vector<vii> graph(n, vii());
        FOR(i,0,m){
            int a,b,c; cin >> a;cin >>b;cin>>c;
            a--; b--;
            graph[a].push_back({b,c});
        }
        
        FOR(i,0,n){
            vb visited(n, false);
            visited[i] = 1;
            best_avg = min(best_avg, cycles(graph, visited, i, i, 0.0, 1));
        }
        if (abs(best_avg - MAXINT)<DELTA)
            cout << "Case #" << t+1 << ": No cycle found." << endl;
        else
            printf("Case #%d: %.2f\n", t+1, best_avg);
            // cout << "Case #" << t+1 << ": " << best_avg << endl;
    }
    return 0;
}