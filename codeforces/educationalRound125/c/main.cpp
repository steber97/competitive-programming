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
    FOR(t,0,T)    {
        int n;
        string v;
        cin >> n;
        cin >> v;

        int counter = 0;
        int index = 0;
        while(index < n) {
            if (v[index] == '('){
                if (index == n-1){
                    break;
                }
                else {
                    /// both () and (( are good!
                    counter ++;
                    index += 2;
                }
            }
            else {
                if (index == n-1){
                    break;
                }
                else{
                    int j = index + 1;
                    while(j < n){
                        if (v[j] == '(')
                            j++;
                        else 
                            break;
                    }
                    if (j == n)
                        break;
                    else {
                        counter ++;
                        index = j + 1;
                    }
                }
            }
        }
        cout << counter << " " << n - index << endl;
    }
    return 0;
}