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


int main(){
    int n; cin >> n;
    FOR(t,0,n){
        string s; cin >> s;

        ll consones = 0;
        ll maxones = 0;
        ll i = 0;
        while(i<s.size()){
            ll j=i;
            if (s[j]=='1'){
                while(j<s.size() && s[j]=='1'){
                    j++;
                }
                maxones = max(maxones, j-i);
            }
            i=j+1;
        }
        if (maxones == s.size()){
            cout << s.size() * s.size() << endl;
        }
        else if (maxones == 0){
            cout << 0 << endl;
        }
        else{
            if ((s.size()>1) && (s[0]=='1') && (s.back()=='1')){
                ll i = 0; 
                while(s[i]=='1'){
                    i++;
                }
                ll j = (ll)s.size()-1LL;
                while(s[j]=='1'){
                    j--;
                }
                maxones = max(maxones, i + (((ll)s.size())-j-1LL));
            }
            maxones++;
            VALUE(maxones);
            if ((maxones%2LL) == 0LL){
                cout << (maxones/2LL) * (maxones/2LL) << endl;
            }
            else{
                cout << (maxones/2LL) * (maxones/2LL + 1LL) << endl;
            }
        }


        
    }
    return 0;
}