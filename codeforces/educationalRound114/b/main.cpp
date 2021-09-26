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
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int mymax, mymin;
        mymax = a-1 + b-1 + c-1;
        mymin = max(0, a - b - c - 1);
        mymin = max(mymin, max(0, b - a - c - 1));
        mymin = max(mymin, max(0, c - a - b - 1));
        if (d >= mymin && d <= mymax)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}