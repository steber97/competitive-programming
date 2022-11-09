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


vi topsort(int i, vvi& graph, vi& indeg, vb& visited){
    vi result = {i};
    visited[i] = true;
    FOR(j,0,graph[i].size())
        indeg[graph[i][j]]--;
    FOR(j,0,graph.size()){
        if (indeg[j]==0 && !visited[j]){
            vi tmp = topsort(j, graph, indeg, visited);
            result.insert(result.end(), tmp.begin(), tmp.end());
        }
    }
    return result;
}


int main(){
    
    int n,m;
    int t = 1;
    while(cin >> n) {
        vector<string> drinks(n);
        map<string, int> mapdrink;
        FOR(i,0,n){
            cin >> drinks[i];
            mapdrink[drinks[i]] = i;
        }
        vvi graph(n, vi());
        vi indeg(n, 0);
        cin >> m;
        FOR(i,0,m){
            string s1, s2;
            cin >> s1 >> s2;
            indeg[mapdrink[s2]]++;
            graph[mapdrink[s1]].push_back(mapdrink[s2]);
        }

        vb visited(n, false);
        vi result;
        FOR(i,0,n) {
            if (!visited[i] && indeg[i] == 0){
                vi tmp = topsort(i, graph, indeg, visited);
                result.insert(result.end(), tmp.begin(), tmp.end());
            }
        }
        cout << "Case #" << t << ": Dilbert should drink beverages in this order: ";
        FOR(i,0,n){
            cout << drinks[result[i]] << ((i!=(n-1))? " " : ".");
        }
        cout << endl << endl;
        t++;
    }    

    return 0;
}