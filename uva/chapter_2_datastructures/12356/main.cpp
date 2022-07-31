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

int find_next_left(vi& v, int a){
    if (v[v[a]-1] == -1){
        return v[a];
    }
    v[a] = find_next_left(v, v[a]-1);
    return v[a];
}

int find_next_right(vi& v, int a){
    VALUE(a);
    if (v[v[a]+1] == -1){
        return v[a];
    }
    v[a] = find_next_right(v, v[a]+1);
    return v[a];
}

int main(){
    while (true){
        int n,s;
        cin >> n >> s;
        if (n==0 && s==0){
            break;
        }
        vi left(n+2, -1);
        vi right(n+2, -1);
        FOR(i,0,s){
            int a,b;
            cin >> a >> b;
            if (right[b+1] == -1)
                right[a] = b;
            else
                right[a] = find_next_right(right, b+1);
            if (left[a-1] == -1)
                left[b] = a;
            else
                left[b] = find_next_left(left, a-1);
            
            
            int r1, r2;
            if (left[a-1] == -1){
                r1 = a-1;
            }
            else{
                left[b] = find_next_left(left, a-1);
                r1 = left[b] - 1;
            }

            if (right[b+1] == -1){
                r2 = b+1;
            }
            else{
                right[a] = find_next_right(right, b+1);
                r2 = right[a]+1;
            }
            VECT(right);
            COUT(endl);
            cout << (r1 != 0 ? to_string(r1) : "*") << " " << (r2 != n + 1 ? to_string(r2) : "*") << endl;
        }
        cout << "-" << endl;
    }
    return 0;    
}