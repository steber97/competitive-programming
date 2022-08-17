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
    int T;
    cin >> T;
    FOR(t,1,T+1){
        int n;
        cin >> n;
        unordered_map<int, int> map;
        vi num(n);
        FOR(i,0,n){
            cin >> num[i];
            map[num[i]] = 0;
        }
        int start = 0, end = 1, res = 1;
        map[num[start]] = 1;
        while(end != n){
            while((end != n) && (map[num[end]] == 0)){
                map[num[end]]++;
                end++;
            }
            if (end != n){
                res = max(res, end-start);
                while(num[start] != num[end]){
                    map[num[start]]--;
                    start ++;
                }
                map[num[start]]--;
                start++;
            }
            else{
                res = max(res, end-start);
            }
        }
        cout << res << endl;
    }
    return 0;    
}