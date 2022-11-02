#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
typedef vector<vector<bool>> vvb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

auto myhash = [](const ii& v) {
        std::hash<int> hasher;
        size_t seed = 0;
        seed ^= v.first;
        seed ^= v.second << 4;
        return seed;
    };

auto myequal = [](const ii& v1, const ii& v2){
        return (v1.first == v2.first) && (v1.second == v2.second);
    };


ii dfs(int i, int j, vvb& water, int r, int c, int m, int n, vvb& visited){
    int neigh = 0;
    ii res = {0,0};

    unordered_set<ii, decltype(myhash), decltype(myequal)> moves (0, myhash, myequal);
    vii movesv = {{m,n}, {m,-n}, {-m,n}, {-m,-n}, {n,m}, {n,-m}, {-n,m}, {-n,-m}};
    for(ii mv: movesv)
        moves.insert(mv);
        
    for(ii p: moves){
        if (((i+p.first) >= 0) && ((i+p.first) < r)){
            if (((j+p.second) >= 0) && ((j+p.second) < c)){
                if (!water[i+p.first][j+p.second]){
                    neigh++;
                    if(!visited[i+p.first][j+p.second]){
                        visited[i+p.first][j+p.second]=true;
                        ii tmp = dfs(i+p.first, j+p.second, water, r, c, m, n, visited);
                        res.first += tmp.first;
                        res.second += tmp.second;
                    }
                }
            }   
        }
    }
    if ((neigh%2)==0)
        res.first += 1;
    else
        res.second += 1;
    return res;
}


int main(){  
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n,m,r,c;
        cin >> r >> c >> n >> m;
        int w;
        cin >> w;
        vvb water(r, vb(c, false));
        FOR(i,0,w){
            int a,b;
            cin >> a >> b;
            water[a][b]=1;
        }  
        vvb visited(r,vb(c,false));
        visited[0][0]=true;
        ii res = dfs(0,0, water, r, c, m, n, visited);
        cout << "Case " << t << ": " << res.first << " " << res.second << endl;
    }
    return 0;    
}