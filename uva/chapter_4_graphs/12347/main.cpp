#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <unordered_set>

using namespace std;

// #define TESTING

#ifdef TESTING 
#define DEBUG cout << "====TESTING====\n" 
#define VALUE(x) cout << "The value of " << #x << " is " << x << endl 
#define PAIR(x) cout << x.first << "\t" << x.second
#define VECT(x) for (int u = 0; u<x.size(); u++) cout << x[u] << " "; cout << endl
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
typedef vector<vector<long long>> vvll;
typedef vector<vector<vector<ll>>> vvvll;
typedef pair<int, int> ii;
typedef pair<double, double> dd;
typedef vector<ii> vii;
typedef vector<dd> vdd;
typedef vector<vii> vvii;
typedef vector<bool> vb;
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define MODULUS 10000
#define DELTA 0.0000001
#define INF 100

class Node {
    public:
    int val;
    
    Node* l, *r;
    Node(int val) : val(val), l(NULL), r(NULL){

    }
    
};


Node* pre_order(vi& pre, int start, int end) {
    if (start > end){
        return NULL;
    }
    Node* node = new Node(pre[start]);
    if (start == end){
        return node;
    }
    
    
    if (pre[start+1] > pre[start]){
        node->r = pre_order(pre, start+1, end);
    }
    else if (pre[end] < pre[start]){
        node->l = pre_order(pre, start+1, end);
    }
    else{
        int i=start + 1, j=end;
        while(i!=j){
            int mid = ((i+j)/2);
            if (pre[mid]>pre[start]){
                j = mid;
            }
            else if (pre[mid]<pre[start]){
                i = mid+1;
            }
        }
        node->l = pre_order(pre, start+1, i-1);
        if (i > start)
            node->r = pre_order(pre, i, end);
    }

    return node;
}

void post_order(Node* bst) {
    if (bst->l != NULL){
        post_order(bst->l);
    }
    if (bst->r != NULL){
        post_order(bst->r);
    }
    cout << bst->val << endl;
}

int main(){
    vi pre;
    while(!cin.eof()) {
        int n; cin >> n;
        if(cin.eof())
            break;
        pre.push_back(n);
    }
    // cout << pre.size() << endl;
    Node* bst = pre_order(pre, 0, pre.size()-1);

    post_order(bst);

    return 0;
}
