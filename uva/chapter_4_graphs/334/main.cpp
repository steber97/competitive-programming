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



int main(){
    int chain; cin >> chain;
    int casenumber = 1;
    while(chain!=0){
        unordered_map<string, int> evmap;
        vector<string> revmap;
        vector<vector<string>> chains(chain, vector<string>());
        FOR(i,0,chain){
            int n; cin >> n;
            FOR(j,0,n){
                string e; cin >> e;
                int size = evmap.size();
                evmap[e] = size;
                revmap.push_back(e);
                chains[i].push_back(e);
            }
        }

        vector<vb> prec(evmap.size(), vb(evmap.size(), false));
        vvi graph(evmap.size(), vi());

        FOR(i,0,chain){
            FOR(j,0,chains[i].size()-1){
                graph[evmap[chains[i][j]]].push_back(evmap[chains[i][j+1]]);
            }
        }
        
        int cross; cin >> cross;
        FOR(i,0,cross){
            string s1, s2;
            cin >> s1 >> s2;
            graph[evmap[s1]].push_back(evmap[s2]);
        }

        FOR(i,0,graph.size()){
            queue<int> q;
            q.push(i);
            vb visited(graph.size(), false);
            visited[i] = true;
            while(!q.empty()) {
                int n = q.front(); q.pop();
                FOR(j,0,graph[n].size()){
                    if (!visited[graph[n][j]]){
                        visited[graph[n][j]] = 1;
                        q.push(graph[n][j]);
                    }
                }
            }
            prec[i] = visited;
        }

        // FOR(i,0,prec.size()){
        //     VECT(prec[i]);
        //     COUT(endl);
        // }
        // COUT("________\n");


        int counter = 0;
        vii p(2, {-1,-1});
        FOR(i,0,prec.size()){
            FOR(j,i+1,prec.size()){
                if (!prec[i][j] && !prec[j][i]){
                    counter++;
                    if (counter == 1){
                        p[0] = {i,j};
                    }
                    else if (counter == 2){
                        p[1] = {i,j};
                    }
                }
            }
        }

        cout << "Case " << casenumber << ", " << (counter>0?to_string(counter):"no")
                 << " concurrent events" << (counter>0?":":".") << endl;
        FOR(i,0,min(counter,2)){
            cout << "(" << revmap[p[i].first] << "," << revmap[p[i].second] << ")" << " ";
        }
        if (counter>0)
            cout << endl;
        casenumber++;
        cin >> chain;
    }
    return 0;
}