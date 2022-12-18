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


int edmondskarp(vvii& graph, int source, int target) {
    int n = graph.size();
    vvi adjmat(n, vi(n, 0));
    FOR(i,0,n){
        FOR(j,0,graph[i].size()){
            adjmat[i][graph[i][j].first] += graph[i][j].second; 
        }
    }
    
    int f = 0, totflow = 0;
    do {
        f=0;
        queue<int> q;
        q.push(source);
        vi parents(n, -1);
        parents[source] = source;
        while(!q.empty()){
            int node = q.front(); q.pop();
            if (node == target)
                break;
            FOR(j,0,graph[node].size()){
                int nei = graph[node][j].first;
                if ((parents[nei] == -1) && (adjmat[node][nei] > 0)){
                    q.push(nei);
                    parents[nei] = node;
                }
            }
        }
        f = INT32_MAX;
        if(parents[target] != -1){
            int it = target;
            while(parents[it] != it){
                // COUT(it);COUT(endl);
                f = min(f, adjmat[parents[it]][it]);
                it = parents[it];
            }
            // COUT(endl);
            it = target;
            totflow += f;
            while(parents[it] != it){
                adjmat[parents[it]][it] -= f;
                adjmat[it][parents[it]] += f;
                it = parents[it];
            }
        }
        if (f==INT32_MAX)
            f = 0;
    } while(f > 0);

    return totflow;
}

double dist(dd p1, dd p2){
    return sqrt( pow(p1.first-p2.first, 2) + pow(p1.second-p2.second, 2));
}


int main(){
    int T; cin >> T;
    FOR(t,1,T+1){
        int n; double d; cin >> n >> d;
        int totp=0;
        vdd ice(n); vi penguins(n); vi broke(n);
        FOR(i,0,n){
            double x,y; int p,b; cin >> x >> y >> p >> b;
            ice[i]={x,y};
            penguins[i]=p;
            broke[i]=b;
            totp+=p;
        }

        vvii graph(n*2 + 2, vii());
        int source = n*2; int target = n*2+1;
        FOR(i,0,n){
            FOR(j,i+1,n){
                if ((d >= dist(ice[i], ice[j])) || (abs(d - dist(ice[i],ice[j])) < DELTA)){
                    graph[i+n].push_back({j, INT32_MAX});
                    graph[j].push_back({i+n, 0});
                    graph[j+n].push_back({i, INT32_MAX});
                    graph[i].push_back({j+n, 0});
                }
            }
        }

        FOR(i,0,n){
            graph[i].push_back({i+n, broke[i]});
            graph[i+n].push_back({i, 0});
            graph[source].push_back({i, penguins[i]});
            graph[i].push_back({source, 0});
        }

        vi result;
        FOR(i,0,n){
            vii v1c(graph[i]);
            vii v2c(graph[target]);
            graph[i].push_back({target, INT32_MAX});
            graph[target].push_back({i, 0});

            FOR(j,0,graph[i].size()){
                COUT(graph[i][j].first); COUT(" ");
            }COUT(endl);

            int flow = edmondskarp(graph, source, target);
            if (flow==totp)
                result.push_back(i);

            graph[i]=v1c;
            graph[target]=v2c;
        }

        FOR(i,0,result.size())
            cout << result[i] << (i!=result.size()-1?" ":"");
        if (result.size()==0)
            cout << -1;
        cout << endl;
    }
    return 0;
}
