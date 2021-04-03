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
        int n;
        cin >> n;
        vii cumulative(n);
        string v;
        cin >> v;
        FOR(i,0,n){
            if (i == 0){
                cumulative[i] = {0,0};
            }
            else{
                cumulative[i] = cumulative[i-1];
            }

            if (v[i] == '0')
                cumulative[i].first++;
            else
                cumulative[i].second++;
            
        }
        // FOR(i,0,n)
        //     cout << cumulative[i].first <<  " " << cumulative[i].second << endl;
        string b;
        cin >> b;
        int counter=0; // Always modulo 2
        bool finish = false;
        for(int i = n-1; i >= 0; i--){
            if (counter == 0){
                if (v[i] == b[i]){
                    // ok!
                }
                else{
                    if (cumulative[i].first == cumulative[i].second){
                        // Ok! change
                        counter ++;
                        counter %= 2;
                    }
                    else{
                        finish = true;
                    }
                }
            }
            else{
                if (v[i] != b[i]){
                    // ok!
                }
                else{
                    if (cumulative[i].first == cumulative[i].second){
                        // Ok! change
                        counter ++;
                        counter %= 2;
                    }
                    else{
                        finish = true;
                    }
                } 
            }

        }
        if (!finish)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;    
}