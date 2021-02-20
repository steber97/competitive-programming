#include <bits/stdc++.h>
#include <climits>

using namespace std;

#define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second << endl
#define VECT(x) for (int i = 0; i<x.size(); i++) cout << x[i] << endl; cout << endl
#else 
#define DEBUG 
#define VALUE(x) 
#define PAIR(x) 
#define VECT(x)
#endif 

typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)


int N;
vvi A(3, vi());

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

pair<ll, ll> inversions(vi& A, vi& B){
    FenwickTree ft (N);  // used for B
    vi reverse(N+1);
    
    FOR(i,1,N+1){
        reverse[B[i]] = i;
    }

    //VECT(reverse);
    
    ll res = 0LL;
    ll correct = 0LL;
    FOR(i, 1, N+1){
        res += ft.rsq(1, N) - ft.rsq(1, reverse[A[i]]) ;
        correct += ft.rsq(1, reverse[A[i]]);
        ft.adjust(reverse[A[i]], 1);
    }
    
    return {res, correct};
}

int main(){

    cin >> N;
    
    FOR(i, 0, 3)
        A[i].resize(N+1);

    FOR(i,0,3)
        FOR(j, 1, N+1){
            cin >> A[i][j];
            A[i][j];
        }
    
    
    pair<ll, ll> res = {0LL, 0LL};   // inversions, correct
    FOR(i, 0, 3)
        FOR(j, i+1, 3){
            // try all pairs
            pair<ll,ll> t = inversions(A[i], A[j]);
            res.first += t.first;
            res.second += t.second;
        }

    res.second -= (res.first/2);
    res.second /= 3;

    cout << res.second << endl;



    return 0;
}