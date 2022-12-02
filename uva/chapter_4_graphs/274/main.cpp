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


vi rooms_visited(vvi& graph, int startroom){
    queue<int> q;
    vb visited(graph.size(), false);
    q.push(startroom);
    visited[startroom] = true;
    vi result;
    while(!q.empty()){
        int n = q.front(); q.pop();
        result.push_back(n);
        FOR(j,0,graph[n].size()){
            int neigh = graph[n][j];
            if (!visited[neigh]){
                visited[neigh] = 1;
                q.push(neigh);
            }
        }
    }
    return result;
}

bool cangohome(vvi& graph, int startroom, unordered_set<int> taboo) {
    queue<int> q;
    
    vb visited(graph.size(), false);
    if(taboo.find(startroom) == taboo.end()){
        q.push(startroom);
        visited[startroom] = true;
    }
    
    while(!q.empty()){
        int i = q.front();
        q.pop();
        FOR(j,0,graph[i].size()){
            int neigh = graph[i][j];
            if (taboo.find(neigh) == taboo.end()){
                if (!visited[neigh]){
                    q.push(neigh);
                    visited[neigh] = true;
                }
                else{
                    if (neigh == startroom)
                        return true;
                }
            }
        }
    }
    return false;
}

int main(){
    string s;
    getline(cin, s);
    int T = stoi(s);
    getline(cin, s);
    FOR(t,0,T){
        vvi catgraph;
        vvi mousegraph;
        int n, rc, rm;
        int counter = 0;
        getline(cin, s);
        while (s.size()>0){
            if (counter == 0){
                vi threei = split(s, ' ');
                n = threei[0], rc = threei[1], rm = threei[2];
                counter ++;
                rc--; rm--;
                catgraph.resize(n, vi());
                mousegraph.resize(n, vi());
            }
            else{
                vi twoi = split(s, ' ');
                int a=twoi[0], b=twoi[1];
                if (a == -1)
                    counter++;
                else {
                    a--; b--;
                    if (counter == 1){
                        catgraph[a].push_back(b);
                    }
                    else{
                        mousegraph[a].push_back(b);
                    }
                }
            }
            getline(cin, s);
        } while(s.size() > 0);

        vi roomscat = rooms_visited(catgraph, rc);
        vi roomsmouse = rooms_visited(mousegraph, rm);

        VECT(roomscat); VECT(roomsmouse);
        unordered_set<int> roomc, roomm;
        FOR(i,0,roomscat.size()){
            roomc.insert(roomscat[i]);
        }
        bool intersection = false;
        FOR(i,0,roomsmouse.size()){
            if (roomc.find(roomsmouse[i]) != roomc.end())
                intersection = true;
        }

        bool can_go_home = cangohome(mousegraph, rm, roomc);

        cout << (intersection ? "Y" : "N") << " " << (can_go_home ? "Y" : "N") << endl;
        if (t != T-1)
            cout << endl;
        
    }
    
    return 0;
}