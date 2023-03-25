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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001
#define INF 100


void euler_tour(int node, list<ii>& result, list<ii>::iterator& iter, vector<pair<ii,bool>>& edges, vvi& graph) {
    // VALUE(node);
    FOR(i,0,graph[node].size()){
        int edge = graph[node][i];
        
        int other = edges[edge].first.first == node ? edges[edge].first.second : edges[edge].first.first;
        
        if (!edges[edge].second) {
            edges[edge].second = true;
            result.insert(iter, {node, other});
            list<ii>::iterator next = iter;
            next++;
            auto dist1 = distance(iter, result.begin());
            auto dist2 = distance(next, result.begin());
            // VALUE(dist1);VALUE(dist2);
            euler_tour(other, result, iter, edges, graph);
        }   
    }
}

int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        int n; cin >> n;
        vector<pair<ii, bool>> edges;
        vvi graph(50, vi());
        FOR(i,0,n){
            int a,b; 
            cin >> a >> b; 
            a--;b--;
            // VALUE(a); VALUE(b);
            edges.push_back({{a,b}, false});
            graph[a].push_back(i);
            graph[b].push_back(i);
        }
        bool alleven = true;
        FOR(i,0,50){
            if ((graph[i].size() % 2) != 0) {
                alleven = false;
            }
        }
        bool printres = false;
        cout << "Case #" << t << endl;
        if (alleven) {
            int start = 0;
            FOR(i,0,50){
                if (graph[i].size()>0){
                    start = i;
                    break;
                }
            }

            list<ii> l;
            list<ii>::iterator it = l.begin();
            euler_tour(start, l, it, edges, graph);
            if (l.size() == edges.size()) {
                printres = true;
                for(list<ii>::iterator iter = l.begin(); iter!=l.end(); iter++){
                    cout << (*iter).first + 1 << " " << (*iter).second + 1 << endl;
                }
            }
        }
        if (!printres){
            cout << "some beads may be lost" << endl;
        }
        if (t!=T){
            cout << endl;
        }

    }
    return 0;
}
