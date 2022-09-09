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
#define MAT(x) for (int u = 0; u < x.size(); u++) { for (int o = 0; o<x[u].size(); o++) cout << x[u][o] << " "; cout << endl;} cout << endl
#define COUT(x) cout << x 

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#define MAT(x)
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

bool compare(pair<ll,ll> p1, pair<ll,ll> p2){
    return p1.first < p2.first;
}

int main(){
    vector<ll> numbers;
    ll two = 1, three=1;
    FOR(i,0,32){
        FOR(j,0,32){
            if(two*three < 4294967296){
                numbers.push_back(two*three);
                three*=3;
            }
            else{
                break;
            }
        }
        three=1;
        two*=2;
    }
    
    sort(numbers.begin(), numbers.end());

    ll t;
    cin >> t;
    while(t!=0){
        vector<ll>::iterator it = lower_bound(numbers.begin(), numbers.end(), t);
        cout << numbers[it-numbers.begin()] << endl;
        cin >> t;
    }
    return 0;    
}