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
typedef vector<double> vd;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vd> vvd;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vi split(string& s, char sep) {
    int j = 0;
    int prevend = 0;
    vi result;
    while(prevend < s.size()){
        while(j < s.size() && s[j] != sep)
            j++;
        int num = stoi(s.substr(prevend, j - prevend));
        result.push_back(num);
        prevend = j+1;
        j++;
    }
    return result;
}


unordered_set<int> closure(vvi& graph, int start, int end){
    queue<int> q;
    vi distances(graph.size(), INT32_MAX);
    distances[start] = 0;
    q.push(start);
    vvi parents(graph.size(), vi());

    while(!q.empty()){
        int node = q.front(); q.pop();
        FOR(i,0,graph[node].size()){
            int neigh = graph[node][i];
            if (distances[neigh] > distances[node] + 1){
                distances[neigh] = distances[node]+1;
                q.push(neigh);
                parents[neigh].push_back(node);
            }
            else if (distances[neigh]==distances[node]+1){
                parents[neigh].push_back(node);
            }
        }
    }
    assert(q.empty());
    q.push(end);
    vb visited(graph.size(), false);
    visited[end] = true;
    unordered_set<int> result;
    while(!q.empty()){
        int node = q.front(); q.pop();
        result.insert(node);
        FOR(j,0,parents[node].size()){
            int neigh = parents[node][j];
            if (!visited[neigh]){
                visited[neigh] =1;
                q.push(neigh);
            }
        }
    }
    VALUE(start);VALUE(end);
    for(int t:result){
        COUT(t); COUT("\t");
    }COUT(endl);
    return result;
}


int main(){
    
    string sn; getline(cin, sn);
    int n = stoi(sn);
    vvi graph(n, vi());
    FOR(i,0,n){
        string s; getline(cin, s);
        vi l = split(s, ' ');
        FOR(j,0,l.size())
            l[j]--;
        graph[i]=l;
    }
    getline(cin, sn); 
    int m = stoi(sn);
    FOR(i,0,m){
        string s; getline(cin, s);
        vi l = split(s, ' ');
        FOR(j,0,l.size())
            l[j]--;

        unordered_set<int> geodeticset;
        FOR(start,0,l.size()){
            FOR(end,start+1,l.size()){
                vi distances(n, INT32_MAX);
                distances[l[start]] = 0;
                unordered_set<int> p = closure(graph, l[start], l[end]);
                for(int t: p)
                    geodeticset.insert(t);
            }
        }
        cout << (geodeticset.size()==n ? "yes" : "no") << endl;
    }
    return 0;
}