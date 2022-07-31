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

#define len 65538LL
// #define len 12LL

int main(){
    int n;
    while(true){
        cin >> n;
        vll frequencies(len, 0LL);
        FOR(i,0,n){
            int t;
            cin >> t;
            frequencies[t]++;
        }
        vll cum_sum(len, 0LL);
        cum_sum[0] = frequencies[0];
        FOR(i,1,len){
            cum_sum[i] = cum_sum[i-1] + frequencies[i];
        }
        
        ll sum_left = 0LL;
        ll sum_right = 0LL;
        for(ll i = 1LL; i<len; i++){
            sum_right += i * frequencies[i];
        }
        
        ll A = 0LL;
        ll min_val = sum_right;
        ll fr = frequencies[0];
        int counter = 1;
        for(ll i = 1LL; i<len; i++){
            sum_left += cum_sum[i-1];
            sum_right -= *(cum_sum.end()-1) - cum_sum[i-1];
            if (sum_left + sum_right < min_val){
                A = i;
                min_val = sum_left + sum_right;
                fr = frequencies[i];
                counter = 1;
            }
            else if (sum_left + sum_right == min_val){
                VALUE(i);
                counter ++;
                fr += frequencies[i];
            }
                
        }
        
        if (cin.eof())
            break;
        VALUE(frequencies[16152]);
        VALUE(frequencies[16153]);
        VALUE(frequencies[16154]);
        VALUE(frequencies[16155]);
        cout << A << " " << fr << " " << counter << endl;
    }
    return 0;    
}