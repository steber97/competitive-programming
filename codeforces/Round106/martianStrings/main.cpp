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

vi sa;

vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}



vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

class SegmentTreeMax{
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
                if (A[st[left(p)]] > A[st[right(p)]]){
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
                        if(A[p1] >= A[p2])
                            res = p1;
                        else    
                            res = p2;
                    }
                }
            }
            return res;
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

        SegmentTreeMax(const vector<int> & vect){
            n = vect.size();
            A = vect;
            st.assign(4*n, 0);
            // Position 0 will always left empty in the st.
            build(1, 0, n-1);
            // print_st();
        }
        SegmentTreeMax(){
            ;
        }

};

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
        SegmentTree(){
            ;
        }

};

string s;
SegmentTree st;
SegmentTreeMax stmax;

int binary_search_low(vi& sa, string magic, string& s){
    int start = 0;
    int end = sa.size()-1;
    while(start <= end){
        int half = (start + end)/2;
        // VALUE(half);
        // VALUE(s.substr(sa[half], magic.size()));
        // VALUE(magic);
        if (s.substr(sa[half], magic.size()).compare(magic) == 0){
            if (start == half){
                return half;
            }    
            end = half;
        }
        else if (s.substr(sa[half], magic.size()).compare(magic) > 0){
            end = half - 1;
        }
        else{
            start = half + 1;
        }
    }
    return -1;
}

int binary_search_high(vi& sa, string magic, string& s){
    int start = 0;
    int end = sa.size()-1;
    while(start <= end){
        if (start == end){
            if (s.substr(sa[start], magic.size()).compare(magic) == 0)
                return start;
            else 
                return -1;
        }
        int half = (start + end)/2 + 1;
        // VALUE(half);
        // VALUE(s.substr(sa[half], magic.size()));
        // VALUE(magic);
        if (s.substr(sa[half], magic.size()).compare(magic) == 0){
            if (end == half){
                return half;
            }    
            start = half;
        }
        else if (s.substr(sa[half], magic.size()).compare(magic) > 0){
            end = half - 1;
        }
        else{
            start = half + 1;
        }
    }
    return -1;
}

bool fatina (int start, int end, int& counter, string& magic, string& s){
    if (start > end)
        return false;
    int half = (start+end) / 2 ;
    string substr1 = magic.substr(0, half);
    string substr2 = magic.substr(half, magic.size()-half);
    if (substr1.size()>0 && substr2.size()>0){
        VALUE(substr1); VALUE(substr2);
        int a1 = binary_search_low(sa, substr1, s);
        int a2 = binary_search_high(sa, substr1, s);
        int b1 = binary_search_low(sa, substr2, s);
        int b2 = binary_search_high(sa, substr2, s);
        if (a1 != -1 && b1 != -1){
            int min = sa[st.rmq(a1, a2)];
            int max = sa[stmax.rmq(b1, b2)];
            if (min + substr1.size() <= max){
                counter++;
                return true;
            }
            else{
                if (fatina (start, half-1, counter, magic, s)){
                    return true;
                }
                return fatina (half+1, end, counter, magic, s);
            }
        }
        else if (a1 == -1 && b1 == -1){
            return false;
        }
        else if (a1 == -1){
            return fatina (start, half-1, counter, magic, s);
        }
        else if (b1 == -1){
            return fatina (half+1, end, counter, magic, s);
        }
    }
    else if (substr1.size()==0){
        return fatina (half+1, end, counter, magic, s);
    }
    else {
        return fatina (start, half-1, counter, magic, s);
    }
}

int main(){
    cin >> s;
    sa = suffix_array_construction(s);
    st = SegmentTree(sa);
    stmax = SegmentTreeMax(sa);
    VECT(sa);
    int N;
    cin >> N;
    int counter = 0;
    // VALUE(binary_search_low(sa, "D", s));
    // VALUE(binary_search_high(sa, "D", s));
    // return 0;
    FOR(i,0,N){
        string magic;
        cin >> magic;
        // [0,half[, [half, size()[
        bool res = fatina(0, magic.size()-1, counter, magic, s);
    }
    cout << counter << endl;
    return 0;
}