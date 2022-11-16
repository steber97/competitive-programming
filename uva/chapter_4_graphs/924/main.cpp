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
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int main(){
    int n;
    cin >> n;
    vvi graph(n,vi());

    FOR(i,0,n){
        int t; cin >> t;
        FOR(j,0,t){
            int a; cin >> a;
            graph[i].push_back(a);
        }
    }

    int T; cin >> T;
    FOR(t,0,T){
        int start; cin >> start;

        queue<int> q;
        q.push(start);
        vi visited(n, -1);
        visited[start] = 0;
        vi visited_by_count(n, 0);
        visited_by_count[0] = -1;
        while(!q.empty()){
            int i = q.front(); q.pop();
            visited_by_count[visited[i]]++;
            FOR(j,0,graph[i].size()){
                if (visited[graph[i][j]] == -1){
                    q.push(graph[i][j]);
                    visited[graph[i][j]] = visited[i]+1;
                }
            }
        }
        int best = 0;
        FOR(i,1,n){
            if (visited_by_count[i] > visited_by_count[best]){
                best = i;
            }
        }
        if (best == 0)
            cout << 0 <<endl;
        else
            cout << visited_by_count[best] << " " << best << endl;
    }
    return 0;
}