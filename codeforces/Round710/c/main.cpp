#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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
        unordered_set<string> myset;
        string s1, s2;
        cin >> s1 >> s2;
        FOR(i,0,s1.size()){
            FOR(l, 1, s1.size()-i+1){
                VALUE(s1.substr(i, l));
                myset.insert(s1.substr(i, l));
            }
        }
        int maxN = 0;
        FOR(i,0,s2.size()){
            FOR(l, 1, s2.size()-i+1){
                if (myset.find(s2.substr(i, l)) != myset.end()){
                    maxN = max(maxN, l);
                }
            }
        }
        cout << s1.size() + s2.size() - 2*maxN << endl;
    }
    return 0;
}