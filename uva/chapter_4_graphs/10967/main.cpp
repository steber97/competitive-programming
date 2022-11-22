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
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


bool are_adj(ii start, ii end, char door){
    // the door in the end position must be in the right direction.
    if ((start.first == end.first) && (start.second == (end.second + 1)) && (door == 'E')){
        return true;
    }
    if ((start.first == end.first) && (start.second == (end.second - 1)) && (door == 'W')){
        return true;
    }
    if ((start.first == (end.first + 1)) && (start.second == end.second) && (door == 'N')){
        return true;
    }
    if ((start.first == (end.first - 1)) && (start.second == end.second) && (door == 'S')){
        return true;
    }
    return false;
}

int mult(ii start, ii end, char door){
    // return 0,1,2 depending on orientation of door in start
    if ((start.first == end.first) && (start.second == (end.second + 1))){
        if (door == 'W')
            return 0;
        if (door == 'N' || door == 'S')
            return 1;
        return 2;
    }

    if ((start.first == end.first) && (start.second == (end.second - 1))){
        if (door == 'E')
            return 0;
        if (door == 'N' || door == 'S')
            return 1;
        return 2;
    }

    if ((start.first == (end.first+1)) && (start.second == end.second)){
        if (door == 'S')
            return 0;
        if (door == 'E' || door == 'W')
            return 1;
        return 2;
    }

    if ((start.first == (end.first-1)) && (start.second == end.second)){
        if (door == 'N')
            return 0;
        if (door == 'E' || door == 'W')
            return 1;
        return 2;
    }
}

class Compare{
    public:
    bool operator() (ii p1, ii p2){
        return p1.second > p2.second;
    }
};


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n,m;
        cin >> n >> m;
        vvc grid(n, vc(m));
        vii doors;
        vvi doorcost(n, vi(m));
        for(int i = n-1; i >= 0; i--){
            FOR(j,0,m){
                cin >> grid[i][j];
                if (grid[i][j] != '.' && grid[i][j] != '#')
                    doors.push_back({i,j});
            }
        }
        FOR(i,0,doors.size()){
            int cost ; cin >> cost;
            doorcost[doors[i].first][doors[i].second] = cost;
        }

        vvii graph(n*m, vii());

        FOR(i,0,n){
            FOR(j,0,m){
                vii neighs = {{i-1, j}, {i, j-1}};
                for(ii neigh: neighs){
                    if(neigh.first < n && neigh.first >= 0 && neigh.second < m && neigh.second >= 0){
                        // case in which there cannot be any connection
                        if (grid[neigh.first][neigh.second] == '#' || grid[i][j]=='#'){
                            // cannot be any link.
                        }
                        else{
                            // case in which there are two empty cells.
                            if (grid[neigh.first][neigh.second] == '.'){
                                graph[i*m + j].push_back({neigh.first * m + neigh.second, 1});
                            }
                            else if (are_adj({i,j}, neigh, grid[neigh.first][neigh.second])){
                                graph[i*m + j].push_back({neigh.first * m + neigh.second, 1});
                            }

                            if (grid[i][j] == '.'){
                                graph[neigh.first * m + neigh.second].push_back({i*m + j, 1});
                            }
                            else if (are_adj(neigh, {i,j}, grid[i][j])){
                                graph[neigh.first * m + neigh.second].push_back({i*m + j, 1});
                            }
                        }
                    }
                }
            }
        }

        FOR(i,0,doors.size()){
            int pos = doors[i].first * m + doors[i].second;
            FOR(j,0,graph[pos].size()){
                ii neigh = {graph[pos][j].first / m, graph[pos][j].first % m};
                graph[pos][j].second += mult(doors[i], neigh, grid[doors[i].first][doors[i].second]) * doorcost[doors[i].first][doors[i].second];
            }
        }
        // FOR(i,0,graph.size()){
        //     FOR(j,0,graph[i].size()){
        //         COUT(graph[i][j].first);COUT(" ");COUT(graph[i][j].second);COUT("\t");
        //     }
        //     COUT(endl);
        // }
        priority_queue<ii, vii, Compare> pq;
        pq.push({0,0});
        vi distances(n*m, INT32_MAX);
        distances[0]=0;
        while(!pq.empty()){
            ii p = pq.top(); pq.pop();
            if (p.first == n*m-1)
                break;
            if (p.second == distances[p.first]){
                FOR(j,0,graph[p.first].size()){
                    int neigh = graph[p.first][j].first;
                    int cost = graph[p.first][j].second;
                    if (distances[neigh] > p.second + cost){
                        pq.push({neigh, cost + p.second});
                        distances[neigh] = cost+p.second;
                    }
                }
            }
        }
        cout << (*(distances.end()-1)!=INT32_MAX? to_string(*(distances.end()-1)): "Poor Kianoosh") << endl;
    }
    return 0;
}