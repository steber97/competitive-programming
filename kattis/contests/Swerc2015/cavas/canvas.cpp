#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <queue>

using namespace std;

//#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
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
    for (int t = 0; t<T; t++){
        int N;
        cin >> N;

        ll values[N];
        for (int i = 0; i<N; i++){
            cin >> values[i];
        }

        // using grater extracts the smallest element of the queue!
        priority_queue<ll, vll, greater<ll> > mypq (values, values+N);

        ll res = 0LL;
        while(mypq.size() != 1){
            ll el1 = mypq.top();
            mypq.pop();
            ll el2 = mypq.top();    
            mypq.pop();
            res += (el1 + el2);
            mypq.push(el1 + el2);
        }

        cout << res << endl;
    }


    return 0;
}