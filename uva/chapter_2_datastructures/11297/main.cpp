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


class SegmentTree2D{
    private:
        vvi A;
        vii st;
        int n1, n2;  // Height and width of A.
        bool min_segment_tree;
        // to get right and let children in a heap fashion.
        
        int getUpLeft(int p){
            return p * 4 - 2;
        }
        int getUpRight(int p){
            return p * 4 - 1;
        }
        int getDownLeft(int p){
            return p * 4;
        }
        int getDownRight(int p){
            return p * 4 + 1;
        } 

        /*
            Returns true if A[pos1] < A[pos2] (if min segment tree)
            Otherwise viceversa.
        */
        bool compare(int pos1, int pos2){

            if(this->min_segment_tree){
                return A[st[pos1].first][st[pos1].second] < A[st[pos2].first][st[pos2].second];
            }
            else{
                return A[st[pos1].first][st[pos1].second] > A[st[pos2].first][st[pos2].second];
            }
        }

        bool compare(ii p1, ii p2){
            if (this->min_segment_tree)
                return A[p1.first][p1.second] < A[p2.first][p2.second];
            else 
                return A[p1.first][p1.second] > A[p2.first][p2.second];
        }

        void build(int p, int u, int d, int l, int r){
            /** 
             * left right up down.
             */
            assert (p < st.size());
            if (l > r || u > d){
                // stop here.
            }
            else if (l == r && u == d){
                st[p] = {u, l};  // Base case, interval is 1 cell.
            }
            else{
                build(getUpLeft(p), u, (d+u)/2, l, (l+r)/2);
                build(getUpRight(p), u, (d+u)/2, (l+r)/2 + 1, r);
                build(getDownLeft(p), (u+d)/2 + 1, d, l, (l+r)/2);
                build(getDownRight(p), (u+d)/2 + 1, d, (l+r)/2 + 1, r);
                
                int bestpos = (st[getUpLeft(p)].first != -1 ? getUpLeft(p) : (st[getUpRight(p)].first != -1 ? getUpRight(p) : (st[getDownLeft(p)].first != -1 ? getDownLeft(p) : getDownRight(p))));
                assert(bestpos!=-1);
                if (st[getUpLeft(p)].first != -1 && compare(getUpLeft(p), bestpos)){
                    bestpos = getUpLeft(p);
                }
                if (st[getUpRight(p)].first != -1 && compare(getUpRight(p), bestpos)){
                    bestpos = getUpRight(p);
                }
                if (st[getDownLeft(p)].first != -1 && compare(getDownLeft(p), bestpos)){
                    bestpos = getDownLeft(p);
                }
                if (st[getDownRight(p)].first != -1 && compare(getDownRight(p), bestpos)){
                    bestpos = getDownRight(p);
                }
                st[p] = st[bestpos];
            }
        }

        /**
         * @brief 
         * 
         * @param p position in heap
         * @param l left
         * @param r right
         * @param u up
         * @param d down
         * @param i index left
         * @param j index right
         * @param k index up
         * @param t index down
         * @return ii 
         */
        ii rmq(int p, int u, int d, int l, int r, int k, int t, int i, int j){
            ii res;
            assert(p<st.size());
            if (i > r || j < l || k > d || t < u){
                // If out of range:
                res = {-1, -1};
            }
            else{
                if (l >= i && r <= j && u >= k && d <= t){
                    res = st[p];
                }
                else{
                    ii p1 = rmq(getUpLeft(p), u, (u+d)/2, l, (l+r) / 2, k, t, i, j);
                    ii p2 = rmq(getUpRight(p), u, (u+d)/2, (l+r)/2 + 1, r, k, t, i, j);
                    ii p3 = rmq(getDownLeft(p), (u+d)/2 + 1, d, l, (l+r)/2, k, t, i, j);
                    ii p4 = rmq(getDownRight(p), (u+d)/2 + 1, d, (l+r)/2 + 1, r, k, t, i, j);
                    
                    res = p1.first != -1 ? p1 : (p2.first != -1 ? p2 : (p3.first != -1 ? p3 : p4)); 
                    assert(res.first != -1);
                    if (p1.first != -1){
                        if (compare(p1, res)){
                            res = p1;
                        }
                    }
                    if (p2.first != -1){
                        if(compare(p2, res)){
                            res = p2;
                        }
                    }
                    if (p3.first != -1){
                        if (compare(p3, res)){
                            res = p3;
                        }
                    }
                    if (p4.first != -1){
                        if (compare(p4, res)){
                            res = p4;
                        }
                    }
                }
            }
            return res;
        }

