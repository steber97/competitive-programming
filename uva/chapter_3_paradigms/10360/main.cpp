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
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int sum_rats(const vvi& grid, int y1, int x1, int y2, int x2){
    int sum = grid[y2][x2];
    if (y1 > 0 && x1 > 0)
        sum -= grid[y1-1][x1-1];
    if (y1 > 0)
        sum -= sum_rats(grid, 0, x1, y1-1, x2);
    if (x1 > 0)
        sum -= sum_rats(grid, y1, 0, y2, x1-1);
    return sum;
}

int main(){
    int T;
    cin >> T;
    int SIZE = 1025;
    FOR(t,0,T){
        int d, n;
        cin >> d >> n;
        vector<vector<int>> grid(SIZE, vector<int>(SIZE, 0));
        vector<vector<int>> sum_grid(SIZE, vector<int>(SIZE, 0));
        vector<vector<int>> rats(n, vector<int>(3));
        
        FOR(i,0,n){
            cin >> rats[i][0] >> rats[i][1] >> rats[i][2];
            grid[rats[i][0]][rats[i][1]] = rats[i][2];
        }
        
        FOR(i,0,SIZE){
            FOR(j,0,SIZE){
                sum_grid[i][j] = grid[i][j];
                if (i>0 && j>0)
                    sum_grid[i][j] += sum_grid[i-1][j-1];
                if (i>0)
                    sum_grid[i][j] += sum_grid[i-1][j] - (j>0 ? sum_grid[i-1][j-1] : 0);
                if (j>0)
                    sum_grid[i][j] += sum_grid[i][j-1] - (i>0 ? sum_grid[i-1][j-1] : 0);
            }
        }


        int besty, bestx, rats_k=0;
        FOR(i,0,SIZE){
            FOR(j,0,SIZE){
                int tmp = sum_rats(sum_grid, i-d > 0 ? i-d : 0, j-d > 0 ? j-d : 0, i+d < SIZE ? i+d : SIZE-1, j+d < SIZE ? j+d : SIZE-1);
                if (tmp > rats_k){
                    besty = i;
                    bestx = j;
                    rats_k = tmp;
                }
            }
        }
        // cout << sum_rats(sum_grid, 5-d, 5-d, 5+d, 5+d) << endl;
        cout << besty << " " << bestx << " " << rats_k << endl;
    }
    return 0;
}