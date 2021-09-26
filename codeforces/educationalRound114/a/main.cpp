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


void print_seq(vector<bool>& opened){
    FOR(i,0,opened.size()){
        cout << (opened[i] ? "(" : ")");
    }
    cout << endl;
}

int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vector<bool> opened(n*2);
        FOR(i,0,n)
        {
            opened[i] = true;
            opened[2 * n - i - 1] = false;
        }
        print_seq(opened);
        for (int j = 1; j < n; j++){
            opened[n - j] = !opened[n - j];
            opened[n + j - 1] = !opened[n + j - 1];
            if (j > 1)
            {
                opened[n - j + 1] = !opened[n - j + 1];
                opened[n + j - 2] = !opened[n + j - 2];
            }
            print_seq(opened);
        }
    }
    return 0;
}