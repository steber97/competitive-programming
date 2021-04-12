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

vector<long long> primes = {5, 11, 101, 1019, 10039, 100057, 1000081, 10000139, 100000073};

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        ll a, b, c;
        cin >> a >> b >> c ;
        ll prime = primes[c-1];
        ll a2 = prime;
        while(to_string(a2).size() != a){
            a2 *= 2ll;
        }
        ll b2 = prime;
        while(to_string(b2).size() != b){
            b2 *= 3ll;
        }
        cout << a2 << " "<< b2 << endl;
    }
}