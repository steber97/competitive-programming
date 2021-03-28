#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>

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
        int n;
        cin >> n;
        vi v(n);
        FOR(i,0,n)
            cin >> v[i];
        int count = 0;
        FOR(i,0,v.size()-1){
            int min = -1;
            FOR(j,i,v.size()){
                if (min == -1 || v[min] > v[j]){
                    min = j;
                }
            }
            reverse(v.begin()+i, v.begin()+min+1);
            VECT(v);
            count += (min + 1 - i);
        }
        cout << "Case #" << t+1 << ": " << count << endl;
    }

    return 0;
}