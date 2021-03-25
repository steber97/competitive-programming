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
        int n, k;
        string s;
        cin >> n >> k;
        cin >> s;
        int result = 0;
        int num_asterisks = 0;
        FOR(i,0,s.size()){
            if (s[i] == '*')
                num_asterisks ++;
        }
        if (num_asterisks <= 2){
            cout << num_asterisks << endl;
        }
        else{
            int last_pos = 0;
            FOR(i,0,s.size()){
                if (s[i] == '*'){
                    last_pos = i;
                    result ++;
                    break;
                }
            }
            bool finish = false;
            while(!finish){
                int best = last_pos;
                FOR(i,last_pos, last_pos + k + 1){
                    if (i == s.size()){
                        finish = true;
                        break;
                    }
                    if (s[i] == '*'){
                        best = i;
                    }
                }
                if (best != last_pos){
                    result ++;
                    last_pos = best;
                }
                else{
                    finish = true;
                }
            }
            cout << result << endl;
        }
    }
    return 0;
}