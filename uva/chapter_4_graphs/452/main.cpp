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
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vector<string> split(string& s, char sep) {
    int j = 0;
    int prevend = 0;
    vector<string> result;
    while(prevend < s.size()){
        while(j < s.size() && s[j] != sep)
            j++;
        result.push_back(s.substr(prevend, j - prevend));
        prevend = j+1;
        j++;
    }
    return result;
}


int visit(vvi& graph, int i, vi& cost, vi& dp){
    if (dp[i]!=-1)
        return dp[i];
    int res = 0;
    FOR(j,0,graph[i].size()){
        int tmp = visit(graph, graph[i][j], cost, dp);
        res = max(tmp, res);
    }
    dp[i] = cost[i]+res;
    return dp[i];
}


int main(){
    int T;
    string s;
    getline(cin, s);
    T = stoi(s);
    getline(cin,s);
    FOR(t,0,T){
        vi indeg(27, 0);
        vvi graph(27, vi());
        vi cost(27, -1);
        do{
            getline(cin, s);
            if(s.size()>0){
                vector<string> l = split(s, ' ');
                int node = l[0][0] - 'A';
                cost[node] = stoi(l[1]);
                if (l.size()==3){
                    FOR(j,0,l[2].size()){
                        int nei = l[2][j]-'A';
                        graph[nei].push_back(node);
                        indeg[node]++;
                    }
                }
            }

        }while(s.size()!=0 && !cin.eof());

        int result = 0;
        vi dp(27, -1);
        FOR(i,0,27){
            if (indeg[i]==0 && cost[i]>-1 && dp[i]==-1){
                int res = visit(graph,i,cost, dp);
                result = max(result, res);
            }
        }
        cout<<result << endl << (t!=T-1?"\n":"");
    }
    return 0;
}
