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


vi find_articulation_points(int i,
                            vvi& graph,
                            vi& parents,
                            vi& dfs_num,
                            vi& dfs_low,
                            int& count){
    
    dfs_num[i] = dfs_low[i] = count++;
    vi result;
    int subtrees = 0;  // Counts how many different subtrees are rooted in i.
    bool articulation_point = false;
    FOR(j,0,graph[i].size()){
        if (dfs_num[graph[i][j]] == -1) {
            // unvisited neighbor
            subtrees ++;
            parents[graph[i][j]] = i;
            vi tmp = find_articulation_points(graph[i][j], graph, parents, dfs_num, dfs_low, count);
            result.insert(result.end(), tmp.begin(), tmp.end());
            if (dfs_low[graph[i][j]] >= dfs_num[i])
                articulation_point = true;
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
            result.push_back(i);
    }
    else {
        if (articulation_point)
            result.push_back(i);
    }           
    return result;
}

int main(){
    int n;
    while(true){
        cin >> n;
        if(n==0)
            break;
        vvi graph(n, vi());
        string s;
        // getline(cin, s);
        while(true){
            getline(cin, s);
            if (s[0] == '0')
                break;
            vi line;
            int i = 0;
            int j = 0;
            while(i < s.size()){
                while(j<s.size() && s[j] != ' ')
                    j++;
                int tmp = stoi(s.substr(i, (j-i))) - 1;
                line.push_back(tmp);
                i = j+1;
                j++;
            }
            FOR(i, 1, line.size()) {
                graph[line[0]].push_back(line[i]);
                graph[line[i]].push_back(line[0]);
            }
        }

        // Find articulation points.
        vi parents(n, -1);
        parents[0] = 0; // Used for the special case of the root.
        vi dfs_num(n, -1);
        vi dfs_low(n, -1);
        int count = 0;
        vi articulation_points = find_articulation_points(
            0, graph, parents, dfs_num, dfs_low, count);
        cout << articulation_points.size() << endl;
        VECT(dfs_num);
        VECT(dfs_low);
        VECT(articulation_points);
    }
    return 0;
}