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


vii find_articulation_bridges(int i,
                            vvi& graph,
                            vi& parents,
                            vi& dfs_num,
                            vi& dfs_low,
                            int& count){
    
    dfs_num[i] = dfs_low[i] = count++;
    vii result;
    FOR(j,0,graph[i].size()){
        if (dfs_num[graph[i][j]] == -1) {
            // unvisited neighbor
            parents[graph[i][j]] = i;
            vii tmp = find_articulation_bridges(graph[i][j], graph, parents, dfs_num, dfs_low, count);
            result.insert(result.end(), tmp.begin(), tmp.end());
            if (dfs_low[graph[i][j]] > dfs_num[i]){
                ii app = ((i<graph[i][j]) ? make_pair(i, graph[i][j]) : make_pair(graph[i][j], i));
                result.push_back(app);
            }
            dfs_low[i] = min(dfs_low[i], dfs_low[graph[i][j]]);
        } 
        else if ((dfs_num[graph[i][j]] != -1) && (parents[i] != graph[i][j])){
            // Back edge, update dfs_low
            dfs_low[i] = min(dfs_low[i], dfs_num[graph[i][j]]);
        }
    }
             
    return result;
}

int main(){
    
    int n;
    while(cin >> n) {
        vvi graph(n, vi());
        FOR(i,0,n){
            int j;
            cin >> j;
            string s;
            cin >> s;
            int num_con = stoi(s.substr(1,s.size()-2));
            FOR(k,0,num_con){
                int l; cin >> l;
                graph[j].push_back(l);
            }
        }
        vi dfs_num(n, -1), dfs_low(n,-1), parents(n, -1);
        int count = 0;
        vii result;
        if (n > 0){
            FOR(i,0,n){
                if (dfs_num[i]==-1){
                    parents[i] =i; // root.
                    vii tmp = find_articulation_bridges(i, graph, parents, dfs_num, dfs_low, count);
                    result.insert(result.end(), tmp.begin(), tmp.end());
                }
            }
            
        }
        else
            result = {};
        cout << result.size() << " critical links" << endl;
        sort(result.begin(), result.end());
        FOR(i,0,result.size()){
            cout << result[i].first << " - " << result[i].second << endl;
        }
        cout << endl;
    }
    return 0;
}