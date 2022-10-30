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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<double>> vvd;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

#define IMP INT32_MAX-1
#define MAX MAXFLOAT


double fatina(int i, bitset<13> visited, vvd& dp, vi& disks, vd& earn, vvd& dists){
    if (visited.count() == 13){
        // it is included the zeroth vertex, the guy's house.
        int end = 0;
        int begin = (i==0?0:disks[i-1]);
        double earning = 0.0;
        if (begin != 0){
            earning = earn[i-1];
        }
        return dists[begin][end] - earning;
    }
    if (dp[i][visited.to_ulong()] != MAXFLOAT)
        return dp[i][visited.to_ulong()];
    double res=MAXFLOAT;
    // VALUE(visited);
    FOR(j,0,disks.size()+1){
        if (!visited[j]){
            visited[j] = 1;
            int begin = (i==0?0:disks[i-1]);
            int end = disks[j-1];
            double tmp = fatina(j, visited, dp, disks, earn, dists) + dists[begin][end];
            if (i!=0)   
                tmp -= earn[i-1];
            if(tmp < res)
                res = tmp;
            visited[j] = 0;
        }
    }
    dp[i][visited.to_ulong()] = res;
    return res;
}

int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n,m;
        cin >> n >> m;
        
        vvd dists(n+1,vd(n+1, MAXFLOAT));
        FOR(i,0,m){
            int s,e;
            double w;
            cin >> s >> e >> w;
            dists[s][e] = min(dists[s][e], w);
            dists[e][s] = min(dists[e][s], w);
            dists[s][s] = 0.0;
            dists[e][e] = 0.0;
        }

        // DO FLOYD WARSHALL algo for all pair min dist O(n^3)
        FOR(k,0,n+1){
            FOR(s,0,n+1){
                FOR(e,0,n+1){
                    if ((dists[s][k] < (MAXFLOAT - DELTA)) && (dists[k][e] < (MAXFLOAT - DELTA)))
                        dists[s][e] = min(dists[s][e], dists[s][k]+dists[k][e]);
                    if ((dists[s][k] < (MAXFLOAT - DELTA)) && (dists[k][e] < (MAXFLOAT - DELTA)))
                        dists[e][s] = min(dists[e][s], dists[e][k]+dists[k][s]);
                }
            }
        }
        int p;
        cin >> p;
        vi disks(p);
        vd earn(p);
        FOR(i,0,p)
            cin >> disks[i] >> earn[i];
        
        vvd dp(p+1, vd(pow(2,14), MAXFLOAT));
        bitset<13> visited(0);
        double res = MAXFLOAT;
        FOR(i,0,pow(2,p)){
            visited = bitset<13>(i << 1);
            //visited[i] = 1;
            visited[0] = 1;
            FOR(j,p+1,13){
                visited[j]=1;
            }
            double gain = fatina(0, visited, dp, disks, earn, dists);
            res = min(gain, res);
        }
        if (abs(res) > DELTA)
            cout << "Daniel can save $" << fixed << setprecision(2) << -res << endl;
        else
            cout << "Don't leave the house" << endl;
    }
    return 0;
}