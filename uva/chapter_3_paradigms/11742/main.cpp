#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << endl; cout << endl
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
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001


vvi permutations(vi& so_far, unordered_set<int>& remaining){
    if (remaining.size() == 1){
        vi res_v(so_far.size()+1);
        FOR(i,0,so_far.size())
            res_v[i] = so_far[i];
        res_v[so_far.size()] = *(remaining.begin());
        return {res_v};
    }
    else{
        vi rem_v(remaining.size());
        vvi res;
        int i = 0;
        for(int r: remaining){
            rem_v[i] = r;
            i++;
        }
        FOR(j,0,rem_v.size()){
            so_far.push_back(rem_v[j]);
            remaining.erase(rem_v[j]);
            vvi tmp = permutations(so_far, remaining);
            res.insert(res.end(), tmp.begin(), tmp.end());
            so_far.resize(so_far.size()-1);
            remaining.insert(rem_v[j]);
        }
        return res;
    }
}

int main(){
    while(true){
        int n,m;
        cin >> n >> m;
        if (n==0)
            break;
        vii constr(m);
        vi dist(m);
        FOR(i,0,m)
            cin >> constr[i].first >> constr[i].second >> dist[i];

        vi so_far = {};
        unordered_set<int> remaining;
        FOR(i,0,n)
            remaining.insert(i);
        vvi permut = permutations(so_far, remaining);
        
        int res=0;
        FOR(i,0,permut.size()){
            vi pos(n);
            FOR(j,0,permut[i].size()){
                pos[permut[i][j]] = j;
            }
            bool sat = true;
            FOR(j,0,m){
                if (dist[j]>0){
                    if(abs(pos[constr[j].first] - pos[constr[j].second]) > dist[j])
                        sat = false;
                }
                else {
                    if (abs(pos[constr[j].first] - pos[constr[j].second]) < -dist[j])
                        sat = false;
                }
            }
            if (sat)
                res++;
        }
        cout << res << endl;

    }
    
    
    return 0;
}