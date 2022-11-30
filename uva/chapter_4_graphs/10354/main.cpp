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

class Compare {
    public: bool operator() (ii p1, ii p2){
        return p1.second > p2.second;
    }
};

// struct hashFunction
// {
//     size_t operator()(const pair<int , int> &x) const
//     {
//         return x.first ^ x.second;
//     }
// };


int main(){
    while(!cin.eof()){
        string l1;
        getline(cin, l1);
        if (l1 == "")
            break;
        vi l1i = split(l1, ' ');
        int p = l1i[0], r = l1i[1], bh = l1i[2],
            o = l1i[3], yo = l1i[4], m = l1i[5];
        
        bh--; o--; yo--; m--;
        vvii graph(p, vii());
        FOR(i,0,r){
            string s;
            getline(cin, s);
            vi edgei = split(s, ' ');
            int start = edgei[0], end=edgei[1], cost=edgei[2];
            start--; end--;
            graph[start].push_back({end, cost});
            graph[end].push_back({start, cost});
        }

        vvi distances = floydwarshall(graph);

        queue<int> q;
        q.push(bh);
        vb visited(p, false);
        visited[bh] = true;
        // unordered_set<ii, hashFunction> forbidden;
        while(!q.empty()){
            int n = q.front();
            q.pop();
            if (n==o)
                break;
            FOR(i,0,p){
                if ((distances[bh][n] + distances[n][i] + distances[i][o]) == 
                    distances[bh][o]
                ){
                    if (!visited[i]){
                        q.push(i);
                        visited[i]=1;
                    }
                    // forbidden.insert({n,i});
                    // forbidden.insert({i,n});
                }
            }
        }

        priority_queue<ii, vii, Compare> pq;
        vi distances2(p, INT32_MAX);
        if (!visited[yo]){
            distances2[yo] = 0;
            pq.push({yo, 0});
        }
        
        while(!pq.empty()){
            int n = pq.top().first, cost = pq.top().second;
            pq.pop();
            if (n==m){
                break;
            }
            if(distances2[n] == cost){
                FOR(j,0,graph[n].size()){
                    int neigh = graph[n][j].first;
                    int costn = graph[n][j].second;
                    if (!visited[neigh]){
                        if (distances2[neigh] > cost + costn){
                            distances2[neigh] = cost + costn;
                            pq.push({neigh, distances2[neigh]});
                        }
                    }
                }
            }
        }

        if (distances2[m] == INT32_MAX){
            cout << "MISSION IMPOSSIBLE." << endl;
        }
        else{
            cout << distances2[m] << endl;
        }
    }
    return 0;
}