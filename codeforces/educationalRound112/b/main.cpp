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
    int T;
    cin >> T;
    FOR(t,0,T){
        int x1, y1, x2, y2;
        int W, H;
        int w, h;
        cin >> W >> H;
        cin >> x1 >> y1 >> x2 >> y2;
        cin >> w >> h;

        int best = max(W, H) + 1;

        // fit to the left.
        if (x1 >= w){
            best = 0;
        }
        else {
            if (x2 - x1 + w > W){

            }
            else{
                best = min(best, w - x1);
            }
        }

        // fit to the right
        if (W - x2 >= w){
            best = 0;
        }
        else{
            if (x2 - x1 + w > W){

            }
            else{
                best = min(best, x2 - (W - w));
            }
        }

        // fit above
        if (H - y2 >= h){
            best = 0;
        }
        else{
            if (y2 - y1 + h > H){

            }
            else{
                best = min(best, y2 - (H - h));
            }
        }
        // fit below
        if (y1 >= h){
            best = 0;
        }
        else{
            if (y2 - y1 + h > H){

            }
            else{
                best = min(best, h - y1);
            }
        }
        if (best < max(W, H) + 1){
            cout << best << endl;
        }
        else{
            cout << -1 << endl;
        }
    }
    return 0;
}