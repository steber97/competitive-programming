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
                COUT(it);COUT(endl);
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
        if (f==INT32_MAX)
            f = 0;
    } while(f > 0);

    return totflow;
}


int main(){
    
    int T; cin >> T;
    FOR(t,1,T+1){
        int n, m; cin >> n >> m;
        vvi people(n, vi(m, 0));
        FOR(i,0,n){
            int k; cin >> k;
            FOR(j,0,k){
                int s; cin >> s; s--;
                people[i][s]++;
            }
        }

        // Network structure:
        int source = 0;
        // one: initial sticker quantity for bob
        // two: people[i][j] intake
        // three: people[i][j] intake with capacity 1 or 0 (if people[i][j] is already > 0)
        // four: people out
        // five: people out (with capacity people[i][j]-1)
        // six: stickers out
        // seven: target

        vi one(m, 0);
        FOR(j,0,m)
            one[j] = j+1;

        vvi two(n, vi(m));
        FOR(i,1,n){
            FOR(j,0,m){
                two[i][j] = *(one.end()-1) + 1 + (i-1)*m + j;
            }
        }

        vvi three(n, vi(m));
        FOR(i,1,n){
            FOR(j,0,m){
                three[i][j] = *((*(two.end()-1)).end()-1) + 1 + (i-1)*m + j;
            }
        }

        vvi four(n, vi(m));
        FOR(i,1,n){
            FOR(j,0,m){
                four[i][j] = *((*(three.end()-1)).end()-1) + 1 + (i-1)*m + j;
            }
        }

        vvi five(n, vi(m));
        FOR(i,1,n){
            FOR(j,0,m){
                five[i][j] = *((*(four.end()-1)).end()-1) + 1 + (i-1)*m + j;
            }
        }

        vi six(m);
        FOR(j,0,m)
            six[j] =  *((*(five.end()-1)).end()-1) + 1 + j;

        int target = *(six.end()-1)  + 1;
        VALUE(target);

        vvii graph(target+1, vii());
        FOR(j,0,m){
            graph[source].push_back({one[j], people[0][j]});
            graph[one[j]].push_back({source, 0});
        }

        FOR(j,0,m){
            graph[one[j]].push_back({six[j], people[0][j]});
            graph[six[j]].push_back({one[j], 0});
        }

        FOR(i,1,n){
            FOR(j,0,m){
                graph[one[j]].push_back({two[i][j], 1});
                graph[two[i][j]].push_back({one[j], 0});
            }
        }

        FOR(i,1,n){
            FOR(j,0,m){
                graph[two[i][j]].push_back({three[i][j], (people[i][j] == 0? 1 : 0)});
                graph[three[i][j]].push_back({two[i][j], 0});
            }
        }

        FOR(i,1,n){
            FOR(k,0,m){
                FOR(j,0,m){
                    if (k!=j){
                        graph[three[i][k]].push_back({four[i][j], 1});
                        graph[four[i][k]].push_back({three[i][j], 0});
                    }
                }
            }
        }

        FOR(i,1,n){
            FOR(j,0,m){
                graph[four[i][j]].push_back({five[i][j], max(0, people[i][j]-1)});
                graph[five[i][j]].push_back({four[i][j], 0});
            }
        }

        FOR(i,1,n){
            FOR(l,1,n){
                if (i!=l){
                    FOR(j,0,m){
                        graph[five[i][j]].push_back({two[l][j], 1});
                        graph[two[l][j]].push_back({five[i][j], 0});                        
                    }
                }
            }
        }

        FOR(i,1,n){
            FOR(j,0,m){
                graph[five[i][j]].push_back({six[j], 1});
                graph[six[j]].push_back({five[i][j], 0});
            }
        }

        FOR(j,0,m){
            graph[six[j]].push_back({target, 1});
            graph[target].push_back({six[j], 0});
        }

        int flow = edmondskarp(graph, source, target);
        cout << "Case #" << t << ": " << flow << endl;
        
    }
    return 0;
}