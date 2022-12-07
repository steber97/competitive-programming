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
typedef vector<vd> vvd;
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

#define INTMAX (INT32_MAX / 4)

vvi floydwarshall(vvi& graph){
    int n = graph.size();
    vvi distances(n, vi(n, INTMAX));
    FOR(i,0,n)
        distances[i][i] = 0;

    FOR(i,0,n){
        FOR(j,0,graph[i].size()){
            distances[i][graph[i][j]] = 1;
        }
    }

    FOR(u,0,n){
        FOR(i,0,n){
            FOR(j,0,n){
                distances[i][j] = min(
                    distances[i][j], 
                    min(distances[i][u] + distances[u][j], INTMAX)
                );
            }
        }
        // FOR(i,0,n){
        //     VECT(distances[i]);COUT(endl);
        // }
    }

    return distances;
}


int main(){
    int n,m;
    cin >> n >> m;
    int counter = 1;
    while(n!=0){
        vector<string> people;
        unordered_map<string, int> mappeople;
        vvi graph(n, vi());
        FOR(i,0,m){
            string s1, s2;
            cin >> s1 >> s2;
            if (mappeople.find(s1)==mappeople.end()){
                mappeople[s1] = people.size();
                people.push_back(s1);
            }
            if (mappeople.find(s2) == mappeople.end()){
                mappeople[s2] = people.size();
                people.push_back(s2);
            }
            graph[mappeople[s1]].push_back(mappeople[s2]);
            graph[mappeople[s2]].push_back(mappeople[s1]);
        }

        vvi distances = floydwarshall(graph);
        int result = 0;
        FOR(i,0,n){
            FOR(j,0,n){
                if (i!=j)
                    result = max(result, distances[i][j]);
            }
        }
        cout << "Network " << counter << ": " << (result!=INTMAX?to_string(result):"DISCONNECTED") << endl << endl;
        cin >> n >> m;
        counter++;
    }
    return 0;
}