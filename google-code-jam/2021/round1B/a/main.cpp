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

ll find_rotation(vll& permut, ll i){
    ll begin = permut[0] - (i+1LL) * 3600000000000LL;
    ll end = permut[0];
    VALUE(i);
    VALUE(begin);
    VALUE(end);
    while(begin < end){
        ll mid = (end + begin) / 2LL;
        // win:
        ll nanos = permut[0] - mid;
        ll hours = nanos / 1000000000LL / 60LL / 60LL;
        ll min = nanos / 1000000000LL / 60LL;
        ll secs = nanos / 1000000000LL;
        VALUE(min);
        if (((min - hours * 60LL) * 60LL * 1000000000LL * 12LL) == (permut[1] - mid)){
            // check seconds
            if (((secs - min * 60LL) * 1000000000LL * 720LL) == permut[2] - mid){
                return mid;
            }
            if (((secs - min * 60LL) * 1000000000LL * 720LL) < permut[2] - mid){
                end = mid-1LL;
            }
            else{
                begin = mid+1LL;
            }
        }
        else{
            if (((min - hours * 60LL) * 60LL * 1000000000LL * 12LL) < (permut[1] - mid)){
                end = mid-1LL;
            }
            else{
                begin = mid+1LL;
            }
        }

    }
    return -1LL;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        ll a, b, c;
        cin >> a >> b >> c;
        // hour-min-sec
        vector<vector<ll>> permuts = {
            {a, b, c},
            {b, a, c},
            {b, c, a},
            {a, c, b},
            {c, a, b},
            {c, b, a},
        };
        bool found = false;
        ll rotation = -1LL;
        ll hours, min, seconds, nanos;
        for (auto permut: permuts){
            VALUE(permut[0]);
            VALUE(permut[1]);
            VALUE(permut[2]);
            if (found)
                break;
            for (ll i = 0LL; i < 12LL; i++){
                rotation = find_rotation(permut, i);
                if (rotation == -1LL){
                    // repeat
                }
                else{
                    // we have found a good value for the rotation.
                    found = true;
                    nanos =  (permut[0] - rotation);
                    hours = nanos / 1000000000LL / 60LL / 60LL;
                    min = nanos / 12LL / 1000000000LL / 60LL;
                    seconds = nanos / 720LL / 1000000000LL;
                    break;
                }
                if (i == 0)
                    break;
            }
        }
        if (found){
           cout << "Case #" << t+1 << ": " << hours << " " << min << " " << seconds<< " " << nanos << endl;
        }
        else{
            cout << "Something went wrong" << endl;
        }
    }
    return 0;
}