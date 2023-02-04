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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


pair<vi, vi> bfs(vvi& graph, int start) {
    queue<int> q;
    q.push(start);
    vi result(graph.size(), -1);
    vi parents(graph.size(), -1);
    result[start] = 0;
    parents[start] = start;
    while(!q.empty()){
        int n = q.front(); q.pop();
        FOR(j,0,graph[n].size()){
            if (result[graph[n][j]]==-1){
                result[graph[n][j]] = result[n] + 1;
                q.push(graph[n][j]);
                parents[graph[n][j]] = n;
            }
        }
    }
    return {result, parents};
}


int main(){

    while(!cin.eof()){
        int n; cin >> n;
        if (cin.eof())
            break;
        vvi graph(n, vi());
        FOR(i,0,n){
            int m; cin >> m;
            FOR(j,0,m){
                int nei; cin >> nei; nei--;
                graph[i].push_back(nei);
            }
        }

        int start = 0;
        
        auto [dist1, parents1] = bfs(graph, start);
        VECT(dist1);
        
        int maxi = 0;
        FOR(i,0,n){
            if (dist1[maxi] < dist1[i])
                maxi = i;
        }
        VALUE(maxi);

        auto [dist2, parents2] = bfs(graph, maxi);
        VECT(dist2);
        int diam = dist2[max_element(dist2.begin(), dist2.end()) - dist2.begin()];

        int max2 = max_element(dist2.begin(), dist2.end()) - dist2.begin();
        int root2 = max2;
        while((((diam%2) == 0) && (dist2[root2] != (diam/2))) || ((diam%2) == 1) && (dist2[root2] != ((diam/2)+1))){
            root2 = parents2[root2];
        }
        vi roots;
        unordered_set<int> leaves;
        
        roots.push_back(root2);
        if ((diam%2) == 1)
            roots.push_back(parents2[root2]);

        vi leavesv;
        for(int r : roots){
            auto [dist3, par3] = bfs(graph, r);
            int maxdist = dist3[max_element(dist3.begin(), dist3.end())-dist3.begin()];
            FOR(j,0,dist3.size()){
                if (dist3[j] == maxdist)
                    leaves.insert(j);
            }
        }


        for(int i: leaves)
            leavesv.push_back(i);
        sort(leavesv.begin(), leavesv.end());
        sort(roots.begin(), roots.end());

        cout << "Best Roots  : ";
        FOR(i,0,roots.size())
            cout << roots[i]+1 << (i!=roots.size()-1 ? " " : "") ;
        cout << endl;
        cout << "Worst Roots : ";
        FOR(i,0,leavesv.size())
            cout << leavesv[i]+1 << (i!=leavesv.size()-1 ? " " : "");
        cout << endl;

    }          
        
   
    return 0;
}
