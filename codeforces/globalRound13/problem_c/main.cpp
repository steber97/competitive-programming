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



ll LSOne(ll b){
    return b & (-b);
}

class FenwickTree{
    private:
        vector<ll> ft;
    public:
        FenwickTree(ll n){
            ft.assign(n+1, 0);
        }

        ll rsq(ll b){
            ll sum = (ll(0));
            for (; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        ll rsq(int a, int b){
            if (a == 1)
                return rsq(b);
            return rsq(b) - rsq(a-1);
        }
        void adjust (int k, ll v){
            for (; k<int(ft.size()); k += LSOne(k)){
                ft[k] += v;
            }
        }
        void print_fenwick_tree(){
            for (int i = 0; i<ft.size(); i++)
                cout << ft[i] << " ";
            cout << endl;
        }
};



int main(){

    // vector<ll> V = {1,2,5,4,3,7,3};
    // FenwickTree ft(V.size());
    // for (int i = 1; i<=V.size(); i++){
    //     ft.adjust(i, V[i-1]);
    // }

    // //ft.print_fenwick_tree();

    // COUT(ft.rsq(1,3)); COUT(endl);

    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vll s(n);
        FOR(i,0,n)
            cin >> s[i];
        FenwickTree ft(n);
        ll res = ((ll)0);
        FOR(i,0,n){
            ll avanzo = ft.rsq(i+1) - s[i] + (ll(1));
            COUT(avanzo); COUT(" "); COUT(ft.rsq(i+1)); COUT(endl);
            if (-avanzo > (ll(0))){
                // we have to finish it.
                res -= avanzo;
            }
            if (i < s.size()-1){
                ft.adjust(i+2+1, (ll(1)));
                if (i + (int(s[i])) + 1 < s.size()){
                    ft.adjust(i + (int(s[i])) + 1 + 1, (ll(-1)));
                }
            }
            if (avanzo > (ll (0))){
                if (i < s.size()){
                    ft.adjust(i+1+1, (ll(avanzo)));
                    if (i<s.size()-1)
                        ft.adjust(i+2+1, (ll(-avanzo)));
                }
            }

            
        }
        cout << res << endl;
    }
    return 0;    
}