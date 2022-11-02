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
typedef vector<vector<bool>> vvb;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int dfs(int i, int j, vector<string>& graph, vvi& colors, int color){
    int counter = 1;
    colors[i][j]=color;
    
    FOR(k,-1,2){
        FOR(l,-1,2){
            if (((i+k)>=0) && ((i+k) < graph.size())){
                if (((j+l)>=0) && ((j+l) < graph[0].size())){
                    if ((colors[i+k][j+l] == -1) && (graph[i+k][j+l] == 'W'))
                        counter += dfs(i+k, j+l, graph, colors, color);
                }
            }
        }
    }

    return counter;
} 


int main(){  
    int T;
    cin >> T;
    vector<string> vs;
    string s;
    while(cin>>s){
        vs.push_back(s);
        // cout << *(vs.end()-1) << endl;
    }  

    int begin = 0;
    int queries = 0;
    int i = 0;
    int t = 0;
    while(i<vs.size()){

        while(vs[i][0] == 'L' || vs[i][0] == 'W'){
            i++;
        }
            
        queries = i;
        vector<string> graph (vs.begin()+begin, vs.begin()+queries);
        vii q;
        
        while(i < vs.size() && vs[i][0] != 'L' && vs[i][0] != 'W'){
            q.push_back({stoi(vs[i])-1, stoi(vs[i+1])-1});    
            i+=2;
        }
        
        vvi colors(graph.size(), vi(graph[0].size(), -1));
        int color = 0;
        vi colorsizes;
        
        FOR(k,0,graph.size()){
            FOR(j,0,graph[0].size()){
                if (colors[k][j] == -1 && graph[k][j] == 'W'){
                    int sizecolor = dfs(k,j,graph,colors,color);
                    colorsizes.push_back(sizecolor);
                    color++;
                }
            }
        }

        FOR(j,0,q.size()){
            cout << colorsizes[colors[q[j].first][q[j].second]] << endl;
        }

        
        begin = i;
        if(t != T-1)
            cout << endl;
        t++;   
    }


    return 0;    
}