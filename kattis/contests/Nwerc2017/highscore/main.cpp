
#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define TESTING

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

ll sq(ll x){
    return x*x;
}

int main(){

    int n;
    cin >> n;
    FOR(k, 0, n){
        ll w;
        vll t(3);
        cin >> t[0] >> t[1] >> t[2] >> w;
        sort(t.begin(), t.end());
        ll best_score;
        best_score = sq(t[2] + w) + sq(t[1]) + sq(t[0]) + ((ll)7) * t[0];
        
        // Case 1, add t[1]-t[0] or w to t[0], and the remainder to t[2];
        ll add = min(w, t[1]-t[0]);
        ll rem = add == w ? (ll)0 : w - (t[1]-t[0]);
        best_score = max(
            best_score,
            sq(t[2]+rem) + sq(t[1]) + sq(t[0]+add) + ((ll)7) * (t[0]+add)
        );

        
        if (add == t[1]-t[0]){
            ll w2 = w-(t[1]-t[0]);
            add = min(t[2]-t[1], w2/((ll)2));
            rem = (add == w2/(ll)2) ? w2 % ((ll)2) : w2 - ((ll)2)*(t[2]-t[1]); 
            
            best_score = max(
                best_score,
                sq(t[2]+rem) + sq(t[1] + add) * ((ll)2) + ((ll)7) * (t[1]+add)    
            );
            if (add == t[2]-t[1]){
                ll w3 = w2 - ((ll)2) * (t[2]-t[1]);
                add = w3 / ((ll)3);
                rem = w3 % ((ll)3);
                best_score = max(
                    best_score,
                    sq(t[2]+rem+add) + ((ll)2) * sq(t[2]+add) + ((ll)7) * (t[2]+add)
                );
            }
        }

        cout << best_score << endl;
    }
    return 0;
}