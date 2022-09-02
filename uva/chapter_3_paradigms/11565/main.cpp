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
    int N;
    cin >> N;
    FOR(n,0,N){
        int a,b,c;
        cin >> a >> b >> c;
        bool found = false;
        for(int x=-101; x<101 && !found; x++){
            for(int y=x+1; y<101 && !found; y++){
                for(int z=y+1; z<101 && !found; z++){
                    if (((x+y+z) == a) && ((x*y*z == b) && ((x*x + y*y + z*z) == c))){
                        cout << x << " " << y << " " << z << endl;
                        found=1;
                    }
                }
            }
        }
        if (!found)
            cout << "No solution." << endl;
    }
    return 0;
}