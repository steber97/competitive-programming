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



ll compute_points(Vehicle& v, Ride& r, int time) {
    ll result = 0;
    if (manhattan({r.sr, r.sc}, {v.r, v.c}) <= (r.start - time)) {
        result += B;
    }
    int start_time = manhattan({r.sr, r.sc}, {v.r, v.c}) + time;
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

vector<string> inputs = {"input/a_example.in", "input/b_should_be_easy.in", 
"input/c_no_hurry.in", "input/d_metropolis.in", "input/e_high_bonus.in"};
vector<string> outputs = {"output/output_a", "output/output_b", 
"output/output_c", "output/output_d", "output/output_e"};

int main(int argc, char** argv){
    int totalpoints = 0;
    FOR(k,0,inputs.size()) {
        ifstream inputfile;
        
        inputfile.open(inputs[k]);
        inputfile >> R >> C >> F >> N >> B >> T;
        vector<Ride> rides;
        ll tot_dist = 0;
        FOR(i,0,N){
            ll sr, sc, er, ec, start, finish;
            inputfile >> sr >> sc >> er >> ec >> start >> finish;
            Ride r(sr,sc,er,ec,start,finish,i);
            rides.push_back(r);
            tot_dist += r.distance();
        }
        vector<Vehicle> vehicles;
        FOR(i,0,F)
            vehicles.push_back(Vehicle(0, 0, i));
        inputfile.close();

        ifstream outputfile;
        outputfile.open(outputs[k]);
        vvi assignments(F, vi());
        FOR(i,0,F){
            int n; outputfile >> n;
            FOR(j,0,n){
                int tmp; outputfile >> tmp;
                assignments[i].push_back(tmp);
            }
        }
        outputfile.close();
        unordered_set<int> rides_ids;
        ll points = 0;
        ll dist_points = 0;
        ll time_stationary = 0;
        ll bonus_points = 0;
        int activities_served = 0;
        FOR(i,0,assignments.size()){
            int time = 0;
            // cout << "ride" << endl;
            FOR(j,0,assignments[i].size()){
                Ride r = rides[assignments[i][j]];
                assert(rides_ids.find(r.id) == rides_ids.end());
                rides_ids.insert(r.id);
                // cout << manhattan({vehicles[i].r, vehicles[i].c}, {r.sr, r.sc}) + time << " " << r.start << endl;
                if (manhattan({vehicles[i].r, vehicles[i].c}, {r.sr, r.sc}) + time <= r.start) {
                    points += B;
                    bonus_points += B;
                }
                
                int starttime = time + manhattan({vehicles[i].r, vehicles[i].c}, {r.sr, r.sc}) ;
                starttime = starttime > r.start ? starttime : r.start;
                
                int finish_trip = starttime + manhattan({r.er, r.ec}, {r.sr, r.sc});
                
                if (finish_trip > T)
                    break;
                time_stationary += (starttime - time);

                if (finish_trip <= r.finish) {
                    points += manhattan({r.er, r.ec}, {r.sr, r.sc});
                    dist_points += manhattan({r.er, r.ec}, {r.sr, r.sc});
                }
                else{
                    time_stationary += manhattan({r.er, r.ec}, {r.sr, r.sc});
                    cout << "Something wrong!" << endl;
                }
                vehicles[i].r = r.er;
                vehicles[i].c = r.ec;
                time = finish_trip;
                activities_served++;
            }
        }
        totalpoints += points;
        cout << "points:\t" << points << ", dist:\t" << dist_points << " / " <<
             time_stationary << ", bonus:\t" << bonus_points << " / " << rides.size() * B << ", activities:\t" << activities_served << "/" << rides.size() << endl;
    }
    
    cout << totalpoints << endl;
    return 0;
}