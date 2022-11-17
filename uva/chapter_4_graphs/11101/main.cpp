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
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    while(true){
        int p1, p2;
        cin >> p1;
        if (p1 == 0)
            break;
        vvi grid(2001, vi(2001, INT32_MAX));
        queue<ii> q;
        FOR(i,0,p1){
            int a,b;
            cin >> a >> b;
            grid[b][a] = 0;
            q.push({b, a});
        }
        cin >> p2;
        FOR(i,0,p2){
            int a,b;
            cin >> a >> b;
            grid[b][a] = -1;
        }
        bool finish = false;
        while(!q.empty() && !finish){
            ii n = q.front(); q.pop();
            int i = n.first,j = n.second;
            // PAIR(n); COUT("\t"); VALUE(grid[i][j]);
            FOR(k,-1,2){
                FOR(l,-1,2){
                    if ((i+k >= 0) && (i+k < grid.size()) &&
                        (j+l >= 0) && (j+l < grid.size()) && 
                        (k==0 || l==0) && (k!=0 || l!=0)){
                        if (grid[i+k][j+l] == INT32_MAX){
                            q.push({i+k, j+l});
                            grid[i+k][j+l] = grid[i][j] + 1;
                        }
                        else if (grid[i+k][j+l] == -1) {
                            cout << grid[i][j]+1 << endl;
                            finish = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}