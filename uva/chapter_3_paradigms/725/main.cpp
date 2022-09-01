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
    int t = 0;
    while(true){
        int n;
        cin >> n;
        if (n==0)
            break;
        if (t>0){
            cout << endl;
        }
        t++;
        int sols = 0;
        FOR(i,1234,98766){
            int n1 = i;
            int n2 = i * n;
            if (n2 < 98766){
                unordered_set<int> digits;
                FOR(k,0,5){
                    digits.insert(n1%10);
                    digits.insert(n2%10);
                    n2 -= (n2%10);
                    n1 -= (n1%10);
                    n1/=10;
                    n2/=10;
                }
                if (digits.size() == 10){
                    sols++;
                    cout << i * n << " / " << (i < 10000 ? "0" + to_string(i) : to_string(i)) << " = " << n << endl;
                }
            }
            else 
                break;
        }
        if (sols==0){
            cout << "There are no solutions for " << n << "." << endl;
        }
    }
    return 0;
}