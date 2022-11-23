#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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
    bool operator() (pair<int, double> p1, pair<int, double> p2){
        return p1.second > p2.second;
    }
};

double distance(dd p1, dd p2){
    return pow((p1.first - p2.first) * (p1.first - p2.first) + 
           (p1.second - p2.second) * (p1.second - p2.second), 0.5);
}

int main(){
    
    while(true){
        int n,m;
        string s;
        cin >> s;
        if (s == "*")
            break;
        cin >> m; n = stoi(s);
        int k; cin >> k;
        vdd pos(k);
        FOR(i,0,k){
            cin >> pos[i].first >> pos[i].second;
        }
        double d; cin >> d;
        
        priority_queue<pair<int, double>, vector<pair<int, double>>, Compare> pq;
        pq.push({-1, 0LL});
        vector<double> dists(k, double(n*m + 100));
        
        double bestdist =  double(n*m + 100);
        while(!pq.empty()){
            int i = pq.top().first;
            double dist = pq.top().second;
            pq.pop();
            if ((i == -1) || (abs(dist - dists[i]) < DELTA)){
                dd p = (i==-1 ? make_pair(0.0,0.0) : pos[i]);
                COUT(p.first);COUT(" ");COUT(p.second);COUT("\t"); COUT(dist);COUT(endl);
                if((distance(p, make_pair(n,m)) < 1.5) || abs(distance(p, {n,m}) - 1.5) < DELTA)
                    bestdist = min(bestdist, dist + distance(p, {n, m}));
                FOR(j,0,k){
                    if (i!=j){
                        dd neigh = pos[j];
                        if ((distance(neigh, p) < 1.5) || (abs(distance(neigh,p) - 1.5) < DELTA) ){
                            if (dists[j] > (dist + distance(neigh, p))){
                                dists[j] = dist + distance(neigh,p);
                                pq.push({j, dists[j]});
                            }   
                        }
                    }
                }
            }
        }

        if (d >= bestdist || abs(d-bestdist)<DELTA){
            cout << "I am lucky!" << endl;
        }
        else{
            cout << "Boom!" << endl;
        }

    }
    return 0;
}