#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<iii> viii;
typedef pair<double,double> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare{
    public:
    bool operator() (ii p1, ii p2){
        return p1.second > p2.second;
    }
};

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        vvii graph(n, vii());
        FOR(i,0,m){
            int a,b,c;
            cin >> a >> b >> c;
            graph[a].push_back({b,c});
        }

        vb visited(n, false);
        vi distances(n, INT32_MAX);
        priority_queue<ii, vii, Compare> pq;
        pq.push({0,0});
        distances[0] = 0;
        bool negative_cycles = false;
        while(!pq.empty()){
            int node = pq.top().first;
            int dist = pq.top().second;
            pq.pop();
            visited[node] = true;
            if (dist == distances[node]){
                FOR(j,0,graph[node].size()){
                    int neigh = graph[node][j].first;
                    int time = graph[node][j].second;
                    if (visited[neigh]){
                        if(distances[neigh] > time + dist){
                            negative_cycles = true;
                            break;
                        }
                    }
                    else{
                        if (distances[neigh] > time+dist){
                            distances[neigh] = time+dist;
                            pq.push({neigh, time+dist});
                        }
                    }
                }
            }
        }

        cout << (negative_cycles?"possible":"not possible") << endl;
    }
    return 0;
}