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
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

int main(){
    int T;
    cin >> T;
    bool finish = false;
    int t = 0;
    while(!finish){
        t++;
        vector<string> nodes;
        unordered_map<string, int> map_nodes;
        while(true){
            string line;
            if (cin.eof()) {
                finish = true;
                break;
            }
            cin >> line;
            if (line[0] != '*'){
                nodes.push_back(line);
                map_nodes[line] = nodes.size()-1;
            }
            else{
                break;
            }
        }
        vector<pair<string,string>> startend;
        string tmp; getline(cin, tmp);
        vvi graph(nodes.size(), vi());
        FOR(i,0,nodes.size()){
            FOR(j,i+1,nodes.size()){
                if (nodes[i].size() == nodes[j].size()){
                    int diff = 0;
                    FOR(k,0,nodes[i].size()){
                        if (nodes[i][k] != nodes[j][k])
                            diff++;
                    }
                    if(diff == 1){
                        graph[i].push_back(j);
                        graph[j].push_back(i);
                    }
                }
                else if (fabs(nodes[i].size() - nodes[j].size()) == 1) {
                    int k=0, l=0;
                    while(k<nodes[i].size() && l<nodes[j].size()){
                        if(nodes[i][k]==nodes[j][l]){
                            k++;l++;
                        }
                        else if (nodes[i].size() > nodes[j].size())
                            k++;
                        else
                            l++;
                    }
                    if (k==nodes[i].size() && l==nodes[j].size()){
                        graph[i].push_back(j);
                        graph[j].push_back(i);
                    }
                }
            }
        }

        while(!finish){
            string line;
            getline(cin, line);
            if (line.find(' ') == line.npos)
                break;
            else{
                string n1, n2;
                n1 = line.substr(0, line.find(' '));
                n2 = line.substr(line.find(' ')+1, line.size() - line.find(' ') - 1);
                
                int start = map_nodes[n1];
                int end = map_nodes[n2];

                queue<int> q; q.push(start);
                vi distances(graph.size(), -1);
                distances[start] = 0;
                while(!q.empty()){
                    int n = q.front(); q.pop();
                    if (n == end){
                        cout << n1 << " " << n2 << " " << distances[n] << endl;
                        break;
                    }
                    FOR(j,0,graph[n].size()){
                        if (distances[graph[n][j]] == -1){
                            q.push(graph[n][j]);
                            distances[graph[n][j]] = distances[n]+1;
                        }
                    }
                }
            }
        }
        if(t==T)
            break;
        cout << endl;
    }
    return 0;
}