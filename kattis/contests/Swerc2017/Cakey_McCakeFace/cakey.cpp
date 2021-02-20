
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

int main(){

    unordered_map<int, int>mym;    // mymap

    int N,M;
    cin >> N >> M ;

    vll v1, v2;
    FOR(i,0,N){
        int temp;
        cin >> temp;
        v1.push_back(temp);
    }
    FOR(i,0,M){
        int temp;
        cin >> temp;
        v2.push_back(temp);
    }

    FOR(i,0,N){
        FOR(j,0,M){
            if (v1[i] <= v2[j]){
                if (mym.find(v2[j]-v1[i]) == mym.end()){
                    mym[v2[j]-v1[i]] = 0;
                }
                mym[v2[j]-v1[i]] += 1;
            }
        }
    }

    ii res = {INT_MAX, 0};   // value, occurrences

    for(ii i: mym){
        VALUE(i.first);
        if (i.second > res.second or (i.second == res.second and i.first < res.first) ){
            res = {i.first, i.second};
        }
    }

    if (res.first == INT_MAX)
        res.first = 0;
    cout << res.first << endl;
    return 0;
}