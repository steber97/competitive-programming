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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<char>> vvc;
typedef vector<vector<bool>> vvb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


bool dfs(int i, int j, vvc& grid, vvi& visited){
    int res = false;
    if (grid[i][j] == 'x')
        res = true;
    
    FOR(k,-1,2){
        FOR(l,-1,2){
            if (((k==0) || (l==0)) && ((k!=0) || (l!=0))){
                if (((i+k) >= 0) && ((i+k) < grid.size())){
                    if (((j+l) >= 0) && ((j+l) < grid.size())){
                        if ((visited[i+k][j+l] == -1) && (grid[i+k][j+l] != '.')){
                            visited[i+k][j+l] = visited[i][j];
                            res |= dfs(i+k, j+l, grid, visited);
                        }
                    }
                }
            }
        }
    }
    return res;
}

int main(){  
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n;
        cin >> n;
        int result = 0;
        vvc grid(n,vc(n));
        FOR(i,0,n){
            FOR(j,0,n){
                cin >> grid[i][j];
            }
        }

        vvi visited(n,vi(n,-1));
        int counter = 0;
        FOR(i,0,n){
            FOR(j,0,n){
                if((visited[i][j] == -1) && (grid[i][j] == 'x' || grid[i][j] == '@')){
                    visited[i][j] = counter++;
                    bool alive = dfs(i, j, grid, visited);
                    if (alive)
                        result ++;
                }
            }
        }
        cout << "Case " << t << ": " << result << endl;
    }
    return 0;    
}