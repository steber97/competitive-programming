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
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;
typedef vector<viii> vviii;
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi floydwarshall(vvi& graph){
    int n = graph.size();
    vvi distances(n, vi(n, INT32_MAX));
    FOR(i,0,n){
        distances[i][i] = 0;
        FOR(j,0,graph[i].size()){
            distances[i][graph[i][j]] = min(
                distances[i][graph[i][j]], 1);
        }
    }

    FOR(u,0,n){
        FOR(i,0,n){
            FOR(j,0,n){
                if (distances[i][u] != INT32_MAX && distances[u][j] != INT32_MAX){
                    distances[i][j] = min(distances[i][j], distances[i][u]+distances[u][j]);
                }
            }
        }
    }

    return distances;
}

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


int main(){
    while(true){
        int n;
        string firstline;
        getline(cin, firstline);
        if (firstline == "")
            break;
        n = stoi(firstline);
        if (n==0)
            break;
        vvi graphold(n, vi());
        vvi graphnew(n, vi());
        FOR(i,0,n){
            string s;
            getline(cin, s);
            vi nodes = split(s, ' ');
            FOR(j,1,nodes.size()){
                graphold[i].push_back(nodes[j]-1);
            }
        }
        FOR(i,0,n){
            string s;
            getline(cin, s);
            vi nodes = split(s, ' ');
            FOR(j,1,nodes.size()){
                graphnew[i].push_back(nodes[j]-1);
            }
        }
        int a,b; 
        string ab;
        getline(cin, ab);
        vi abi = split(ab, ' ');
        a=abi[0]; b=abi[1];

        vvi distancesold = floydwarshall(graphold);
        vvi distancesnew = floydwarshall(graphnew);
        bool ok = true;
        FOR(i,0,n){
            FOR(j,0,n){
                if (distancesnew[i][j] > (a * distancesold[i][j] + b)){
                    ok = false;
                }
            }
        }

        cout << (ok ? "Yes" : "No") << endl; 
    }
    return 0;
}