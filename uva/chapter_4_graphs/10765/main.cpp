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



vii fatina(int i, vvi& graph, vi& parents, vi& dfs_num, vi& dfs_low, int& count){
    dfs_num[i] = dfs_low[i] = count++;
    vii result;
    int subtrees = 0;  // Counts how many different subtrees are rooted in i.
    int articulation_points = 0;

    FOR(j,0,graph[i].size()){
        if (dfs_num[graph[i][j]] == -1) {
            // unvisited neighbor
            subtrees ++;
            parents[graph[i][j]] = i;
            vii tmp = fatina(graph[i][j], graph, parents, dfs_num, dfs_low, count);
            result.insert(result.end(), tmp.begin(), tmp.end());
            if (dfs_low[graph[i][j]] >= dfs_num[i])
                articulation_points++;
            dfs_low[i] = min(dfs_low[i], dfs_low[graph[i][j]]);
        } 
        else if ((dfs_num[graph[i][j]] != -1) && (parents[i] != graph[i][j])){
            // Back edge, update dfs_low
            dfs_low[i] = min(dfs_low[i], dfs_num[graph[i][j]]);
        }
    }
    // Decide whether i is an articulation point:
    if (parents[i] == i){
        // special case, we have the root.
        if (subtrees>1)
            result.push_back({subtrees, i});
        else
            result.push_back({1, i});
    }
    else {
        if (articulation_points > 0)
            result.push_back({articulation_points+1, i});
        else 
            result.push_back({1, i});
    }           
    return result;
}

bool compare(ii p1, ii p2){
    if(p1.first > p2.first)
        return true;
    if (p2.first > p1.first)
        return false;
    return p1.second < p2.second;
}

int main(){
    int n,m;
    while(cin >> n >> m) {
        if (n == 0 && m == 0)
            break;
        vvi graph(n, vi());
        int a=-2,b=-2;
        cin >> a >> b;
        while(a!=-1){
            graph[a].push_back(b);
            graph[b].push_back(a);
            cin >> a >> b;
        }
        vi dfs_num(n, -1), dfs_low(n,-1), parents(n, -1);
        int count = 0;
        vii result;
        if (n > 0){
            FOR(i,0,n){
                if (dfs_num[i]==-1){
                    parents[i] = i; // root.
                    vii tmp = fatina(i, graph, parents, dfs_num, dfs_low, count);
                    result.insert(result.end(), tmp.begin(), tmp.end());
                }
            }
            
        }
        FOR(i,0,result.size()){
            PAIR(result[i]); COUT(endl);
        }
        
        sort(result.begin(), result.end(), compare);
        FOR(i,0,m){
            cout << result[i].second << " " << result[i].first << endl;
        }
        cout << endl;
    }
    return 0;
}