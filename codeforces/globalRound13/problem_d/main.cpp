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

    int n;
    cin >> n;

    FOR(q,0,n){
        int a,b;
        cin >> a >> b;

        if (a > b){
            cout << "NO" << endl;
        }
        else{
            bitset<35> bita(a);
            bitset<35> bitb(b);
            int counta= 0 , countb=0;
            bool done = true;
            FOR(i,0,35){
                if (bita[i]==1)
                    counta++;
                if(bitb[i] ==1)
                    countb++;
                if (countb > counta){
                    cout << "NO" << endl;
                    done = false;
                    break;
                }
            }
            if(done)
                cout << "YES" << endl;
        }
    }
    return 0;    
}