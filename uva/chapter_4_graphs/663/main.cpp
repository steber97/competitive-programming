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


bool intersects(pair<ii,ii>sheet, ii number){
    return ((number.first >= sheet.first.first) && (number.first <= sheet.second.first) && 
            (number.second >= sheet.first.second) && (number.second <= sheet.second.second));
}

int edmondskarp(vvi& graph, ii& taboo, int source, int sink) {
    vvi adjmat(graph.size(), vi(graph.size(), 0));
    FOR(i,0,graph.size()){
        FOR(j,0,graph[i].size()){
            if (i != taboo.first || graph[i][j] != taboo.second){
                adjmat[i][graph[i][j]] = 1;
            }
        }
    }
    int result = 0;
    bool cancontinue = true;
    while(cancontinue){

        queue<int> q;
        vi parents(graph.size(), -1);
        q.push(0);
        while(!q.empty()){
            int node = q.front(); q.pop();
            // VALUE(node);
            if (node == sink){
                break;
            }
            FOR(j,0,graph.size()){
                if (adjmat[node][j] != 0){
                    if (parents[j]==-1){
                        parents[j]=node;
                        q.push(j);
                    }
                }
            }
        }

        if (parents[sink]==-1){
            cancontinue = false;
        } else {
            int iter = sink;
            while(iter != source) {
                int prev = parents[iter];
                adjmat[prev][iter] = 0;
                adjmat[iter][prev] = 1;
                iter = prev;
            }
            result++;
        }
    }
    VALUE(result);
    return result;
}


int main(){
    int T = 1;
    int n; cin >> n;
    while(n!=0){
        vector<pair<ii, ii>> sheets(n);
        vii numbers(n);
        FOR(i,0,n){
            int xmin,xmax,ymin,ymax; 
            cin >> xmin >> xmax >> ymin >> ymax;
            sheets[i] = {{xmin, ymin}, {xmax, ymax}};
        }
        FOR(i,0,n){
            int x,y; cin >> x >> y;
            numbers[i] = {x,y};
        }

        vvi graph(n*2 + 2, vi());
        int source = 0, sink = 2*n + 1;
        vii edges;
        FOR(i,0,n){
            graph[source].push_back(i+1);
            graph[n + i + 1].push_back(sink);
            FOR(j,0,n){
                if (intersects(sheets[i], numbers[j])){
                    graph[i+1].push_back(n+1+j);
                    edges.push_back({i+1, n+1+j});
                }
            }
        }

        FOR(i,0,graph.size()){
            COUT(i); COUT(" ");
            FOR(j,0,graph[i].size()) {
                COUT(graph[i][j]); COUT(" ");
            }
            COUT(endl);
        }
        vii result;
        for(auto taboo: edges){
            if (edmondskarp(graph, taboo, source, sink) != n){
                result.push_back({taboo.first - 1, taboo.second - n - 1});
            }
        }

        sort(result.begin(), result.end(), [](ii p1, ii p2){
            return p1.first < p2.first;
        });

        cout << "Heap " << T << endl;
        if (result.size() == 0){
            cout << "none" << endl;
        } else{
            FOR(i,0,result.size()){
                cout << "(" << char('A' + result[i].first) << "," << result[i].second+1 << ")" << (i!=result.size()-1 ? " ": "");
            }
            cout << endl;
        }
        cout << endl;


        cin >> n;
        T++;
    }
    return 0;
}