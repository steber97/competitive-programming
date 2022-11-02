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
typedef vector<vector<bool>> vvb;
typedef vector<vector<char>> vvc;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int move(vvc& grid, int i, int j, string& s, int k, int orient){
    
    if (k==s.size())
        return grid[i][j] == '*' ? 1 : 0;
    int res = 0;
    vii moves = {{-1,0}, {0,1}, {1,0}, {0, -1}};  // according north, east, south, west.
    if (grid[i][j] == '*'){
        res ++;
        grid[i][j] = '.';
    }
    if (s[k]=='D'){
        // turn right
        orient ++;
        orient = (orient == 4 ? 0 : orient);
    }
    else if (s[k]=='E'){
        // left
        orient --;
        orient = (orient == -1 ? 3 : orient);
    }
    else {
        // forward
        if(((i+moves[orient].first) >= 0) && ((i+moves[orient].first) < grid.size())){
            if (((j+moves[orient].second) >= 0) && ((j+moves[orient].second)<grid[0].size())){
                if (grid[i + moves[orient].first][j + moves[orient].second] != '#'){
                    i = i + moves[orient].first;
                    j = j + moves[orient].second;
                }
            }
        }
    }
    assert (orient >= 0);
    res += move(grid, i, j, s, k+1, orient);
    return res;
}

int main(){  
    int n,m,p;
    while(true){
        cin >> n >> m >> p;
        if (n==0)
            break;
        vvc grid(n, vc(m));
        ii initial;
        FOR(i,0,n){
            FOR(j,0,m){
                cin >> grid[i][j];  
                if ((grid[i][j] == 'N') || (grid[i][j] == 'S') || 
                        (grid[i][j] == 'L') || (grid[i][j] == 'O'))
                    initial = {i,j};
            }
        }
        string s;
        cin >> s;
        // north, east, south, west.
        int orient = (grid[initial.first][initial.second] == 'N' ? 0 : grid[initial.first][initial.second] == 'L' ? 1 : grid[initial.first][initial.second] == 'S' ? 2 : 3);
        grid[initial.first][initial.second] = '.';
        int res = move(grid, initial.first, initial.second, s, 0, orient);
        cout << res << endl;
    }
    return 0;    
}