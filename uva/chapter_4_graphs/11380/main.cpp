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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<pair<int,ll>> vill;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<pair<ll,ll>> vllll;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<vector<pair<int,ll>>> vvill;
typedef vector<vllll> vvllll;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001



int edmondskarp(vvii& graph, int source, int target) {
    int n = graph.size();
    vvi adjmat(n, vi(n, 0));
    vii result;
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
                COUT(it);COUT(endl);
                if (f > adjmat[parents[it]][it]){
                    f = adjmat[parents[it]][it];
                }
                f = min(f, adjmat[parents[it]][it]);
                it = parents[it];
            }
            COUT(endl);
            it = target;
            totflow += f;
            while(parents[it] != it){
                adjmat[parents[it]][it] -= f;
                adjmat[it][parents[it]] += f;
                it = parents[it];
            }
        }
        else{
            unordered_set<int> bipartition;
            FOR(i,0,graph.size()){
                if (parents[i]!=-1)
                    bipartition.insert(i);
            }
            FOR(i,0,graph.size()){
                FOR(j,0,graph[i].size()){
                    if (bipartition.find(i)!=bipartition.end() && bipartition.find(graph[i][j].first) == bipartition.end() && graph[i][j].second > 0)
                        result.push_back({i,graph[i][j].first});
                }
            }

        }
        if (f==INT32_MAX)
            f = 0;
    } while(f > 0);

    return totflow;
}


vi split(string& s, char sep) {
    int j = 0;
    int prevend = 0;
    vi result;
    while(prevend < s.size()){
        while(j < s.size() && s[j] != sep)
            j++;
        int num = stoi(s.substr(prevend, j - prevend));
        result.push_back(num);
        prevend = j+1;
        j++;
    }
    return result;
}


int main(){
    while(!cin.eof()){
        string l1; 
        getline(cin, l1);
        if (l1=="")
            break;
        vi l1i = split(l1, ' ');
        int n=l1i[0],m=l1i[1],p=l1i[2];
        vector<string> grid;
        FOR(i,0,n){
            string s;
            getline(cin,s);
            grid.push_back(s);
        }

        vvii graph(n*m*2 + 2, vii()); // source is n*m*2 and target is n*m*2+1;
        FOR(i,0,n){
            FOR(j,0,m){
                graph[i*m + j].push_back({
                    (i*m + j) + m*n,
                    (grid[i][j]=='.'? 1 : (grid[i][j] == '*' ? 1 : (grid[i][j] == '~' ? 0 : (grid[i][j] == '@' ? m*n*2 : (grid[i][j] == '#' ? m*n*2 : -1)))))});
                graph[(i*m+j)+m*n].push_back({i*m+j, 0});
                FOR(k,-1,2){
                    FOR(l,-1,2){
                        if (((k==0) || (l==0)) && ((k!=0) || (l!=0))){
                            if (((k+i)>=0) && ((k+i) < n)){
                                if (((l+j)>=0) && ((l+j) < m)){
                                    int nei = (i+k)*m + (j+l);
                                    graph[(i*m+j)+m*n].push_back({nei, n*m*2});
                                    graph[nei].push_back({(i*m+j)+m*n, 0});
                                }
                            }
                        }
                    }
                }
            }
        }   
        int source = m*n*2;
        int target = source +1;
        FOR(i,0,n){
            FOR(j,0,m){
                if (grid[i][j]=='*'){
                    graph[source].push_back({i*m+j, 1});
                    graph[i*m+j].push_back({source, 0});
                }
                if (grid[i][j] == '#'){
                    graph[i*m+j + m*n].push_back({target, p});
                    graph[target].push_back({i*m+j + m*n, 0});
                }
            }
        }

        int flow = edmondskarp(graph, source, target);
        cout << flow << endl;
        getline(cin, l1);
    }
    return 0;
}