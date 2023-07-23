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
    int T; cin >> T;
    FOR(t,0,T){
        int n; cin >> n;
        vi v(n);
        FOR(i,0,n){
            cin >> v[i];
        }
        vi vcopy(v);
        sort(vcopy.begin(), vcopy.end());
        int prev;
        bool next_appears;
        if (vcopy[0]!=0){
            prev = 0;
            next_appears = vcopy[0]==1;
        }
        else{
            bool set = false;
            FOR(i,0,n-1){
                if (vcopy[i+1]-vcopy[i] > 1){
                    prev = vcopy[i]+1;
                    set = true;
                    next_appears = vcopy[i+1]==prev+1;
                    break;
                }
            }
            if (!set){
                prev  = vcopy.back()+1;
                next_appears = false;
            }
        }
        VALUE(prev);
        VALUE(next_appears);
        if (!next_appears){
            cout << (v.size() == prev ? "NO" : "YES") << endl;
        }
        else{
            int minnext = v.size()-1; int maxnext = 0;
            FOR(i,0,n){
                if (v[i] == prev+1){
                    minnext = min(minnext, i);
                    maxnext = max(maxnext, i);
                }
            }
            VALUE(minnext);
            VALUE(maxnext);
            unordered_set<int> numbers;
            FOR(i,0,n){
                if (i<minnext || i > maxnext){
                    numbers.insert(v[i]);
                }
            }
            bool cando = true;
            FOR(i,0,prev){
                if (numbers.find(i) == numbers.end())
                    cando = false;
            }
            cout << (cando? "YES" : "NO") << endl;
        }
    }
    return 0;
}