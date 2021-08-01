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
    int n,m;
    cin >> n >> m;
    vector<priority_queue<int>> nob(n);
    vector<priority_queue<int>> rem(n);
    int result = 0;

    FOR(i,0,m){
        int a, b;
        cin >> a >> b;
        a--; b--;
        if ((nob[a].empty() or (nob[a].top() < a)) and (b > a)){
            result ++;
        }
        if ((nob[b].empty() or (nob[b].top() < b)) and (a > b)){
            result ++;
        }
        nob[a].push(b);
        nob[b].push(a);
    }

    FOR(i,0,n){
        VALUE(nob[i].top());
    }

    int Q;
    cin >> Q;
    VALUE(Q);
    FOR(q,0,Q){
        int a;
        cin >> a;
        VALUE(a);
        if (a == 1){
            // add
            int n1, n2;
            cin >> n1 >> n2; n1--; n2--; 
            if ((nob[n1].empty() or (nob[n1].top() < n1)) and (n2 > n1)){
                result ++;
            }
            if ((nob[n2].empty() or (nob[n2].top() < n2)) and (n1 > n2)){
                result ++;
            }
            nob[n1].push(n2);
            nob[n2].push(n1);
            VALUE(n1);
            VALUE(n2);
            VALUE(nob[n1].top());
            VALUE(nob[n2].top());
        }
        else if (a == 2){
            // Remove
            int n1, n2;
            cin >> n1 >> n2; n1--; n2--;
            bool prev_up_1, prev_up_2;
            prev_up_1 = nob[n1].top() > n1;
            prev_up_2 = nob[n2].top() > n2;
            rem[n1].push(n2);
            rem[n2].push(n1);
            while(!rem[n1].empty() and rem[n1].top() >= nob[n1].top()){
                rem[n1].pop(); nob[n1].pop();
            }

            while(!rem[n2].empty() and rem[n2].top() >= nob[n2].top()){
                rem[n2].pop(); nob[n2].pop();
            }
            if (prev_up_1 and (nob[n1].empty() or nob[n1].top() < n1))
                result --;
            if (prev_up_2 and (nob[n2].empty() or nob[n2].top() < n2))
                result --;
        }
        else{
            cout << n - result << endl;
        }
    }
 
    return 0;
}  