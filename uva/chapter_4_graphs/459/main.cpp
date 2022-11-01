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
typedef vector<vector<bool>> vvb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


void dfs(int node, vvi& graph, vb& visited){
    visited[node]=true;
    FOR(i,0,graph[node].size()){
        if (!visited[graph[node][i]])
            dfs(graph[node][i], graph, visited);
    }
}


int main(){
    int T;
    cin >> T;
    int t = 0;
    char maxchar;
    cin >> maxchar;
    while(t<T){
        VALUE(maxchar);
        vvi graph(maxchar-'A'+1, vi());
        string s;
        while(cin >> s){
            if (s.size()==2){
                graph[s[0]-'A'].push_back(s[1]-'A');
                graph[s[1]-'A'].push_back(s[0]-'A');
            }
            else{
                maxchar = s[0];
                break;
            }
        }

        int ccs = 0;
        vb visited(graph.size(), false);
        FOR(i,0,graph.size()){
            if (!visited[i]){
                ccs++;
                dfs(i, graph, visited);
            }
        }
        cout << ccs << endl;
        cout << (t!=T-1 ? "\n" : "");
        t++;
    
    }
    
    return 0;    
}