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
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare {
    public:
    bool operator () (iii a, iii b) {
        return get<1>(a) > get<1>(b);
    }
};

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
    
    while(!cin.eof()) {
        string tmp; getline(cin, tmp);
        if (tmp.size()==0)
            break;
        vi nk = split(tmp, ' ');
        assert(nk.size()==2);
        int n = nk[0]; int k = nk[1];
        
        getline(cin, tmp);
        vi t = split(tmp, ' ');
        
        vvi elevator(n);
        
        vector<string> lines(n);
        vvii graph(100, vii());
        FOR(i,0,n){
            getline(cin, lines[i]);
        }
        FOR(i,0,n){
            string s = lines[i];
            int j = 0;
            int prevend = 0;
            while(prevend < s.size()){
                while(j < s.size() && s[j] != ' ')
                    j++;
                int num = stoi(s.substr(prevend, j - prevend));
                elevator[i].push_back(num);
                prevend = j+1;
                j++;
                if (elevator[i].size()>1){
                    graph[num].push_back({elevator[i][elevator[i].size()-2], i});
                    graph[elevator[i][elevator[i].size()-2]].push_back({num, i});
                }
            }
        }

        int start = 0;
        vvi distances(100, vi(n, INT32_MAX));
        priority_queue<iii, vector<iii>, Compare> pq;
        FOR(i,0,n){
            if (elevator[i].size() > 0 && elevator[i][0] == 0){
                pq.push({0, 0, i});
                distances[0][i] = 0;
            }
        }

        while(!pq.empty()){
            iii tup = pq.top(); pq.pop();
            int floor = get<0>(tup);
            int distance = get<1>(tup);
            int elev = get<2>(tup);
            COUT(floor); COUT(" "); COUT(distance); COUT(" "); COUT(elev); COUT(endl);
            if (floor == k)
                break;
            if (distances[floor][elev] == distance){
                FOR(j, 0, graph[floor].size()){
                    int neigh = graph[floor][j].first;
                    int elevneigh = graph[floor][j].second;
                    int time = abs(neigh-floor) * t[elevneigh];
                    time += (elevneigh==elev) ? 0 : 60;
                    COUT("\t"); COUT(neigh); COUT(" "); COUT(elevneigh); COUT(" "); COUT(time); COUT(endl);
                    if (distance + time < distances[neigh][elevneigh]) {

                        pq.push({neigh, distance+time, elevneigh});
                        distances[neigh][elevneigh] = distance+time;
                    }
                }
            }
        }
        int bestdist = INT32_MAX;
        FOR(i,0,n)
            bestdist = min(bestdist, distances[k][i]);
        cout << (bestdist != INT32_MAX ? to_string(bestdist) : "IMPOSSIBLE") << endl;
    }
    
    return 0;
}