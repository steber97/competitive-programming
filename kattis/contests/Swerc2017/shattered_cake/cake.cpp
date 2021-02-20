
#include <bits/stdc++.h>
#include <climits>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl

#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)


int main(){

    int n,l;
    cin >> l >> n;

    vector<pair<ll,ll>> cakes(n);
    FOR(i,0,n)
        cin >> cakes[i].first >> cakes[i].second;

    ll total = 0LL;

    FOR(i,0,n){
        total += cakes[i].first * cakes[i].second;
    }

    cout << total / l << endl;

    return 0;
}