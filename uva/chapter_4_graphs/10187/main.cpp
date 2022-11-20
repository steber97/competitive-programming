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
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare {
    public:
    bool operator() (iii t1, iii t2) {
        if (get<1>(t1) != get<1>(t2))
            return get<1>(t1) > get<1>(t2);
        return get<2>(t1) > get<2>(t2);
    }
};


int main(){
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int m;
        cin >> m;
        unordered_map<string, int> mapcity;
        vector<string> cities;
        vector<viii> graph;
        FOR(i,0,m){
            string c1, c2;
            int hour, duration;
            cin >> c1 >> c2 >> hour >> duration;
            if (mapcity.find(c1) == mapcity.end()){
                int n = mapcity.size();
                mapcity[c1] = n;
                cities.push_back(c1);
                graph.push_back(vector<iii>());
            }
            if (mapcity.find(c2) == mapcity.end()){
                int n = mapcity.size();
                mapcity[c2] = n;
                cities.push_back(c2);
                graph.push_back(viii());
            }
            if (!(hour < 18 && hour > 6))
                if (((hour >= 18) && ((duration + (hour - 18)) <= 12)) || 
                        ((hour <= 6) && ((duration + hour) <= 6)))
                    graph[mapcity[c1]].push_back({mapcity[c2], hour, duration});
            
        }
        string start, end; cin >> start >> end;

        vii distances(graph.size(), {INT32_MAX, INT32_MAX});
        distances[mapcity[start]] = {0, 18};
        priority_queue<iii, viii, Compare> pq;
        pq.push({mapcity[start], 0, 18});

        while(!pq.empty()){
            iii tmp = pq.top(); pq.pop();
            int city = get<0>(tmp), blood = get<1>(tmp), hour = get<2>(tmp);
            if (hour == distances[city].second && blood == distances[city].first){
                FOR(i,0,graph[city].size()){
                    iii neight = graph[city][i];
                    int bloodplus = 0;
                    int neigh = get<0>(neight), hourneigh = get<1>(neight), dist = get<2>(neight);
                    if ((hourneigh >= 18 && hour <= 6) || 
                            (hourneigh >= 18 && hour >= 18 && hour > hourneigh) || 
                            (hourneigh <= 6 && hour <= 6 && hour > hourneigh)){
                        bloodplus++;
                    }
                    if ((distances[neigh].first > blood + bloodplus) || 
                            (distances[neigh].first == blood + bloodplus && distances[neigh].second > hourneigh + dist)){
                        pq.push({neigh, blood + bloodplus, hourneigh + dist});
                        distances[neigh] = {blood + bloodplus, hourneigh + dist};
                    }
                }
            }
        }
        cout << "Test Case " << t << "." << endl;
        if (distances[mapcity[end]].first != INT32_MAX){
            cout << "Vladimir needs " << distances[mapcity[end]].first << " litre(s) of blood." << endl;
        }
        else
            cout << "There is no route Vladimir can take." << endl;
    }
    return 0;
}