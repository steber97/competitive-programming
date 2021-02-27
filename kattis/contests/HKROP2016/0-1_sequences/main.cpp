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

ll pow_mod(ll k, ll mod){
    ll res = 1;
    FOR(i, 0, k){
        res *= ((ll)2);
        res %= mod;
    }
    return res;
}

int main(){
    
    string s;
    cin >> s;
    ll mod = 1000000007;

    VALUE (-mod+1 % mod);
    ll k = ((ll)0);
    FOR(i,0,s.size()){
        if (s[i] == '?'){
            k++;
        }
    }

    ll ones_before = (ll(0));
    ll quest_before = ((ll)0);
    ll res = (ll(0));
    ll two_k = pow_mod(k, mod);
    ll two_k_div_2 = pow_mod(k-1, mod);
    ll two_k_div_4 = pow_mod(k-2, mod);
    VALUE(two_k);
    FOR(i,0,s.size()){
        if (s[i] == '?'){
            res += ((two_k_div_2 * ones_before) % mod);
            res += ((two_k_div_4 * quest_before) % mod);
            quest_before ++;
        }
        else if (s[i] == '1'){
            ones_before ++;
        }
        else if (s[i] == '0'){
            res += ((two_k * ones_before) % mod); 
            res += ((two_k_div_2 * quest_before) % mod);
        }
    }
    res %= mod;
    cout << (res < ((ll)0) ? res + mod : res) << endl;
    return 0;
}