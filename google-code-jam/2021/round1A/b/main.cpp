#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <random>

using namespace std;

// #define TESTING

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
    FOR(t,0,T)   {
        long long res = 0ll;
        int m;
        cin >> m;
        vll numbers(m), occur(m);
        ll sum=0ll;
        FOR(i,0,m){
            cin >> numbers[i] >> occur[i];
            sum += numbers[i] * occur[i];
        }
        ll lower = sum > 499ll*50ll? sum - 499ll*50ll : 1ll;
        for (ll n = sum; n >= lower; n--){
            ll res_sum = sum;
            ll res_n = n;
            FOR(i,0,m){
                ll taken = 0ll;
                while((res_n % numbers[i]) == 0ll){
                    res_n /= numbers[i];
                    res_sum -= numbers[i];
                    taken++;
                }
                if (taken > occur[i])
                    break;
                if (res_sum == n && res_n == 1ll){
                    res = n;
                    break;
                }
            }
            if (res != 0ll)
                break;
        }
        cout << "Case #" << t+1 << ": " << res << endl;
    }

    return 0;
}