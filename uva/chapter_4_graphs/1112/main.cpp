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
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

class Compare{
    public:
    bool operator() (ii a, ii b) {
        return a.second > b.second;
    }
};

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        if (t != 0)
            cout << endl;
        int n, exit, time;
        cin >> n >> exit >> time;
        exit--;
        int m; cin >> m;
        VALUE(m);
        vector<vii> graph(n, vii());
        FOR(i,0,m){
            int a,b,c; cin >> a >> b >> c;
            a--; b--;
            VALUE(a); VALUE(b);
            graph[a].push_back({b,c});
        }
        int counter = 0;
        FOR(i,0,n){
            vi costs(n, INT32_MAX);
            priority_queue<ii, vector<ii>, Compare> pq;
            pq.push({i, 0});
            costs[i] = 0;
            while(!pq.empty()){
                int node = pq.top().first; 
                int cost = pq.top().second;
                pq.pop();
                COUT(node); COUT(" "); COUT(cost); COUT(" "); COUT(costs[node]); COUT(endl);
                if (node == exit){
                    break;
                }
                if (cost == costs[node]){
                    VALUE(graph[node].size());
                    FOR(j,0,graph[node].size()){
                        COUT(graph[node][j].first); COUT(endl);
                        if ((cost + graph[node][j].second) < costs[graph[node][j].first]){
                            pq.push({graph[node][j].first, cost + graph[node][j].second});
                            costs[graph[node][j].first] = cost + graph[node][j].second;
                        }
                    }
                }
            }

            if (costs[exit] <= time)
                counter++;
        }
        cout << counter << endl;
    }
    return 0;
}