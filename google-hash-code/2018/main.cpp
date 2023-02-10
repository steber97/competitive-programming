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

int R,C,F,N,B,T;


ll manhattan(pair<ll,ll> p1, pair<ll,ll> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}
struct Ride {
    ll sr, sc, er, ec, start, finish;
    int id;
    bool served = false;
    Ride(ll sr, ll sc, ll er, ll ec, ll start, ll finish, int id) : 
        sr(sr), sc(sc), er(er), ec(ec), start(start), finish(finish), id(id) {
            served = false;
    }
    ll distance(){
        return manhattan({sr,sc},{er,ec});
    }
};

struct Vehicle {
    ll r,c;
    int id;
    Vehicle(ll r, ll c, int id) : r(r),c(c),id(id){

    }
};

class Compare {
    public:
    bool operator() (pair<Vehicle,int> v1, pair<Vehicle,int> v2) {
        return v1.second > v2.second;
    }
};



ll compute_points(Vehicle& v, Ride& r, ll time) {
    ll result = 0;
    if (manhattan({r.sr, r.sc}, {v.r, v.c}) <= (r.start - time)) {
        result += B;
    }
    ll start_time = manhattan({r.sr, r.sc}, {v.r, v.c}) + time;
    start_time = start_time < r.start? r.start : start_time;
    if (manhattan({r.sr, r.sc}, {r.er, r.ec}) + start_time <= r.finish)
        result += manhattan({r.sr, r.sc}, {r.er, r.ec});
    return result;
}

ll compute_ride_time(Vehicle& v, Ride r, ll current_time) {
    ll movement = manhattan({v.r, v.c}, {r.sr, r.sc}) + current_time;
    current_time = movement > r.start ? movement : r.start;
    current_time += manhattan({r.sr, r.sc}, {r.er, r.ec});
    return current_time;
}


bool isbetter(Vehicle v, Ride r1, Ride r2, ll current_time) {
return ( 
    (compute_points(v, r1, current_time)) - 
    (compute_ride_time(v, r1, current_time))
    ) > 
    ( 
    (compute_points(v, r2, current_time)) - 
    (compute_ride_time(v, r2, current_time)))
    ;
}


int main(){
    cin >> R >> C >> F >> N >> B >> T;
    vector<Ride> rides;
    FOR(i,0,N){
        ll sr, sc, er, ec, start, finish;
        cin >> sr >> sc >> er >> ec >> start >> finish;
        Ride r(sr,sc,er,ec,start,finish,i);
        rides.push_back(r);
    }
    vector<Vehicle> vehicles;
    FOR(i,0,F)
        vehicles.push_back(Vehicle(0, 0, i));

    priority_queue<pair<Vehicle,int>, vector<pair<Vehicle,int>>, Compare> pq;

    FOR(i,0,F)
        pq.push({vehicles[i], 0});

    vvi assignments(F, vi());
    ll t = 0;
    while(t < T && !pq.empty()) {
        auto[ v, current_time] = pq.top();
        pq.pop();
        t = current_time;
        Ride* bestride = NULL;
        FOR (i,0,rides.size()){
            if (!rides[i].served) {
                if (compute_ride_time(v, rides[i], current_time) <= rides[i].finish) {
                    if (bestride == NULL){
                        bestride = &rides[i];
                    }
                    else{
                        if (isbetter(v, rides[i], *bestride, current_time)){
                            bestride = &rides[i];
                        }
                    }
                }
            }
        }
        if (bestride!=NULL){
            ll vehicletime = compute_ride_time(v,*bestride,current_time);
            if (vehicletime <= T){
                assignments[v.id].push_back(bestride->id);
                v.c = bestride->ec;
                v.r = bestride->er;
                bestride->served = true;
                pq.push({v, vehicletime});
            }
        }

    }
    unordered_set<int> ride_ids;
    FOR(i,0,F){
        cout << assignments[i].size() << " ";
        FOR(j,0,assignments[i].size()){
            cout << assignments[i][j] << (j != assignments[i].size()-1 ? " ":"");
            if (ride_ids.find(assignments[i][j]) != ride_ids.end()){
                cout<<"same ride assigned twice " << assignments[i][j] << endl;
                assert(ride_ids.find(assignments[i][j]) == ride_ids.end());
            }
        }
        cout << endl;
    }
    return 0;
}