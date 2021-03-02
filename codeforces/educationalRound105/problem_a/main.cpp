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
    
    int T;
    cin >> T;
    FOR(t,0,T){
        string s;
        cin >> s;
        vi s_i(s.size());
        FOR(i,0,s.size()){
            if (s[i]=='A')
                s_i[i] = 0;
            if (s[i]=='B')
                s_i[i] = 1;
            if (s[i]=='C')
                s_i[i] = 2;
        }
        vector<vector<bool>> combinations= {
            {true, true, true},
            {true, true, false},
            {true, false, true},
            {false, true, true},
            {true, false, false},
            {false, true, false},
            {false, false, true},
            {false, false, false}
        };

        bool win = false;
        for(vb c: combinations){
            int open=0;
            bool done = true;
            FOR(j,0,s_i.size()){
                if (c[s_i[j]])
                    open ++;
                else{
                    open--;
                    if (open<0)
                        done = false;
                }
            }
            if (open != 0)
                done = false;
            if (done)
                win = true;
        }
        cout << (win?"YES":"NO") << endl;
    }
    return 0;    
}