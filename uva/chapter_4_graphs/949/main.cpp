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
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int main(){
    int n,m;
    cin >> m >> n;
    int r; cin >> r;
    vvi prohibited(n*m, vi(m));
    FOR(i,0,r) {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        prohibited[b*m + a].push_back(d*m + c);
        // prohibited[c*m + d].push_back(a*m + b);
    }

    int cameranum; cin >> cameranum;
    vi t(501);
    FOR(i,0,cameranum){
        int tmp3, tmp1, tmp2;
        cin >> tmp1 >> tmp2 >> tmp3;
        t[tmp1] = tmp3 * m + tmp2;
    }

    vvi graph(n*m, vi());
    FOR(i,0,n){
        FOR(j,0,m){
            FOR(k,-1,2){
                FOR(l,-1,2){
                    if ((i+k >= 0) && (i+k < n) && (j+l >= 0) && (j+l < m) && 
                            (k==0 || l==0) && (k!=0 || l!=0)){
                        bool proh = false;
                        FOR(r,0,prohibited[i*m+j].size()){
                            if (prohibited[i*m+j][r] == ((i+k) * m + (j+l))){
                                proh=true;
                                break;
                            }
                        }
                        if (!proh){
                            graph[i*m+j].push_back((i+k)*m + (j+l));
                        }
                    }
                }
            }
        }
    }

    queue<int> q;
    q.push(0);
    vi visited(n*m, -1);
    visited[0] == 0;
    while(!q.empty()){
        int node = q.front(); q.pop();
        if ((visited[node] <= 500) && (t[visited[node]] == node)){
            q.push(node);
            visited[node]++;
        }
        else if (node == (n*m -1)){
            cout << visited[node] << endl;
            break;
        }
        else {
            FOR(j,0,graph[node].size()){
                if(visited[graph[node][j]] == -1){
                    q.push(graph[node][j]);
                    visited[graph[node][j]] = visited[node] + 1;
                }
            }
        }
    }


    return 0;
}