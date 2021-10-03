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
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define COUT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001

class Compare{
public:
    bool operator() (tuple<string, int, int>& t1, tuple<string, int, int>& t2){
        if (get<1>(t1) < get<1>(t2))
            return true;
        if (get<1>(t1) == get<1>(t2) && get<2>(t1) < get<2>(t2))
            return true;
        return false;
    }
};


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    char c[50];
    cin.getline(c, 51);

    unordered_map<string, pair<int,int>> mymap;
    FOR(i,0,n*3){
        char c[60];
        cin.getline(c, 51);
        string s = c;
        COUT(s); COUT(endl);
        if (mymap.find(s) == mymap.end())
            mymap[s] = {0, i};
        mymap[s] = {mymap[s].first+1, i};
    }
    
    priority_queue<tuple<string, int, int>, vector<tuple<string, int, int>>, Compare> q;

    for (pair<string, pair<int, int>> myk : mymap){
        
        q.push({myk.first, myk.second.first, myk.second.second});
    }
    
    FOR(i, 0, k){
        if (q.size() == 0)
            break;
        tuple<string, int, int> t = q.top();
        cout << get<0>(t) << endl;
        q.pop();
    }

    return 0;
}