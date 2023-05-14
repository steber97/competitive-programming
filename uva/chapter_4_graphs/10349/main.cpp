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


int MCBM(vvi& graph,int source, int sink) {
    vvi adjmat(graph.size(), vi(graph.size(), 0));
    FOR(i,0,graph.size()){
        FOR(j,0,graph[i].size()){
            adjmat[i][graph[i][j]] = 1;
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
    return result;
}


int main(){
    int T ; cin >> T;
    FOR(t,1,T+1){
        int h,w; cin >> h >> w;
        vvi matnode(h, vi(w));
        vvc mat(h, vc(w));
        vvi graph(w*h+2, vi());
        int counter=0;
        int source = 0, sink = w*h+1;
        int places = 0;
        FOR(i,0,h){
            FOR(j,0,w){
                cin >> mat[i][j];
                matnode[i][j] = ++counter;
            }
        }

        FOR(i,0,h){
            FOR(j,0,w){
                if (mat[i][j]=='*'){
                    places++;
                    if ((i+j)%2==0){
                        graph[source].push_back(matnode[i][j]);
                        FOR(l,-1,2){
                            FOR(k,-1,2){
                                if (l!=0 || k!=0){
                                    if ((i+l>=0) && (i+l < h) && (j+k >=0) && (j+k<w)) {
                                        if (mat[i+l][j+k] == '*'){
                                            graph[matnode[i][j]].push_back(matnode[i+l][k+j]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else{
                        graph[matnode[i][j]].push_back(sink);
                    }
                }
            }
        }

        int mcbm = MCBM(graph, source, sink);

        cout << places - (mcbm*2) + mcbm << endl;
        
    }
    return 0;
}