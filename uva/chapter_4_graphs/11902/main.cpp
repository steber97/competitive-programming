#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

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


void dfs(int node, vvi& adjmat, vb& visited, int taboo=-1){
    visited[node]=true;
    FOR(i,0,visited.size()){
        if ((adjmat[node][i] == 1) && (!visited[i]) && (taboo!=i))
            dfs(i, adjmat, visited, taboo);
    }
}


int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n;
        cin >> n;
        vvi adjmat(n, vi(n));
        FOR(i,0,n)
            FOR(j,0,n)
                cin >> adjmat[i][j];
        
        vb reachable(n, false);
        dfs(0, adjmat, reachable);
        cout << "Case " << t << ":" << endl;
        cout << "+";
        FOR(i,0,2*n-1){
            cout << "-";
        }
        cout << "+" << endl;
        FOR(i,0,n){
            vb reachable2(n, false);
            if(i!=0){
                dfs(0, adjmat, reachable2, i);
            }
            VECT(reachable2);
            cout << "|";
            FOR(j,0,n){
                if ((reachable[j] && !reachable2[j]))
                    cout << "Y";
                else
                    cout << "N";
                cout << "|";
            }
            cout << endl;
            cout << "+";
            FOR(i,0,2*n-1){
                cout << "-";
            }
            cout << "+" << endl;

        }
        
    }
    return 0;    
}