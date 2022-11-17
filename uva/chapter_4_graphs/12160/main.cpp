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
typedef vector<ii> vii;
typedef vector<tuple<int, int, int>> viii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


int main(){
    int casen = 1;
    while(true){
        int start, end, b;
        cin >> start >> end >> b;
        if(start == 0 && end == 0 && b == 0)
            break;
        vi buttons(b);
        FOR(i,0,b){
            string s; cin >> s;
            buttons[i] = stoi(s);
        }

        queue<int> q;
        vi visited(10000, -1);
        q.push(start);
        visited[start] = 0;
        bool found = false;
        while(!q.empty()){
            int n = q.front(); q.pop();
            if (n == end){
                found = true;
                break;
            }
            FOR(i,0,b){
                int neigh = (n + buttons[i]) % 10000;
                if (visited[neigh] == -1){
                    q.push(neigh);
                    visited[neigh] = visited[n] + 1;
                }
            }
        }

        cout << "Case " << casen++ << ": " ;
        if (found){
            cout << visited[end] << endl;
        }
        else{
            cout << "Permanently Locked" << endl;
        }
    }
    return 0;
}