#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

#define TESTING

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
const int MAXN = 200010;
int INF = 300000;

int LSOne(int b){
    return b & (-b);
}

class FenwickTree{
    private:
        vector<int> ft;
    public:
        FenwickTree(int n){
            ft.assign(n+1, 0);
        }

        int rsq(int b){
            int sum = 0;
            for (; b; b -= LSOne(b)){
                sum += ft[b];
            }
            return sum;
        }

        int rsq(int a, int b){
            if (a == 1)
                return rsq(b);
            return rsq(b) - rsq(a-1);
        }
        void adjust (int k, int v){
            for (; k<int(ft.size()); k += LSOne(k)){
                ft[k] += v;
            }
        }
        void print_fenwick_tree(){
            for (int i = 0; i<ft.size(); i++)
                cout << ft[i] << " ";
            cout << endl;
        }
};


int main(){
    int T = 1;
    while(true){
        int n;
        cin >> n;
        if (n == 0)
            break;
        if (T!=1)
            cout << endl;
        cout << "Case " << T << ":" << endl;
        vi pot(n);
        FOR(i, 0, n){
            cin >> pot[i];
        }

        FenwickTree ft(n);
        FOR(i,0,n){
            ft.adjust(i+1, pot[i]);
        }

        while(true){
            string s;
            cin >> s;
            if (s=="END"){
                break;
            }
            else if (s=="M"){
                int x,y;
                cin >> x >> y;
                cout << ft.rsq(x, y) << endl;
            }
            else if (s=="S"){
                int x,r;
                cin >> x >> r;
                int prev = ft.rsq(x, x);
                ft.adjust(x, r - prev);
            }
        }
        T++;
    }
    return 0;    
}