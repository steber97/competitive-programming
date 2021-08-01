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

struct p {
    queue<pair<int,int>> q;
    int put=0;
};

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        string enemy, grigor;
        cin >> enemy >> grigor;
        int counter = 0;
        FOR(i,0,n){
            // if we can reach the end, do it.
            if (enemy[i] == '0' and grigor[i] == '1'){
                counter ++;
                enemy[i] = '2';
            }
            else if (grigor[i] == '1'){
                if (i > 0 and enemy[i-1] == '1'){
                    counter ++;
                    enemy[i-1] = '2';
                }
                else if (i < n - 1 and enemy[i+1] == '1'){
                    counter ++;
                    enemy[i+1] = '2';
                }
            }
        }
        cout << counter << endl;
    }
    return 0;
}