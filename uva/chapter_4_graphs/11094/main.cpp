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


int dfs(vvc& grid, vvi& visited, int y, int x, char land){
   //  COUT(y); COUT(" "); COUT(x); COUT(endl);
    int res = 1;
    FOR(i,-1,2){
        FOR(j,-1,2){
            if (((i==0) || (j==0)) && ((i!=0) || (j!=0)))
            if (((i+y) >= 0) && ((i+y)<grid.size())){
                int posx = x+j;
                if (posx < 0)
                    posx = grid[0].size()-1;
                else if (posx == grid[0].size())
                    posx = 0;
                if ((grid[i+y][posx]==land) && (visited[i+y][posx] == -1)){
                    visited[i+y][posx] = visited[y][x];
                    res += dfs(grid, visited, y+i, posx, land);
                }
            }
        }
    }
    return res;
}


int main(){  
    int n,m;
    while(cin >> n >> m){
        vvc grid(n, vc(m));
        FOR(i,0,n)
            FOR(j,0,m)
                cin >> grid[i][j];
        int a,b;
        cin >> a >> b;
        vvi visited(n, vi(m, -1));
        visited[a][b] = 0;
        char land = grid[a][b];
        int res1 = dfs(grid, visited, a, b, land);
        // VALUE(res1);
        int res = 0;
        int counter = 1;
        FOR(i,0,n){
            FOR(j,0,m){
                if ((visited[i][j] == -1) && (grid[i][j]==land)){
                    visited[i][j] = counter++;
                    int res2 = dfs(grid, visited, i, j, land);
                    res = max(res, res2);
                }
            }
        }
        if (counter != 1)
            cout << res << endl;
        else    
            cout << 0 << endl;
    }
    return 0;    
}