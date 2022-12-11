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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi edmondskarp(vvii& graph, int source, int target) {
    int n = graph.size();
    vvi adjmat(n, vi(n, 0));
    FOR(i,0,n){
        FOR(j,0,graph[i].size()){
            adjmat[i][graph[i][j].first] = graph[i][j].second; 
        }
    }
    
    int f = 0;
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
                f = min(f, adjmat[parents[it]][it]);
                it = parents[it];
            }
            it = target;
            while(parents[it] != it){
                adjmat[parents[it]][it] -= f;
                adjmat[it][parents[it]] += f;
                it = parents[it];
            }
        }
        if (f==INT32_MAX)
            f = 0;
    } while(f > 0);

    return adjmat;
}


int main(){
    string l;
    while(!cin.eof()){
        // 10 source, 11 target.
        vvii graph(12, vii());
        unordered_map<int,char> taskmap; 
        FOR(i,0,10){
            graph[10].push_back({i,1});
            graph[i].push_back({10,0});
        }
        do{
            getline(cin, l);
            if (l.size()!=0 && !cin.eof()){
                char task = l[0];
                
                int users = l[1] - '0';
                vi tasks;
                int i = 3;
                while(l[i] !=';'){
                    tasks.push_back(l[i]-'0');
                    i++;
                }
                FOR(j,0,users){
                    graph.push_back(vii());
                    taskmap[graph.size()-1] = task;
                    FOR(k,0,tasks.size()){
                        graph[tasks[k]].push_back({graph.size()-1, 1});
                        graph[graph.size()-1].push_back({tasks[k], 0});
                    }
                    graph[graph.size()-1].push_back({11, 1});
                    graph[11].push_back({graph.size()-1, 0});
                }
            }
        }while(l.size()!=0 && !cin.eof());
        // COUT("CASE");COUT(endl);
        // FOR(i,0,graph.size()){
        //     FOR(j,0,graph[i].size()){
        //         COUT(graph[i][j].first);COUT(" ");
        //     }
        //     COUT(endl);
        // }
        vvi flow = edmondskarp(graph, 10, 11);
        bool ok = true;
        vector<char> result;
        int assign = 0;
        FOR(i,0,10){
            char assignment = 'a';
            FOR(j,0,graph[i].size()){
                if ((graph[i][j].second > 0) && (flow[i][graph[i][j].first] == 0)){
                    assignment = taskmap[graph[i][j].first];
                }
            }
            if (assignment == 'a')
                result.push_back('_');
            else{
                result.push_back(assignment);
                assign++;
            }
        }
        if (assign == graph.size()-12){
            FOR(i,0,10)
                cout << result[i];
            cout << endl;
        }
        else{
            cout << "!" << endl;
        }
        
    }
    return 0;
}