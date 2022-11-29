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
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<vii> vvii;
typedef vector<vector<vector<ii>>> vvvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi floydwarshall(vvii& graph){
    vvi distances(graph.size(), vi(graph.size(), INT32_MAX));
    FOR(i,0,graph.size())
        distances[i][i] = 0;

    FOR(i,0,graph.size()){
        FOR(j,0,graph[i].size()){
            distances[i][graph[i][j].first] = min(graph[i][j].second, distances[i][graph[i][j].first]);
        }
    }


    FOR(u,0,graph.size()){
        FOR(i,0,graph.size()){
            FOR(j,0,graph.size()){
                if ((distances[i][u] != INT32_MAX) && (distances[u][j] != INT32_MAX)){
                    distances[i][j] = min(distances[i][j], distances[i][u] + distances[u][j]);
                }
            }
        }
    }

    return distances;
}



int main(){
    int n;
    while(cin >> n){
        if(n==0)
            break;
        unordered_map<char,int> mapcity;
        vector<char> mapcityrev;
        vvii graphyoung;
        vvii graphold;
        FOR(i,0,n){
            char y, b, c1, c2;
            int cost;
            cin >> y >> b >> c1 >> c2 >> cost;
            if (mapcity.find(c1) == mapcity.end()){
                int count = graphyoung.size();
                mapcity[c1] = count;
                mapcityrev.push_back(c1);
                graphyoung.push_back(vii());
                graphold.push_back(vii());
            }
            if (mapcity.find(c2) == mapcity.end()){
                int count = graphyoung.size();
                mapcity[c2] = count;
                mapcityrev.push_back(c2);
                graphyoung.push_back(vii());
                graphold.push_back(vii());
            }
            if (y == 'Y'){
                graphyoung[mapcity[c1]].push_back({mapcity[c2], cost});
                if (b == 'B')
                    graphyoung[mapcity[c2]].push_back({mapcity[c1], cost});
            }
            else{
                graphold[mapcity[c1]].push_back({mapcity[c2], cost});
                if (b == 'B')
                    graphold[mapcity[c2]].push_back({mapcity[c1], cost});
            }
        }

        // VALUE(graphold.size());
        // VALUE(graphyoung.size());
        char a,b;
        cin >> a >> b;

        if (mapcity.find(a) == mapcity.end()){
            int count = graphyoung.size();
            mapcity[a] = count;
            mapcityrev.push_back(a);
            graphyoung.push_back(vii());
            graphold.push_back(vii());
        }
         if (mapcity.find(b) == mapcity.end()){
            int count = graphyoung.size();
            mapcity[b] = count;
            mapcityrev.push_back(b);
            graphyoung.push_back(vii());
            graphold.push_back(vii());
        }

        vvi distancesyoung = floydwarshall(graphyoung);
        vvi distancesold = floydwarshall(graphold);

        int best = INT32_MAX;
        vi bestnodes = {};
        FOR(i,0,distancesold.size()){
            if (distancesyoung[mapcity[a]][i] != INT32_MAX && distancesold[mapcity[b]][i] != INT32_MAX){
                if (best > distancesyoung[mapcity[a]][i] + distancesold[mapcity[b]][i]){
                    best = distancesyoung[mapcity[a]][i] + distancesold[mapcity[b]][i];
                    bestnodes = {i};
                }
                else if (best == distancesyoung[mapcity[a]][i] + distancesold[mapcity[b]][i]){
                    bestnodes.push_back(i);
                }
            }
        }

        if (best != INT32_MAX){
            cout << best << " "; 
            sort(bestnodes.begin(), bestnodes.end());
            FOR(i,0,bestnodes.size())
                cout << mapcityrev[bestnodes[i]] << (i != bestnodes.size()-1 ? " ": "");
            cout << endl;
        }
        else{
            cout << "You will never meet." << endl;
        }
    }
    return 0;
}