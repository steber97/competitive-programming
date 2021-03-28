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

vi fatina(int n, int c){
    VALUE(n); VALUE(c);
    if (n == 1 && c == 0){
        return {1};
    }
    else{
        assert (n > 1 and c >= 1);
        if (n + n - 2 > c){
            // Do not rotate
            vi result;
            result.push_back(n);
            vi end = fatina(n-1, c-1);
            FOR(i,0,end.size())
                result.push_back(end[i]);
            return result;
        }
        else{
            vi start = fatina(n-1, c-n);
            reverse(start.begin(), start.end());
            start.push_back(n);
            return start;
        }
    }
}


int main(){
    int T;
    cin >> T;
    FOR(t,0,T){
        int n, c;
        cin >> n >> c;
        int sum =0;
        FOR(i,2,n+1)
            sum += i;

        if (c < n - 1 || c > sum){
            cout << "Case #" << t+1 << ": IMPOSSIBLE" << endl;
        }
        else{
            vi result = fatina(n,c);
            cout << "Case #" << t+1 << ": ";
            FOR(i,0,n){
                cout << n - result[i] + 1<< " ";
            }
            cout << endl;
        }
    }

    return 0;
}