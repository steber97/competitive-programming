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
    
bool mysort(pair<ii, int>& p1, pair<ii, int>& p2){
    if (p1.first.second < p2.first.second)
        return true;
    return p1.first.first < p2.first.first;
}

int main(){
    int T;
    cin >> T;
    for(int t = 0; t < T; t++){
        int n;
        cin >> n;
        vi per(n);
        FOR(i,0,n)
            cin >> per[i];
        vector<pair<ii, int>> inter(n);
        FOR(i,0,n){
            if (per[i] == 0){
                inter[i].first.first = i+2;
                inter[i].first.second = n;
                inter[i].second = i;
            }
            else{
                inter[i].first.first = (i+1) / (per[i]+1) + 1;
                inter[i].first.second = (i+1) / (per[i]); 
                inter[i].second = i;
            }
            
        }
        FOR(i,0,n)
            PAIR(inter[i].first);
        sort(inter.begin(), inter.end(), mysort);
        vi result(n);
        FOR(i,0,n){
            result[inter[i].second] = i+1;
        }
        FOR(i,0,n)
            cout << result[i] << " ";
        cout << endl;
    }
    return 0;
}