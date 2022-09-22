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




int main(){
    int n, l;
    cin >> n >> l;
    while(n != 0){
        vi d(n);
        vi k(l);
        FOR(i,0,n)
            cin >> d[i];
        FOR(i,0,l)
            cin >> k[i];

        sort(d.begin(), d.end());
        sort(k.begin(), k.end());

        int i=0,j=0,res=0;
        while(i<n && j<l){
            if (d[i] > k[j]){
                j++;
            }
            else{
                res+=k[j];
                i++;j++;
            }
        }
        if (i < n){
            cout << "Loowater is doomed!" << endl;
        }
        else{
            cout << res << endl;
        }
        cin >> n >> l;
    }
    
    return 0;
}