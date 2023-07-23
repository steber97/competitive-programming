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
    FOR(i,0,n){
        string s; cin >> s;
        if (s.size()==1){
            if (s == "_"){
                cout << 2 << endl;
            }
            else{
                cout << 1 << endl;
            }
        } else{
            int res = 0;
            FOR(i,0,s.size()){
                if (i == 0){
                    if (s[i]=='_'){
                        res++;
                    }
                } if (i==s.size()-1 && s[i]=='_'){
                    res++;
                } else if (s[i]==s[i+1] && s[i]=='_'){
                    res++;
                }
            
                
            }
            cout << res << endl;
        }
    }
    return 0;
}