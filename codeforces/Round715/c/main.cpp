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

vector<char> letters;

vector<vector<long long>> dp(3000, vector<long long>(3000, -1LL));
vector<pair<long long, long long>> p;

long long fatina(int start, int end){
    if (start == end){
        return 0LL;
    }
    else if (dp[start][end] != -1LL){
        return dp[start][end];
    }
    else{
        ll r1 = fatina(start+1, end);
        ll r2 = fatina(start, end-1);
        dp[start][end] = min(
            r1 + (p[end].first - p[start].first)*p[start].second,
            r2 + (p[end].first - p[start].first)*p[end].second
        );
        return dp[start][end];
    }
}

int main(){
    int n;
    cin >> n;
    vll num(n);
    FOR(i,0,n)
        cin >> num[i];
    sort(num.begin(), num.end());
    ll total = LONG_LONG_MAX;
      // value, frequency
    FOR(i,0,n){
        if (p.size()==0){
            p.push_back({num[i], 1LL});
        }
        else if ((*prev(p.end())).first == num[i] ) {
            (*prev(p.end())).second++;
        }
        else{
            p.push_back({num[i], 1LL});
        }
    }

    total = fatina(0, p.size()-1);
    
    cout << total << endl;
    return 0;
}