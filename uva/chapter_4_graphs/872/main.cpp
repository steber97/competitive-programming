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
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi topsort(int n, vvi& graph, vi& indeg, vb& visited, int missing){
    vvi res;
    if (missing == 1){
        res = {{n}};
    }
    else{
        FOR(i,0,graph.size()){
            if (!visited[i] && indeg[i]==0){
                visited[i] = 1;
                FOR(j,0,graph[i].size()){
                    indeg[graph[i][j]]--;
                }
                vvi tmp = topsort(i, graph, indeg, visited, missing-1);
                if(tmp.size() > 0){
                    FOR(j,0,tmp.size()){
                        assert((*(tmp[j].end()-1)) == i);
                        tmp[j].push_back(n);
                    }
                    res.insert(res.end(), tmp.begin(), tmp.end());
                }
                visited[i] = 0;
                FOR(j,0,graph[i].size()){
                    indeg[graph[i][j]]++;
                }
            }
        }
    }
    return res;
}


int main(){
    
    int T;
    cin >> T;
    string tmp;
    getline(cin, tmp);  // Do not know why tbh
    FOR(t,0,T){
        string l1, l2, l3;
        getline(cin, l1);
        getline(cin, l2);
        getline(cin, l3);
        // cout << l1 << endl << l2 << endl << l3 << endl;
        unordered_map<char, int> graphmap;
        vector<char> backmap;
        int counter = 0;
        FOR(i,0,l2.size()){
            if (l2[i]!=' '){
                graphmap[l2[i]] = counter++;
                backmap.push_back(l2[i]);
            }
        }
        vvi graph(counter, vi());
        vi indeg(counter, 0);
        vb visited(counter, false);
        for(int i = 0; i < l3.size(); i+=4){
            char c1 = l3[i], c2 = l3[i+2];
            graph[graphmap[c1]].push_back(graphmap[c2]);
            indeg[graphmap[c2]]++;
        }
        vvi res;
        FOR(i,0,counter){
            if (indeg[i] == 0){
                visited[i] = 1;
                FOR(j,0,graph[i].size())
                    indeg[graph[i][j]]--;
                vvi tmp = topsort(i, graph, indeg, visited, counter);
                res.insert(res.end(), tmp.begin(), tmp.end());
                visited[i] = 0;
                FOR(j,0,graph[i].size())
                    indeg[graph[i][j]]++;
                
            }
        }
        vector<string> res_str;
        FOR(i,0,res.size()){
            reverse(res[i].begin(), res[i].end());
            vector<char> res_char(res[i].size());

            FOR(j,0,res[i].size())
                res_char[j] = backmap[res[i][j]];
            
            string tmp(res_char.begin(), res_char.end());
            
            res_str.push_back(tmp);
        }
        sort(res_str.begin(), res_str.end());
        FOR(i,0,res_str.size()){
            FOR(j,0,res_str[i].size()){
                cout << res_str[i][j] << ((j != (res_str[i].size()-1))? " " : "");
            }
            cout << endl;
        }
        if (res_str.size() == 0)
            cout << "NO" << endl;
        if (t != T-1)
            cout << endl;
    }
    return 0;
}