        void balance(ii pos){
            int k = 0;
            int t = n1-1;
            int i = 0;
            int j = n2-1;
            int p = 1;
            while(i != j || k != t){
                // COUT(p); COUT(" "); COUT(st[p].first); COUT(","); COUT(st[p].second); COUT(" "); COUT(k); COUT(" "); COUT(t); COUT(" "); COUT(i); COUT(" "); COUT(j); COUT(endl);
                int half1 = (k + t) / 2;
                int half2 = (i + j) / 2;

                if (pos.first <= half1 && pos.second <= half2){
                    t = half1;
                    j = half2;
                    p = p * 4 - 2;
                }
                else if (pos.first <= half1 && pos.second > half2){
                    t = half1;
                    i = half2 + 1;
                    p = p * 4 - 1;
                }
                else if (pos.first > half1 && pos.second <= half2){
                    k = half1 + 1;
                    j = half2;
                    p = p * 4;
                }
                else{
                    k = half1 + 1;
                    i = half2 + 1;
                    p = p * 4  + 1;
                }
            }
            assert(p<st.size());
            
            while(p > 1){
                int representative = ((p + 2) % 4) == 0 ? p + 2 : (((p+1)%4) == 0 ? p + 1 : ((p%4) == 0 ? p : p - 1));
                int parent = representative/4;
                if (parent == 0 || representative == 0)
                    break;
                if ((st[representative-2].first != -1) &&
                        compare(representative-2, parent)){ 
                    st[parent] = st[representative-2];
                }
                if ((st[representative-1].first != -1) &&
                        compare(representative-1, parent)){
                    st[parent] = st[representative-1];
                }
                if ((st[representative].first != -1) &&
                        compare(representative, parent)){
                    st[parent] = st[representative];
                }
                if ((st[representative+1].first != -1) &&
                        compare(representative+1, parent)){
                    st[parent] = st[representative+1];
                }
                p = parent;
            }
        }

    public:
        ii rmq (int k, int t, int i, int j){
            return rmq(1, 0, n1-1, 0, n2-1, k, t, i, j); 
        }

        void update_tree(ii pos, int val){
            A[pos.first][pos.second] = val;
            balance(pos);
        }


        /*
            min_segment_tree true-> make a minimum segment tree (returns min for rmq).
                otherwise return false.
        */
        SegmentTree2D(const vvi & vect, bool min_segment_tree = true){
            
            n1 = vect.size();
            if (n1 > 0)
                n2 = vect[0].size();
            else 
                n2 = 0;
            A = vect;
            this->min_segment_tree = min_segment_tree;
            st.assign(6*n1*n2, {-1, -1});
            // Position 0 will always left empty in the st.
            build(1, 0, n1-1, 0, n2-1);
        }

};



int main(){
    int n;
    cin >> n;
    vvi pop(n, vi(n));
    FOR(i,0,n){
        FOR(j,0,n){
            cin >> pop[i][j];
        }
    }

    SegmentTree2D stmin(pop, true);
    SegmentTree2D stmax(pop, false);
    
    int Q;
    cin >> Q;
    FOR(q,0,Q){
        char r;
        cin >> r;
        if (r == 'q'){
            int a,b,c,d;
            cin >> a >> b >> c >> d; 
            a--;b--;c--;d--;
            ii pmin, pmax;
            // pmin = stmin.rmq(b,d,a,c);
            // pmax = stmax.rmq(b,d,a,c);

            pmin = stmin.rmq(a,c,b,d);
            pmax = stmax.rmq(a,c,b,d);
            cout << pop[pmax.first][pmax.second] << " " << pop[pmin.first][pmin.second] << endl;
        }
        else {
            int a,b,c;
            cin >> a >> b >> c;
            a--; b--;
            // pop[b][a]= c;
            pop[a][b] = c;
            // stmin.update_tree({b,a}, c);
            // stmax.update_tree({b,a}, c);
            stmin.update_tree({a,b}, c);
            stmax.update_tree({a,b}, c);
        }
    }
    return 0;    
}