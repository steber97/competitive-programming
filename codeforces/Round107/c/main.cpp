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
    int n, q;
    cin >> n >> q;
    vi first_color(50, -1);
    FOR(i,0,n){
        int t;
        cin >> t;
        t--;
        if (first_color[t] == -1)
            first_color[t] = i;
    }
    FOR(i,0,q){
        int t;
        cin >> t;
        t --;
        int res = first_color[t];
        FOR(j,0,50){
            if(first_color[j] != -1){
                if (j == t){
                    first_color[j] = 0;
                }
                else{
                    if (first_color[j] < res)
                        first_color[j] ++;

                }
            }
        }
        cout << res + 1 << " " ;
    
    }
    cout << endl;
    return 0;
}