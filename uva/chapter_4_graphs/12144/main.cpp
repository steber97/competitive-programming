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
    int n,m;
    cin >> n >> m;
    while(true){
        if (n==0)
            break;
        
        int start,end;
        cin >> start >> end;

        vector<iii> edges(m);
        vector<vector<iii>> graph(n, viii()); // neigh, cost, edgeid
        FOR(i,0,m){
            int a,b,c;
            cin >> a >> b >> c;
            edges[i] = {a,b,c};
            graph[a].push_back({b, c, i});
        }

        vvi parents(n, vi());
        parents[start] = {-1};
        vi distances(n, INT32_MAX);
        distances[start] = 0;
        priority_queue<ii, vii, Compare> pq;
        pq.push({start,0});
        while(!pq.empty()){
            int node,cost;
            node = pq.top().first;
            cost = pq.top().second;
            pq.pop();
            if (node == end)
                break;
            if(distances[node]==cost){
                FOR(j,0,graph[node].size()){
                    int neigh =get<0>(graph[node][j]);
                    int costneigh = get<1>(graph[node][j]);
                    int edgeid = get<2>(graph[node][j]);
                    if (distances[neigh] > cost + costneigh){
                        distances[neigh] = cost + costneigh;
                        pq.push({neigh, distances[neigh]});
                        parents[neigh] = {edgeid};
                    }
                    else if (distances[neigh] == cost + costneigh){
                        parents[neigh].push_back(edgeid);
                    }
                }
            }
        }
        vector<bool> present(m, false);

        stack<int> s; 
        s.push(end);

        while(!s.empty()){
            int node = s.top(); s.pop();
            if(parents[node].size()>0){
                if (parents[node][0] != -1){
                    FOR(j,0,parents[node].size()){
                        int edgeid = parents[node][j];
                        if (!present[edgeid]){
                            present[edgeid] = true;
                            s.push(get<0>(edges[edgeid]));
                        }
                    }
                }
            }
        }

        vector<vector<iii>> graph2(n, viii());
        FOR(i,0,m){
            if (!present[i]){
                graph2[get<0>(edges[i])].push_back({get<1>(edges[i]), get<2>(edges[i]), 0});
            }
        }
        VECT(present);
        FOR(i,0,n){
            FOR(j,0,graph2[i].size()){
                COUT(get<0>(graph2[i][j]));COUT(" ");COUT(get<1>(graph2[i][j]));COUT("\t");
            }
            COUT(endl);
        }
        // VECT(present);
        vi distances2(n, INT32_MAX);
        distances2[start] = 0;
        priority_queue<ii, vii, Compare> pq2;
        pq2.push({start,0});
        while(!pq2.empty()){
            int node,cost;
            node = pq2.top().first;
            cost = pq2.top().second;
            pq2.pop();
            if (node == end)
                break;
            if(distances2[node]==cost){
                FOR(j,0,graph2[node].size()){
                    int neigh =get<0>(graph2[node][j]);
                    int costneigh = get<1>(graph2[node][j]);
                    int edgeid = get<2>(graph2[node][j]);
                    if (distances2[neigh] > cost + costneigh){
                        distances2[neigh] = cost + costneigh;
                        pq2.push({neigh, distances2[neigh]});
                    }
                }
            }
        }
        
        cout << (distances2[end]!=INT32_MAX?distances2[end]:-1) << endl;

        cin >> n >> m;
    }
    return 0;
}