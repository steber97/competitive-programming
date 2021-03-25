#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

//#define TESTING

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

const int MAXN = 200010;
int INF = 300000;


class SegmentTree{
    private:
        vector<int> A, st;
        int n;
        // to get right and let children in a heap fashion.
        int left(int p){
            return p * 2;
        }
        int right(int p){
            return p*2 + 1;
        }

        void build(int p, int l, int r){
            if (l > r){

            }
            else if (l == r){
                st[p] = l;
            }
            else{
                build(left(p), l, (l+r)/2);
                build(right(p), (l+r)/2 + 1, r);
                if (A[st[left(p)]] < A[st[right(p)]]){
                    st[p] = st[left(p)];
                }
                else{
                    st[p] = st[right(p)];
                }
            }
        }

        int rmq(int p, int l, int r, int i, int j){
            int res;
            if (i > r || j < l){
                // If out of range:
                res = -1;
            }
            else{
                if (l >=  i && r <= j){
                    res = st[p];
                }
                else{
                    int p1 = rmq(left(p), l, (l+r) / 2, i, j);
                    int p2 = rmq(right(p), (l+r)/2 + 1, r, i, j);
                    if (p1 == -1)
                        res = p2;
                    else if(p2 == -1)
                        res = p1;
                    else{
                        if(A[p1] <= A[p2])
                            res = p1;
                        else    
                            res = p2;
                    }
                }
            }
            return res;
        }

        void balance(int pos){
            int i = 0;
            int j = n-1;
            int p = 1;
            while(i != j){
                int half = (i + j) / 2;
                if (half >= pos){
                    j = half;
                    p = p * 2;
                }
                else{
                    i = half + 1;
                    p = p * 2 + 1;
                }
            }
            //cout << p << endl;
            // Other child:
            int other_child = ((p % 2) == 0? p + 1 : p -1);
            p = (A[st[p]] > A[st[other_child]] ? p : other_child);
            while(p > 0 && A[st[p]] <= A[st[p/2]]){
                other_child = ((p % 2) == 0? p + 1 : p -1);
                p = (A[st[p]] <= A[st[other_child]] ? p : other_child);
                if (A[st[p]] <= A[st[p/2]]){
                    st[p/2] = st[p];
                    p /= 2;
                }
                else{
                    break;
                }
            }
        }

    public:
        int rmq (int i, int j){
            return rmq(1, 0, n-1, i, j); 
        }


        void print_st(){
            for (int i: st){
                cout << i << " ";
            }
            cout << endl;
        }

        void update_tree(int pos, int val){
            A[pos] = val;
            balance(pos);
        }
        SegmentTree(const vector<int> & vect){
            n = vect.size();
            A = vect;
            st.assign(4*n, 0);
            // Position 0 will always left empty in the st.
            build(1, 0, n-1);
            // print_st();
        }

};


int main(){
    int T;
    cin >> T;
    FOR(q,0,T){
        int n;
        cin >> n;
        vi v(n);
        vi vneg(n);
        vi range(n), rangeneg(n);
        FOR(i,0,n){
            cin >> v[i];
            v[i]--;
            vneg[i] = -v[i];
            range[i] = i;
            rangeneg[i] = -i;
        }
        SegmentTree stmin (range);
        SegmentTree stmax(rangeneg);
        vi resmin;
        vi resmax;
        FOR(i,0,n){
            if (i == 0){
                resmin.push_back(v[i]);
                resmax.push_back(v[i]);
                stmin.update_tree(v[i], 300000);
                stmax.update_tree(v[i], 300000);
            }
            else if (v[i] > v[i-1]){
                resmin.push_back(v[i]);
                resmax.push_back(v[i]);
                stmin.update_tree(v[i], 300000);
                stmax.update_tree(v[i], 300000);
            }
            else{
                int posmin = stmin.rmq(0, v[i]);
                resmin.push_back(posmin);
                stmin.update_tree(posmin, 300000);
                int posmax = stmax.rmq(0, v[i]);
                resmax.push_back(posmax);
                stmax.update_tree(posmax, 300000);
            }
        }
        FOR(i,0,resmin.size()){
            cout << resmin[i] + 1 << " " ;
        }
        cout << endl;
        FOR(i,0,resmax.size()){
            cout << resmax[i] + 1 << " " ;
        }
        cout << endl;
    }
    return 0;
}