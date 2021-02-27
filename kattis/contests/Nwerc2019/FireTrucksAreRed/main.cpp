#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
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


int main(){
    
    int n;
    cin >> n;

    unordered_map<int, vector<int>> edges;
    vvi numbers(n, vi());

    FOR(i,0,n){
        int m;
        cin >> m;
        numbers[i].resize(m);
        FOR(j,0,m){
            cin >> numbers[i][j];
            if (edges.find(numbers[i][j]) == edges.end())
                edges[numbers[i][j]] = vi();
            edges[numbers[i][j]].push_back(i);
        }
    }

    queue<int> q;
    q.push(0);
    int countVis = 1;
    vb visited(n, false);
    vector<pair<int,int>> parent(n, {-1,-1});
    visited[0] = true;

    while(!q.empty() && countVis < n){
        int w = q.front();
        q.pop();
        for (int v: numbers[w]){
            for (int u: edges[v]){ 
                if (!visited[u]){
                    countVis ++;
                    visited[u] = true;
                    q.push(u);
                    parent[u] = {w, v};
                }
                if (countVis == n)
                    break;
            }
            if (countVis == n)
                break;
        }
    }

    if (countVis == n){
        FOR(i,1,n){
            cout << i+1 << " " << parent[i].first + 1 << " " << parent[i].second << endl;
        }
    }
    else {
        cout << "impossible" << endl;
    }
    return 0;
}