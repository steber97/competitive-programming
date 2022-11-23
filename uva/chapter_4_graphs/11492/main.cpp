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
typedef vector<char> vc;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef vector<vc> vvc;
typedef vector<vvi> vvvi;
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef pair<double,double> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


class Compare{
    public:
    bool operator() (tuple<int, int, char> p1, tuple<int, int, char> p2){
        if(get<1>(p1) != get<1>(p2))
            return get<1>(p1) > get<1>(p2);
        return get<2>(p1) > get<2>(p2);
    }
};

int main(){
    int n;
    cin >> n;
    while(n!=0){
        string start,end;
        cin >> start >> end;

        unordered_map<string, int> maplang;
        maplang[start] = 0;
        maplang[end] = 1;
        vector<string> lang = {start, end};
        vector<vector<pair<int, string>>> graph = {vector<pair<int,string>>(), vector<pair<int,string>>()};

        FOR(i,0,n){
            string s1, s2, word;
            cin >> s1 >> s2 >> word;
            if (maplang.find(s1)==maplang.end()){
                int count = maplang.size();
                maplang[s1] = count;
                lang.push_back(s1);
                graph.push_back(vector<pair<int, string>>());
            }
            if (maplang.find(s2)==maplang.end()){
                int count = maplang.size();
                maplang[s2] = count;
                lang.push_back(s2);
                graph.push_back(vector<pair<int, string>>());
            }
            graph[maplang[s1]].push_back({maplang[s2], word});
            graph[maplang[s2]].push_back({maplang[s1], word});
        }

        vector<vector<int>> dists(graph.size(), vi('z'-'a'+1, INT32_MAX));
        priority_queue<tuple<int, int, char>, vector<tuple<int, int, char>>, Compare> pq;
        pq.push({maplang[start], 0, '.'});  // special char '.' because we have no previous.
        FOR(i,0,'z'-'a'+1)
            dists[maplang[start]][i] = 0;

        while(!pq.empty()){
            int l = get<0>(pq.top());
            int cost = get<1>(pq.top());
            char c = get<2>(pq.top());
            
            pq.pop();
            if (l == maplang[end]){
                break;
            }
                
            if ((c == '.') || (cost == dists[l][c-'a'])){

                VALUE(lang[l]); VALUE(cost); VALUE(c);
                FOR(j,0,graph[l].size()){
                    int neigh = graph[l][j].first;
                    string w = graph[l][j].second;
                    COUT(lang[neigh]); COUT(" "); COUT(w); COUT("\t");
                    if (w[0] != c){
                        if (w.size() + cost < dists[neigh][w[0]-'a']){
                            pq.push({neigh, cost + w.size(), w[0]});
                            dists[neigh][w[0]-'a'] = cost +w.size();
                        } 
                    }
                }
                COUT(endl);
            }
        }

        int bestdist = INT32_MAX;
        FOR(i,0,'z'-'a'+1){
            bestdist = min(bestdist, dists[maplang[end]][i]);
        }

        cout << (bestdist < INT32_MAX ? to_string(bestdist) : "impossivel") << endl;


        cin >>n ;   
    }
    return 0;
}