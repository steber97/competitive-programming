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

double distance(double y, double x){
    return sqrt(x*x + y*y);
}

int main(){
    
    int T;
    cin >> T;
    FOR(t,0,T){
        int n;
        cin >> n;
        vector<double> m,d;
        FOR(i,0,2*n){
            int a,b;
            cin >> a >> b;
            if (a == 0)
                m.push_back(abs((double(b))));
            else
                d.push_back(abs((double(a))));
        }
        sort(m.begin(), m.end());
        sort(d.begin(), d.end());
        double res = 0.0;
        FOR(i,0,n){
            res += distance(m[i], d[i]);
        }
        cout << std::fixed << setprecision(11) << res << endl;
    }

    return 0;
}