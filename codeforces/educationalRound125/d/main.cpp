#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

#include <assert.h>

using namespace std;

#define TESTING

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


class Unit {
public:
    int c, d, h;
    Unit(int c, int d, int h){
        this->c = c;
        this->d = d;
        this->h = h;
    }

};

bool sort_units_by_cost(Unit* u1, Unit* u2){
    return u1->c < u2->c;
}

class Compare{
    public:
        bool operator() (const Unit& v1, const Unit& v2){
            
            return v1.d * v1.h > v2.d * v2.h;
        }
    };


int binary_search(vector<Unit*>& units_per_cost, int val){
    int start = 0, end=units_per_cost.size()-1;
    while(start <= end){
        if (end - start == 0){
            if (units_per_cost[end] == NULL)
                return -1;
            if (units_per_cost[end]->d * units_per_cost[end]->h > val){
                return units_per_cost[end]->c;
            }
            return -1;
        }
        if (end - start == 1){
            if (units_per_cost[start] != NULL)
                if (units_per_cost[start]->d * units_per_cost[start]->h > val){
                    assert (start == units_per_cost[start]->c);
                    return units_per_cost[start]->c;
                }
            if (units_per_cost[end] != NULL)
                if (units_per_cost[end]->d * units_per_cost[end]->h > val){
                    assert(end == units_per_cost[end]->c);
                    return end;
                }
            return -1;
        }
        int mid = (start + end) / 2; 
        if (units_per_cost[mid] == NULL){
            start = mid+1;
        }
        else if (units_per_cost[mid]->d * units_per_cost[mid]->h > val){
            end = mid;
        }
        else {
            start = mid+1;
        }
    }
}


int main(){
    int n, C;
    cin >> n >> C;
    vector<Unit*> units(n);
    FOR(i, 0, n){
        int c, d, h;
        cin >> c >> d >> h;
        units[i] = new Unit(c, d, h);
    }
    int m;
    cin >> m;
    vector<pair<int, int>> monsters(m);
    FOR(i, 0, m){
        cin >> monsters[i].first >> monsters[i].second;
    }

    vector<Unit*> units_per_cost(C+1, NULL);
    

    sort(units.begin(), units.end(), sort_units_by_cost);
    int index_units = 0;

    FOR(c, 0, C + 1){
        // Use c-1 if it is worth.
        if (c > 0 && units_per_cost[c-1] != NULL){
            if (units_per_cost[c] == NULL)
                units_per_cost[c] = units_per_cost[c-1];
            else if(units_per_cost[c]->h * units_per_cost[c]->d < units_per_cost[c-1]->h * units_per_cost[c-1]->d){
                units_per_cost[c] = units_per_cost[c-1];
            }
        }

        // use units of given cost c
        while(index_units < units.size() && units[index_units]->c == c){
            if (units_per_cost[c] == NULL || 
                    units_per_cost[c]->d * units_per_cost[c]->h < units[index_units]->d * units[index_units]->h){
                units_per_cost[c] = units[index_units];
            }
            index_units++;
        }

        if (units_per_cost[c] != NULL){
            if (c * 2 <= C){
                if (units_per_cost[c*2] == NULL || 
                        (units_per_cost[c*2]->d * units_per_cost[c*2]->h < 
                        units_per_cost[c]->d * 2 * units_per_cost[c]->h)){
                    units_per_cost[c*2] = new Unit(c*2, units_per_cost[c]->d*2, units_per_cost[c]->h);
                }
            }
            if (c * 3 <= C){
                if (units_per_cost[c*3] == NULL || 
                        (units_per_cost[c*3]->d * units_per_cost[c*3]->h < 
                        units_per_cost[c]->d * 3 * units_per_cost[c]->h)){
                    units_per_cost[c*3] = new Unit(c*3, units_per_cost[c]->d*3, units_per_cost[c]->h);
                }
            }
        }

    }

    FOR(i,0,m){
        // Find for every monster minimum cost
        int val = monsters[i].first * monsters[i].second;
        int mincost = binary_search(units_per_cost, val);
        cout << mincost << " ";
    }
    cout << endl;

    return 0;
}