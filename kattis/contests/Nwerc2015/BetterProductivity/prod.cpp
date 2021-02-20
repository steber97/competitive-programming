#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)

int n,p;   // employees and production lines.
vii emp;
vii good_v, bad_v;


bool sort_bad(ii& p1, ii& p2){
    // sort by start.
    return p1.first < p2.first  ;
}

bool sort_good(ii& p1, ii& p2){
    // sort by length of interval
    return (p1.second - p1.first) > (p2.second - p2.first);
}

int interv(int s, int e, vii vect){
    //VALUE(s);
    //VALUE(e);
    /*int res = INT_MAX;
    FOR(i, s, e+1){
        res = min(vect[i].second, res);
    }
    return res - vect[e].first > 0 ? res - vect[e].first : -INT_MAX;*/
    return vect[s].second - vect[e].first > 0? vect[s].second - vect[e].first : -INT_MAX ;
}

int summation(vii vect, int pos){
    int res = 0;
    FOR(i, 0, pos+1){
        res += vect[i].second - vect[i].first;
    }
    return res;
}

int main(){

    cin >> n >> p;

    emp.resize(n);

    FOR(i, 0, n){
        cin >>emp[i].first >> emp[i].second;
    }

    // IDENTIFY GOOD WORKERS
    vb good(n, false);
    FOR(i, 0, n){
        FOR(j, 0, n){
            if (i != j){
                
                if (emp[i].first >= emp[j].first and emp[i].second < emp[j].second){
                    good[j] = true;
                }
                else if (emp[i].first > emp[j].first and emp[i].second <= emp[j].second){
                    good[j] = true;
                }
                else if (emp[j].first >= emp[i].first and emp[j].second < emp[i].second){
                    good[i] = true;
                }
                else if (emp[j].first > emp[i].first and emp[j].second <= emp[i].second){
                    good[i] = true;
                }
            }
        }
    }

    
    FOR(i, 0, n){
        if (good[i]){
            good_v.push_back(emp[i]);
        }
        else{
            bad_v.push_back(emp[i]);
        }
    }

    sort(bad_v.begin(), bad_v.end(), sort_bad);
    sort(good_v.begin(), good_v.end(), sort_good);

    FOR(i, 0, bad_v.size())
        PAIR(bad_v[i]);

    #ifdef TESTING
        cout << endl;
    #endif
    FOR(i, 0, good_v.size())
        PAIR(good_v[i]);    

    // DP on bad workers
    vvi DP(p, vi(bad_v.size(), -INT_MAX));

    FOR(i, 0, p){   // number of cuts
        FOR(j, i, bad_v.size()){   // position until where to cut
            if (i == 0){
                // Base case
                DP[i][j] = interv(0, j, bad_v);
                
            }
            else{
                FOR(k, i, j+1){  // position of the last cut
                    DP[i][j] =   max(DP[i][j], 
                                    (DP[i-1][k-1] > 0 and interv(k, j, bad_v) > 0 ? DP[i-1][k-1] + interv(k, j, bad_v) : -INT_MAX ));  
                }
            }
        }
        
    }

    #ifdef TESTING
        FOR(i,0,DP.size()){
            FOR(j,0,DP[i].size()){
                //cout<< DP[i][j] << "\t";
            }
            //cout << "endline" << endl;
        }
    #endif

    // Put singular good workers

    int res = -INT_MAX;
    FOR(i, 0, p){
        if (i == 0)
            // Base case, we put no good worker
            res = max(res, DP[p-1][DP[p-1].size()-1]);
        // Try to combine good and bad employees
        else if (i <= good_v.size() and p-i-1 >= 0)
            res = max(res, summation(good_v, i-1) + DP[p-i-1][DP[p-i-1].size()-1]);
    }

    cout << res << endl;


    return 0;
}