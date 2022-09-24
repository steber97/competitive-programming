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




int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int b;
        cin >> b;
        vll v(b-1);
        FOR(i,0,b-1){
            cin >> v[i];
        }

        ll bestval = 0;
        ii bestinter = {b,b};
        int end = b-1;
        ll running = 0;

        for(int i = b-2; i>=0; i--){
            if (running + v[i] >= 0){
                running += v[i];
                if (running > bestval || (running == bestval && ((bestinter.second - bestinter.first) <= end-i))){
                    bestval = running;
                    bestinter.first = i; bestinter.second = end;
                }
            }
            else{
                end = i;
                running = 0;
            }
        }
        if (bestinter.first != b){
            cout << "The nicest part of route " << t+1 << " is between stops " << bestinter.first+1 << " and " << bestinter.second+1 << endl;
        }
        else{
            cout << "Route " << t+1 << " has no nice parts" << endl;
        }
    }
    return 0;
}