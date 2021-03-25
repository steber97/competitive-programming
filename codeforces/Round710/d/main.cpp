#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vi v(n);
        unordered_map<int,int> mymap;
        priority_queue<int> pq;
        FOR(i,0,n){
            int tmp;
            cin >> tmp;
            if (mymap.find(tmp) == mymap.end()){
                mymap[tmp] = 0;
            }
            mymap[tmp] ++;
        }
        for(pair<int,int> p: mymap){
            pq.push(p.second);
        }
        bool finish = false;
        while(!pq.empty()){
            int v1, v2;
            v1 = pq.top();
            pq.pop();
            if (pq.empty()){
                cout << v1 << endl;
                finish = true;
                break;
            }
            else{
                v2 = pq.top();
                pq.pop();
                v1--; v2--;
                if (v1 > 0)
                    pq.push(v1); 
                if (v2 > 0)
                    pq.push(v2);
            }
        }
        if (!finish)
            cout << 0 << endl;
    }
    return 0;
}