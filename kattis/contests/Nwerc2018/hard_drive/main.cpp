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
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
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

    int n, c, b;
    cin >> n >> c >> b;
    unordered_set<int> z;
    vi soluz(n, 0);
    FOR(i,0,b){
        int zi;
        cin >> zi;
        zi --;
        z.insert(zi);
    }
    int init ;
    int j = 0;
    if (c % 2 == 1){
        soluz[0] = 1;
        init = 2;
        c--;
    }
    else{
        soluz[0] = 0;
        init = 1;
    }

    while(init < n){
        if (c > 0){
            if (z.find(init) == z.end()){
                soluz[init] = 1;
                c-=2;
                init += 2;
            }
            else{
                init ++;
            }
        }
        else{
            break;
        }
    }

    FOR(i,0,n){
        cout << soluz[i];
    }
    cout << endl;

    return 0;
}