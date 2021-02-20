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
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
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
    
    int n, p;

    cin >> n ;
    vii canvas(n);
    vi pegs_per_canvas(n, 0);
    vb in_the_middle(n, false); // in between canvas i and i+1
    unordered_set<int> already_pegs;
    int best = 0;
    int count = 0;
    FOR (i,0,n){
        cin >> canvas[i].first >> canvas[i].second;
    }
    cin >> p;
    vi pegs(p);
    int j = 0;
    FOR(i,0,p){
        cin >> pegs[i];
        already_pegs.insert(pegs[i]);
        while(j < canvas.size() && canvas[j].second < pegs[i]){
            j++;
        }
        if (j < canvas.size() and canvas[j].first <= pegs[i] and pegs[i] <= canvas[j].second)
            pegs_per_canvas[j]++;
        if (j < canvas.size()-1 and canvas[j].second == pegs[i] and pegs[i] == canvas[j+1].first){
            in_the_middle[j] = true;
            pegs_per_canvas[j+1] ++;
        }
    }

    FOR(i,0,pegs_per_canvas.size()){
        if (pegs_per_canvas[i] > 2){
            cout << "impossible" << endl;
            return 0;
        }
    }

    vi sol;
    FOR(i,0,canvas.size()){
        if (pegs_per_canvas[i] == 0){
            FOR(j, canvas[i].first+1, canvas[i].second){
                if (already_pegs.find(j) == already_pegs.end()){
                    pegs_per_canvas[i] ++;
                    already_pegs.insert(j);
                    sol.push_back(j);
                    break;
                }
            }
        }
        if (pegs_per_canvas[i] == 1){
            if (already_pegs.find(canvas[i].second) == already_pegs.end() and 
                    (i < canvas.size()-1 and (pegs_per_canvas[i+1] < 2 or canvas[i].second != canvas[i+1].first))){
                already_pegs.insert(canvas[i].second);
                pegs_per_canvas[i] ++;
                sol.push_back(canvas[i].second);
                if (i<canvas.size()-1 and canvas[i].second == canvas[i+1].first){
                    pegs_per_canvas[i+1] ++;
                }
            }
            else{
                FOR(j,canvas[i].first+1,canvas[i].second){
                    if (already_pegs.find(j) == already_pegs.end()){
                        pegs_per_canvas[i] ++;
                        already_pegs.insert(j);
                        sol.push_back(j);
                        break;
                    }
                }
            }
        }
    }

    cout << sol.size() << endl;
    FOR (i,0, sol.size()){
        cout << sol[i] << (i<sol.size()-1?" ":"");
    }
    cout << endl;

    return 0;
}