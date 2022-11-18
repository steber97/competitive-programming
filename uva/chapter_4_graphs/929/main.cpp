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
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

class Compare{
public:
    bool operator() (tuple<ii, int> p1, tuple<ii, int> p2)
    {
        return get<1>(p1) > get<1>(p2);
    }
};


int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n,m;
        cin >> n >> m;
        vvi grid(n, vi(m));
        vvi costs(n, vi(m, INT32_MAX));
        FOR(i,0,n){
            FOR(j,0,m){
                cin >> grid[i][j];
            }
        }

        priority_queue<tuple<ii, int>, vector<tuple<ii, int>>, Compare> pq;
        pq.push({{0,0}, grid[0][0]});
        costs[0][0] = grid[0][0];

        while(!pq.empty()){
            tuple<ii, int> t = pq.top(); pq.pop();
            int i = get<0>(t).first, j = get<0>(t).second;
            PAIR(get<0>(t)); COUT(endl);
            if ((i==(n-1)) && (j==(m-1))){
                break;
            }
            int cost = get<1>(t);
            if (cost == costs[i][j]){
                FOR(k,-1,2){
                    FOR(l,-1,2){
                        if (((i+k) < n) && ((i+k) >=0) && ((j+l) < m) && ((j+l) >= 0)) {
                            if (((k==0) || (l == 0)) && ((k!=0) || (l!=0))) {
                                if (costs[i+k][j+l] > costs[i][j] + grid[i+k][j+l]){
                                    pq.push({{i+k, j+l}, costs[i][j] + grid[i+k][j+l]});
                                    costs[i+k][j+l] = costs[i][j] + grid[i+k][j+l];
                                }
                            }   
                        }
                    }
                }
            }
        }

        cout << costs[n-1][m-1] << endl;

    }
    return 0;
}