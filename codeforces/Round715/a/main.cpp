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

vector<char> letters;




int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vi odd, even;
        FOR(i,0,n){
            int r;
            cin >> r;
            if (r%2==0)
                even.push_back(r);
            else
                odd.push_back(r);
        }
        FOR(i,0,even.size()){
            cout << even[i] << " ";
        }
        FOR(i,0,odd.size())
            cout << odd[i] << " ";
        cout << endl;
    }
    return 0;
}